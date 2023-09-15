
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

  auto menus = generateStatusMenus(width, height);
  for (auto &menu : menus)
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
    log("Ignoring action while menu is disabled");
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
  m_terrain.load(fileName);
}

void Game::save(const std::string &fileName) const
{
  m_terrain.save(fileName);
}

void Game::toggleLatticeMode(bool prev)
{
  m_terrain.nextLattice(prev);
  generate();
}

void Game::toggleDisplayMode(bool /*prev*/)
{
  /// Two values don't really benefit from the cycling order.
  m_displayMode = (m_displayMode == DisplayMode::HEIGHT ? DisplayMode::TERRAIN
                                                        : DisplayMode::HEIGHT);
}

auto Game::displayMode() const noexcept -> DisplayMode
{
  return m_displayMode;
}

void Game::toggleNextSeed()
{
  m_terrain.nextSeed();
  generate();
}

void Game::toggleTerrainScale(bool prev)
{
  m_terrain.nextScale(prev);
  generate();
}

void Game::toggleNoisePeriod(bool prev)
{
  m_terrain.nextPeriod(prev);
  generate();
}

void Game::toggleCacheSize(bool prev)
{
  m_terrain.nextCacheSize(prev);
  generate();
}

auto Game::latticeAt(const int x, const int y) const -> std::vector<float>
{
  std::vector<float> out;

  const terrain::LatticePoint2d p(x / m_terrain.scale(), y / m_terrain.scale());

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

  switch (m_terrain.lattice())
  {
    case terrain::LatticeType::GRADIENT:
    {
      auto noise          = std::make_unique<terrain::WhiteNoise>(-1.0f, 1.0f);
      auto hasher         = std::make_unique<terrain::Hasher2d>(m_terrain.seed());
      m_gradientGenerator = std::make_unique<terrain::GradientGenerator2d>(std::move(hasher),
                                                                           std::move(noise),
                                                                           m_terrain.cacheSize());
    }
    break;
    case terrain::LatticeType::PERIODIC_GRADIENT:
      m_gradientGenerator
        = std::make_unique<terrain::PeriodicGradientGenerator2d>(m_terrain.period(),
                                                                 m_terrain.seed());
      break;
    case terrain::LatticeType::PERIODIC_PERLIN:
      m_gradientGenerator = std::make_unique<terrain::PeriodicPerlinGenerator2d>(m_terrain.period(),
                                                                                 m_terrain.seed());
      break;
    case terrain::LatticeType::VALUE:
    default:
    {
      auto noise       = std::make_unique<terrain::WhiteNoise>();
      auto hasher      = std::make_unique<terrain::Hasher2d>(m_terrain.seed());
      m_valueGenerator = std::make_unique<terrain::ValueGenerator2d>(std::move(hasher),
                                                                     std::move(noise),
                                                                     m_terrain.cacheSize());
    }
    break;
  }
}

auto Game::terrain() const noexcept -> const terrain::Terrain &
{
  return m_terrain;
}

void Game::enable(bool enable)
{
  m_state.disabled = !enable;

  if (m_state.disabled)
  {
    log("Disabled game UI", utils::Level::Verbose);
  }
  else
  {
    log("Enabled game UI", utils::Level::Verbose);
  }
}

void Game::updateUI()
{
  auto text = "Scale: " + std::to_string(m_terrain.scale());
  m_menus.scale->setText(text);

  text = "Lattice: ";
  text += str(m_terrain.lattice());
  m_menus.lattice->setText(text);

  text = "Display: ";
  text += (m_displayMode == DisplayMode::HEIGHT ? "height" : "terrain");
  m_menus.display->setText(text);

  text = "Period: ";
  text += std::to_string(m_terrain.period());
  m_menus.period->setText(text);

  text = "Cache: ";
  text += std::to_string(m_terrain.cacheSize());
  m_menus.cache->setText(text);
}

auto Game::generateStatusMenus(int width, int /*height*/) -> std::vector<MenuShPtr>
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
