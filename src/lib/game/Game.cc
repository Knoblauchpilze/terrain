
#include "Game.hh"
#include "Bilinear.hh"
#include "GradientGenerator.hh"
#include "GradientLattice.hh"
#include "Hasher.hh"
#include "Menu.hh"
#include "PeriodicPerlinGenerator.hh"
#include "PeriodicPerlinLattice.hh"
#include "ValueGenerator.hh"
#include "ValueLattice.hh"
#include "WhiteNoise.hh"

#include <sstream>

namespace pge {

constexpr auto STATUS_MENU_HEIGHT      = 50;
constexpr auto PERFORMANCE_MENU_HEIGHT = 25;

constexpr auto MIN_NOISE_PERIOD = 4;
constexpr auto MAX_NOISE_PERIOD = 1024;

constexpr auto MIN_TERRAIN_SCALE = 2;
constexpr auto MAX_TERRAIN_SCALE = 16;

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

  menus = generatePerformanceMenus(width, height);
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
  m_terrain->increaseTimers();

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
  m_terrain->load(fileName);
}

void Game::save(const std::string &fileName) const
{
  m_terrain->save(fileName);
}

void Game::toggleLatticeMode()
{
  switch (m_latticeMode)
  {
    case LatticeMode::VALUE:
      m_latticeMode = LatticeMode::GRADIENT;
      break;
    case LatticeMode::GRADIENT:
      m_latticeMode = LatticeMode::PERLIN;
      break;
    case LatticeMode::PERLIN:
    default:
      m_latticeMode = LatticeMode::VALUE;
      break;
  }

  generate();
}

void Game::toggleDisplayMode()
{
  m_displayMode = (m_displayMode == DisplayMode::HEIGHT ? DisplayMode::TERRAIN
                                                        : DisplayMode::HEIGHT);
}

auto Game::displayMode() const noexcept -> DisplayMode
{
  return m_displayMode;
}

void Game::toggleTerrainScale()
{
  m_scale *= 2;
  if (m_scale > MAX_TERRAIN_SCALE)
  {
    m_scale = MIN_TERRAIN_SCALE;
  }

  generate();
}

auto Game::scale() const noexcept -> int
{
  return m_scale;
}

void Game::toggleNoisePeriod()
{
  m_period *= 2;
  if (m_period > MAX_NOISE_PERIOD)
  {
    m_period = MIN_NOISE_PERIOD;
  }

  generate();
}

auto Game::latticeAt(const int x, const int y) const -> std::vector<float>
{
  std::vector<float> out;

  switch (m_latticeMode)
  {
    case LatticeMode::VALUE:
      out.push_back(m_valueGenerator->at(utils::Vector2i(x, y)));
      break;
    case LatticeMode::GRADIENT:
    case LatticeMode::PERLIN:
    {
      const auto grad = m_gradientGenerator->at(utils::Vector2i(x, y));
      out.push_back(grad.x());
      out.push_back(grad.y());
    }
    break;
    default:
      break;
  }

  return out;
}

void Game::generate()
{
  const auto seed = m_nextSeed;
  auto hasher     = std::make_unique<lattice::Hasher>(seed);

  noise::INoisePtr noise;
  switch (m_latticeMode)
  {
    case LatticeMode::GRADIENT:
    {
      noise = std::make_unique<noise::WhiteNoise>(-1.0f, 1.0f);

      auto noiseCopy      = std::make_unique<noise::WhiteNoise>();
      auto hasherCopy     = std::make_unique<lattice::Hasher>(seed);
      m_gradientGenerator = std::make_unique<lattice::GradientGenerator>(std::move(hasherCopy),
                                                                         std::move(noiseCopy));
    }
    break;
    case LatticeMode::PERLIN:
      m_gradientGenerator = std::make_unique<lattice::PeriodicPerlinGenerator>(m_period, seed);
      break;
    case LatticeMode::VALUE:
    default:
    {
      noise = std::make_unique<noise::WhiteNoise>();

      auto noiseCopy   = std::make_unique<noise::WhiteNoise>();
      auto hasherCopy  = std::make_unique<lattice::Hasher>(seed);
      m_valueGenerator = std::make_unique<lattice::ValueGenerator>(std::move(hasherCopy),
                                                                   std::move(noiseCopy));
    }
    break;
  }

  auto interpolator = std::make_unique<interpolation::Bilinear>();

  lattice::ILatticePtr lattice;
  switch (m_latticeMode)
  {
    case LatticeMode::GRADIENT:
      lattice = std::make_unique<lattice::GradientLattice>(std::move(hasher),
                                                           std::move(noise),
                                                           std::move(interpolator));
      break;
    case LatticeMode::PERLIN:
      lattice = std::make_unique<lattice::PeriodicPerlinLattice>(m_period,
                                                                 seed,
                                                                 std::move(interpolator));
      break;
    case LatticeMode::VALUE:
    default:
      lattice = std::make_unique<lattice::ValueLattice>(std::move(hasher),
                                                        std::move(noise),
                                                        std::move(interpolator));
      break;
  }

  m_terrain = std::make_unique<terrain::Terrain>(std::move(lattice), m_scale);
  ++m_nextSeed;
}

auto Game::terrain() const noexcept -> const terrain::Terrain &
{
  return *m_terrain;
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
  auto text = "Scale: " + std::to_string(m_scale);
  m_menus.scale->setText(text);

  text = "Lattice: ";
  text += (m_latticeMode == LatticeMode::GRADIENT
             ? "gradient"
             : (m_latticeMode == LatticeMode::PERLIN ? "perlin" : "value"));
  m_menus.lattice->setText(text);

  text = "Display: ";
  text += (m_displayMode == DisplayMode::HEIGHT ? "height" : "terrain");
  m_menus.display->setText(text);

  text = "Period: ";
  text += std::to_string(m_period);
  m_menus.period->setText(text);

  const auto perf = m_terrain->timers();
  if (perf.steps == 0)
  {
    return;
  }
  constexpr auto NANOSECOND_TO_MILLISECOND = 1.0f / 1'000'000.0f;

  const auto readable = [](const int64_t v, const int64_t steps) -> std::string {
    auto out = NANOSECOND_TO_MILLISECOND * v;
    out /= steps;

    std::stringstream ss;
    ss.precision(3);

    ss << out;
    return ss.str();
  };

  text = "H: ";
  text += readable(perf.heightDuration, perf.steps);
  text += "ms";
  m_menus.height->setText(text);

  text = "A: ";
  text += readable(perf.atDuration, perf.steps);
  text += "ms";
  m_menus.at->setText(text);

  text = "Ar: ";
  text += readable(perf.areaDuration, perf.steps);
  text += "ms";
  m_menus.area->setText(text);

  text = "G: ";
  text += readable(perf.generateForDuration, perf.steps);
  text += "ms";
  m_menus.generateFor->setText(text);

  text = "I: ";
  text += readable(perf.interpolateDuration, perf.steps);
  text += "ms";
  m_menus.interpolate->setText(text);

  text = "N: ";
  text += readable(perf.normalizeDuration, perf.steps);
  text += "ms";
  m_menus.normalize->setText(text);

  text = "M: ";
  text += readable(perf.modulusDuration, perf.steps);
  text += "ms";
  m_menus.modulus->setText(text);

  text = "P: ";
  text += readable(perf.permDuration, perf.steps);
  text += "ms";
  m_menus.perm->setText(text);

  text = "Gr: ";
  text += readable(perf.gradDuration, perf.steps);
  text += "ms";
  m_menus.grad->setText(text);
}

auto Game::generateStatusMenus(int width, int /*height*/) -> std::vector<MenuShPtr>
{
  std::vector<MenuShPtr> out{};
  auto status = generateMenu(olc::vi2d{0, 0},
                             olc::vi2d{width, STATUS_MENU_HEIGHT},
                             "",
                             "status",
                             false,
                             menu::Layout::Horizontal);

  m_menus.scale = generateMenu(olc::vi2d{0, 0},
                               olc::vi2d{10, STATUS_MENU_HEIGHT},
                               "Scale: N/A",
                               "scale",
                               true);
  m_menus.scale->setSimpleAction([](Game &g) { g.toggleTerrainScale(); });
  status->addMenu(m_menus.scale);
  m_menus.lattice = generateMenu(olc::vi2d{0, 0},
                                 olc::vi2d{10, STATUS_MENU_HEIGHT},
                                 "Lattice: N/A",
                                 "lattice",
                                 false);
  status->addMenu(m_menus.lattice);
  m_menus.display = generateMenu(olc::vi2d{0, 0},
                                 olc::vi2d{10, STATUS_MENU_HEIGHT},
                                 "Display: N/A",
                                 "display",
                                 false);
  status->addMenu(m_menus.display);
  m_menus.period = generateMenu(olc::vi2d{0, 0},
                                olc::vi2d{10, STATUS_MENU_HEIGHT},
                                "Period: " + std::to_string(m_period),
                                "period",
                                true);
  m_menus.period->setSimpleAction([](Game &g) { g.toggleNoisePeriod(); });
  status->addMenu(m_menus.period);

  out.push_back(status);
  return out;
}

auto Game::generatePerformanceMenus(int width, int height) -> std::vector<MenuShPtr>
{
  std::vector<MenuShPtr> out{};
  auto perf = generateMenu(olc::vi2d{0, height - PERFORMANCE_MENU_HEIGHT},
                           olc::vi2d{width, PERFORMANCE_MENU_HEIGHT},
                           "",
                           "perf",
                           false,
                           menu::Layout::Horizontal);

  m_menus.height = generateMenu(olc::vi2d{0, 0},
                                olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                                "H: N/A",
                                "height",
                                false);
  perf->addMenu(m_menus.height);
  m_menus.at = generateMenu(olc::vi2d{0, 0},
                            olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                            "A: N/A",
                            "at",
                            false);
  perf->addMenu(m_menus.at);
  m_menus.area = generateMenu(olc::vi2d{0, 0},
                              olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                              "Ar: N/A",
                              "area",
                              false);
  perf->addMenu(m_menus.area);
  m_menus.generateFor = generateMenu(olc::vi2d{0, 0},
                                     olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                                     "G: N/A",
                                     "generateFor",
                                     false);
  perf->addMenu(m_menus.generateFor);
  m_menus.interpolate = generateMenu(olc::vi2d{0, 0},
                                     olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                                     "I: N/A",
                                     "interpolate",
                                     false);
  perf->addMenu(m_menus.interpolate);
  m_menus.normalize = generateMenu(olc::vi2d{0, 0},
                                   olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                                   "N: N/A",
                                   "normalize",
                                   false);
  perf->addMenu(m_menus.normalize);
  m_menus.modulus = generateMenu(olc::vi2d{0, 0},
                                 olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                                 "M: N/A",
                                 "modulus",
                                 false);
  perf->addMenu(m_menus.modulus);
  m_menus.perm = generateMenu(olc::vi2d{0, 0},
                              olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                              "P: N/A",
                              "perm",
                              false);
  perf->addMenu(m_menus.perm);
  m_menus.grad = generateMenu(olc::vi2d{0, 0},
                              olc::vi2d{10, PERFORMANCE_MENU_HEIGHT},
                              "Gr: N/A",
                              "grad",
                              false);
  perf->addMenu(m_menus.grad);

  out.push_back(perf);

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
