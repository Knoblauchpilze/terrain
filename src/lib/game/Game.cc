
#include "Game.hh"
#include "GradientGenerator.hh"
#include "Hasher.hh"
#include "Menu.hh"
#include "PeriodicGradientGenerator.hh"
#include "PeriodicPerlinGenerator.hh"
#include "ValueGenerator.hh"
#include "WhiteNoise.hh"

namespace pge {

constexpr auto DEFAULT_MENU_HEIGHT = 50;

namespace {
auto generateMenu(const olc::vi2d &pos,
                  const olc::vi2d &size,
                  const std::string &text,
                  const std::string &name,
                  bool clickable             = false,
                  const menu::Layout &layout = menu::Layout::Vertical,
                  olc::Pixel bgColor         = olc::VERY_DARK_GREEN) -> pge::MenuShPtr
{
  auto fd = pge::menu::newMenuContent(text, "", size);

  fd.color  = bgColor == olc::BLACK ? olc::WHITE : olc::BLACK;
  fd.hColor = RGBToHSL(bgColor).b < 128 ? olc::WHITE : olc::BLACK;

  fd.align = pge::menu::Alignment::Center;

  return std::make_shared<pge::Menu>(pos,
                                     size,
                                     name,
                                     pge::menu::newColoredBackground(bgColor),
                                     fd,
                                     layout,
                                     clickable,
                                     false);
}
} // namespace

Game::Game()
  : utils::CoreObject("game")
{
  setService("game");

  generate();
}

std::vector<MenuShPtr> Game::generateMenus(float width, float height)
{
  std::vector<MenuShPtr> out;

  auto menus = generateLatticeMenus(width, height);
  for (const auto &menu : menus)
  {
    out.push_back(menu);
  }

  menus = generateTerrainMenus(width, height);
  for (const auto &menu : menus)
  {
    out.push_back(menu);
  }

  return out;
}

void Game::performAction(float /*x*/, float /*y*/)
{
  // Only handle actions when the game is not disabled.
  if (m_state.disabled)
  {
    debug("Ignoring action while menu is disabled");
    return;
  }
}

bool Game::step(float /*tDelta*/)
{
  // When the game is paused it is not over yet.
  if (m_state.paused)
  {
    return true;
  }

  updateUI();

  return true;
}

void Game::togglePause()
{
  if (m_state.paused)
  {
    resume();
  }
  else
  {
    pause();
  }

  enable(!m_state.paused);
}

void Game::load(const std::string &fileName)
{
  m_map.load(fileName);
}

void Game::save(const std::string &fileName) const
{
  m_map.save(fileName);
}

auto Game::displayMode() const noexcept -> DisplayMode
{
  return m_displayMode;
}

void Game::toggleDisplayMode(bool /*prev*/)
{
  /// Two values don't really benefit from the cycling order.
  m_displayMode = (m_displayMode == DisplayMode::HEIGHT ? DisplayMode::TERRAIN
                                                        : DisplayMode::HEIGHT);
}

void Game::toggleTerrainMode(bool prev)
{
  m_map.nextTerrain(prev);
}

void Game::toggleLatticeMode(bool prev)
{
  m_map.nextLattice(prev);
  generate();
}

void Game::toggleInterpolationMode(bool prev)
{
  m_map.nextInterpolation(prev);
  generate();
}

void Game::toggleNoisePeriod(bool prev)
{
  m_map.nextPeriod(prev);
  generate();
}

void Game::toggleCacheSize(bool prev)
{
  m_map.nextCacheSize(prev);
  generate();
}

void Game::toggleTerrainScale(bool prev)
{
  m_map.nextScale(prev);
  generate();
}

void Game::toggleTerrainLacunarity(bool prev)
{
  m_map.nextLacunarity(prev);
  generate();
}

void Game::toggleTerrainGain(bool prev)
{
  m_map.nextGain(prev);
  generate();
}

void Game::toggleTerrainLayer(bool prev)
{
  m_map.nextLayersCount(prev);
  generate();
}

void Game::toggleNextSeed()
{
  m_map.nextSeed();
  generate();
}

auto Game::latticeAt(const int x, const int y) const -> std::vector<float>
{
  std::vector<float> out;

  const terrain::LatticePoint2d p(x / m_map.scale(), y / m_map.scale());

  if (m_valueGenerator != nullptr)
  {
    out.push_back(m_valueGenerator->at(p));
  }
  else if (m_gradientGenerator != nullptr)
  {
    const auto grad = m_gradientGenerator->at(p);
    out.insert(out.end(), grad.begin(), grad.end());
  }

  return out;
}

void Game::generate()
{
  m_valueGenerator.reset();
  m_gradientGenerator.reset();

  switch (m_map.lattice())
  {
    case terrain::LatticeType::GRADIENT:
    {
      auto noise          = std::make_unique<terrain::WhiteNoise>(-1.0f, 1.0f);
      auto hasher         = std::make_unique<terrain::Hasher2d>(m_map.seed());
      m_gradientGenerator = std::make_unique<terrain::GradientGenerator2d>(std::move(hasher),
                                                                           std::move(noise),
                                                                           m_map.cacheSize());
    }
    break;
    case terrain::LatticeType::PERIODIC_GRADIENT:
      m_gradientGenerator = std::make_unique<terrain::PeriodicGradientGenerator2d>(m_map.period(),
                                                                                   m_map.seed());
      break;
    case terrain::LatticeType::PERIODIC_PERLIN:
      m_gradientGenerator = std::make_unique<terrain::PeriodicPerlinGenerator2d>(m_map.period(),
                                                                                 m_map.seed());
      break;
    case terrain::LatticeType::VALUE:
    default:
    {
      auto noise       = std::make_unique<terrain::WhiteNoise>();
      auto hasher      = std::make_unique<terrain::Hasher2d>(m_map.seed());
      m_valueGenerator = std::make_unique<terrain::ValueGenerator2d>(std::move(hasher),
                                                                     std::move(noise),
                                                                     m_map.cacheSize());
    }
    break;
  }
}

auto Game::map() const noexcept -> const terrain::Map &
{
  return m_map;
}

void Game::enable(bool enable)
{
  m_state.disabled = !enable;

  if (m_state.disabled)
  {
    verbose("Disabled game UI");
  }
  else
  {
    verbose("Enabled game UI");
  }
}

void Game::updateUI()
{
  // Lattice options.
  auto text = "Scale: " + std::to_string(m_map.scale());
  m_menus.scale->setText(text);

  text = str(m_map.lattice());
  m_menus.lattice->setText(text);

  text = str(m_map.interpolation());
  m_menus.interpolation->setText(text);

  text = (m_displayMode == DisplayMode::HEIGHT ? "height" : "terrain");
  m_menus.display->setText(text);

  text = "Period: ";
  text += std::to_string(m_map.period());
  m_menus.period->setText(text);

  text = "Cache: ";
  text += std::to_string(m_map.cacheSize());
  m_menus.cache->setText(text);

  // Terrain options.
  text = "Terrain: ";
  text += str(m_map.terrain());
  m_menus.terrain->setText(text);

  text = "Layers: ";
  text += std::to_string(m_map.layersCount());
  m_menus.layers->setText(text);

  text = "Gain: ";
  text += std::to_string(m_map.gain());
  m_menus.gain->setText(text);

  text = "Lacunarity: ";
  text += std::to_string(m_map.lacunarity());
  m_menus.lacunarity->setText(text);
}

auto Game::generateLatticeMenus(int width, int /*height*/) -> std::vector<MenuShPtr>
{
  std::vector<MenuShPtr> out{};
  auto status = generateMenu(olc::vi2d{0, 0},
                             olc::vi2d{width, DEFAULT_MENU_HEIGHT},
                             "",
                             "status",
                             false,
                             menu::Layout::Horizontal);

  m_menus.scale = generateMenu(olc::vi2d{0, 0},
                               olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                               "Scale: N/A",
                               "scale",
                               true);
  m_menus.scale->setSimpleAction([](Game &g) { g.toggleTerrainScale(false); });
  status->addMenu(m_menus.scale);
  m_menus.lattice = generateMenu(olc::vi2d{0, 0},
                                 olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                 "Lattice: N/A",
                                 "lattice",
                                 true);
  m_menus.lattice->setSimpleAction([](Game &g) { g.toggleLatticeMode(false); });
  status->addMenu(m_menus.lattice);
  m_menus.interpolation = generateMenu(olc::vi2d{0, 0},
                                       olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                       "Interpolation: N/A",
                                       "interpolation",
                                       true);
  m_menus.interpolation->setSimpleAction([](Game &g) { g.toggleInterpolationMode(false); });
  status->addMenu(m_menus.interpolation);
  m_menus.display = generateMenu(olc::vi2d{0, 0},
                                 olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                 "Display: N/A",
                                 "display",
                                 true);
  m_menus.display->setSimpleAction([](Game &g) { g.toggleDisplayMode(false); });
  status->addMenu(m_menus.display);
  m_menus.period = generateMenu(olc::vi2d{0, 0},
                                olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                "Period: N/A",
                                "period",
                                true);
  m_menus.period->setSimpleAction([](Game &g) { g.toggleNoisePeriod(false); });
  status->addMenu(m_menus.period);
  m_menus.cache = generateMenu(olc::vi2d{0, 0},
                               olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                               "Cache: N/A",
                               "cache",
                               true);
  m_menus.cache->setSimpleAction([](Game &g) { g.toggleCacheSize(false); });
  status->addMenu(m_menus.cache);

  auto gen = generateMenu(olc::vi2d{0, 0},
                          olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                          "Generate",
                          "generate",
                          true);
  gen->setSimpleAction([](Game &g) { g.toggleNextSeed(); });
  status->addMenu(gen);

  out.push_back(status);
  return out;
}

auto Game::generateTerrainMenus(int width, int height) -> std::vector<MenuShPtr>
{
  std::vector<MenuShPtr> out{};
  auto terrain = generateMenu(olc::vi2d{0, height - DEFAULT_MENU_HEIGHT},
                              olc::vi2d{width, DEFAULT_MENU_HEIGHT},
                              "",
                              "terrain",
                              false,
                              menu::Layout::Horizontal);

  m_menus.terrain = generateMenu(olc::vi2d{0, 0},
                                 olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                 "Terrain: N/A",
                                 "terrain",
                                 true);
  m_menus.terrain->setSimpleAction([](Game &g) { g.toggleTerrainMode(false); });
  terrain->addMenu(m_menus.terrain);
  m_menus.layers = generateMenu(olc::vi2d{0, 0},
                                olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                "Layers: N/A",
                                "layers",
                                true);
  m_menus.layers->setSimpleAction([](Game &g) { g.toggleTerrainLayer(false); });
  terrain->addMenu(m_menus.layers);
  m_menus.gain = generateMenu(olc::vi2d{0, 0},
                              olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                              "Gain: N/A",
                              "gain",
                              true);
  m_menus.gain->setSimpleAction([](Game &g) { g.toggleTerrainGain(false); });
  terrain->addMenu(m_menus.gain);
  m_menus.lacunarity = generateMenu(olc::vi2d{0, 0},
                                    olc::vi2d{10, DEFAULT_MENU_HEIGHT},
                                    "Lacunarity: N/A",
                                    "lacunarity",
                                    true);
  m_menus.lacunarity->setSimpleAction([](Game &g) { g.toggleTerrainLacunarity(false); });
  terrain->addMenu(m_menus.lacunarity);

  out.push_back(terrain);
  return out;
}

bool Game::TimedMenu::update(bool active) noexcept
{
  // In case the menu should be active.
  if (active)
  {
    if (!wasActive)
    {
      // Make it active if it's the first time that
      // we detect that it should be active.
      date      = utils::now();
      wasActive = true;
      menu->setVisible(true);
    }
    else if (utils::now() > date + utils::toMilliseconds(duration))
    {
      // Deactivate the menu in case it's been active
      // for too long.
      menu->setVisible(false);
    }
    else
    {
      // Update the alpha value in case it's active
      // for not long enough.
      olc::Pixel c = menu->getBackgroundColor();

      float d = utils::diffInMs(date, utils::now()) / duration;
      c.a     = static_cast<uint8_t>(std::clamp((1.0f - d) * pge::alpha::Opaque, 0.0f, 255.0f));
      menu->setBackground(pge::menu::newColoredBackground(c));
    }
  }
  // Or if the menu shouldn't be active anymore and
  // it's the first time we detect that.
  else if (wasActive)
  {
    // Deactivate the menu.
    menu->setVisible(false);
    wasActive = false;
  }

  return menu->visible();
}

} // namespace pge
