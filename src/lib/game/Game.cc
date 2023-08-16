
#include "Game.hh"
#include "Bilinear.hh"
#include "Hasher.hh"
#include "Menu.hh"
#include "ValueLattice.hh"
#include "WhiteNoise.hh"

namespace pge {

constexpr auto DEFAULT_MENU_WIDTH = 100;

namespace {
auto generateMenu(const olc::vi2d &pos,
                  const olc::vi2d &size,
                  const std::string &text,
                  const std::string &name,
                  bool clickable     = false,
                  olc::Pixel bgColor = olc::VERY_DARK_GREEN) -> pge::MenuShPtr
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
                                     pge::menu::Layout::Vertical,
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

Game::~Game() {}

std::vector<MenuShPtr> Game::generateMenus(float width, float height)
{
  std::vector<MenuShPtr> out;

  auto menus = generateNoiseMenus(width, height);
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
  m_terrain->load(fileName);
}

void Game::save(const std::string &fileName) const
{
  m_terrain->save(fileName);
}

void Game::generate()
{
  const auto seed   = m_nextSeed;
  auto hasher       = std::make_unique<lattice::Hasher>(seed);
  auto noise        = std::make_unique<noise::WhiteNoise>();
  auto interpolator = std::make_unique<interpolation::Bilinear>();
  auto lattice      = std::make_unique<lattice::ValueLattice>(std::move(hasher),
                                                         std::move(noise),
                                                         std::move(interpolator));
  m_terrain         = std::make_unique<terrain::Terrain>(std::move(lattice));
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

void Game::updateUI() {}

auto Game::generateNoiseMenus(int width, int height) -> std::vector<MenuShPtr>
{
  std::vector<MenuShPtr> out{};
  auto noises = generateMenu(olc::vi2d{width - DEFAULT_MENU_WIDTH, 0},
                             olc::vi2d{DEFAULT_MENU_WIDTH, height},
                             "",
                             "noises",
                             false);

  auto title = generateMenu(olc::vi2d{width - DEFAULT_MENU_WIDTH, 0},
                            olc::vi2d{DEFAULT_MENU_WIDTH, height},
                            "Noises",
                            "title",
                            false);
  noises->addMenu(title);

  out.push_back(noises);
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
