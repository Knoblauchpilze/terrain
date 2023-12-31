
#include "App.hh"
#include "Type.hh"

namespace pge {

const auto CURSOR_COLOR = olc::Pixel{255, 255, 0, alpha::SemiOpaque};

namespace {
auto colorFromTerrain(const terrain::Type &terrain) noexcept -> olc::Pixel
{
  switch (terrain)
  {
    case terrain::Type::ABYSS:
      return olc::VERY_DARK_BLUE;
    case terrain::Type::OCEAN:
      return olc::DARK_BLUE;
    case terrain::Type::SEA:
      return olc::COBALT_BLUE;
    case terrain::Type::COAST:
      return olc::BIDOOF;
    case terrain::Type::ICE_PACK:
      return olc::CORNFLOWER_BLUE;
    case terrain::Type::PLAIN:
      return olc::APPLE_GREEN;
    case terrain::Type::TOUNDRA:
      return olc::PALE_GREEN;
    case terrain::Type::FOREST:
      return olc::VERY_DARK_GREEN;
    case terrain::Type::TAIGA:
      return olc::PALE_DARK_GREEN;
    case terrain::Type::DESERT:
      return olc::PALE_YELLOW;
    case terrain::Type::MOUNTAIN:
      return olc::BROWN;
    case terrain::Type::ROCKS:
      return olc::GREY;
    case terrain::Type::ICE:
      return olc::OFF_WHITE;
    default:
      return olc::RED;
  }
}

auto colorFromHeight(const float height) noexcept -> olc::Pixel
{
  const auto c = static_cast<unsigned>(
    std::max(0.0f, std::min(255.0f, std::round(255.0f * height))));
  return olc::Pixel(c, c, c);
}
} // namespace

App::App(const AppDesc &desc)
  : PGEApp(desc)
  , m_game(nullptr)
  , m_state(nullptr)
  , m_menus()
  , m_packs(std::make_shared<sprites::TexturePack>())
{}

bool App::onFrame(float fElapsed)
{
  // Handle case where no game is defined.
  if (m_game == nullptr)
  {
    return false;
  }

  if (!m_game->step(fElapsed))
  {
    info("This is game over");
  }

  return m_game->terminated();
}

void App::onInputs(const controls::State &c, const CoordinateFrame &cf)
{
  // Handle case where no game is defined.
  if (m_game == nullptr)
  {
    return;
  }

  // Handle menus update and process the
  // corresponding actions.
  std::vector<ActionShPtr> actions;
  bool relevant = false;

  for (unsigned id = 0u; id < m_menus.size(); ++id)
  {
    menu::InputHandle ih = m_menus[id]->processUserInput(c, actions);
    relevant             = (relevant || ih.relevant);
  }

  if (m_state != nullptr)
  {
    menu::InputHandle ih = m_state->processUserInput(c, actions);
    relevant             = (relevant || ih.relevant);
  }

  for (unsigned id = 0u; id < actions.size(); ++id)
  {
    actions[id]->apply(*m_game);
  }

  bool lClick = (c.buttons[controls::mouse::Left] == controls::ButtonState::Released);
  if (lClick && !relevant)
  {
    olc::vf2d it;
    olc::vi2d tp = cf.pixelsToTilesAndIntra(olc::vi2d(c.mPosX, c.mPosY), &it);

    m_game->performAction(tp.x + it.x, tp.y + it.y);
  }

  if (c.keys[controls::keys::P])
  {
    m_game->togglePause();
  }
  if (m_state->getScreen() == Screen::Game)
  {
    if (c.keys[controls::keys::S])
    {
      m_state->save();
    }
    if (c.keys[controls::keys::G])
    {
      m_game->toggleNextSeed();
    }
    if (c.keys[controls::keys::M])
    {
      m_game->toggleDisplayMode(c.shift);
    }
    if (c.keys[controls::keys::L])
    {
      m_game->toggleLatticeMode(c.shift);
    }
    if (c.keys[controls::keys::C])
    {
      m_game->toggleCacheSize(c.shift);
    }
    if (c.keys[controls::keys::I])
    {
      m_game->toggleInterpolationMode(c.shift);
    }
    if (c.keys[controls::keys::O])
    {
      m_game->toggleTerrainLayer(c.shift);
    }
    if (c.keys[controls::keys::F])
    {
      m_game->toggleTerrainLacunarity(c.shift);
    }
    if (c.keys[controls::keys::A])
    {
      m_game->toggleTerrainGain(c.shift);
    }
    if (c.keys[controls::keys::T])
    {
      m_game->toggleTerrainMode(c.shift);
    }
  }
}

void App::loadData()
{
  // Create the game and its state.
  m_game = std::make_shared<Game>();
}

void App::loadResources()
{
  // Assign a specific tint to the regular drawing layer so that we have a built
  // in transparency.
  // We can't do it directly when drawing in the rendering function because as the
  // whole layer will be drawn as one quad in opengl with an opaque alpha, we will
  // lose this info.
  // This means that everything is indeed transparent but that's the only way for
  // now to achieve it.
  setLayerTint(Layer::Draw, olc::Pixel(255, 255, 255, alpha::SemiOpaque));
}

void App::loadMenuResources()
{
  // Generate the game state.
  m_state = std::make_shared<GameState>(olc::vi2d(ScreenWidth(), ScreenHeight()),
                                        Screen::Game,
                                        *m_game);
  m_game->togglePause();

  m_menus = m_game->generateMenus(ScreenWidth(), ScreenHeight());
}

void App::cleanResources()
{
  if (m_packs != nullptr)
  {
    m_packs.reset();
  }
}

void App::cleanMenuResources()
{
  m_menus.clear();
}

void App::drawDecal(const RenderDesc &res)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::VERY_DARK_GREY);

  // In case we're not in the game screen, do nothing.
  if (m_state->getScreen() != Screen::Game)
  {
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  renderTerrain(res.cf);
  if (hasCursor())
  {
    renderCursor(res);
  }

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::draw(const RenderDesc & /*res*/)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::Pixel(255, 255, 255, alpha::Transparent));

  // In case we're not in game mode, just render the state.
  if (m_state->getScreen() != Screen::Game)
  {
    m_state->render(this);
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::drawUI(const RenderDesc & /*res*/)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::Pixel(255, 255, 255, alpha::Transparent));

  // In case we're not in game mode, just render the state.
  if (m_state->getScreen() != Screen::Game)
  {
    m_state->render(this);
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  // Render the game menus.
  for (unsigned id = 0u; id < m_menus.size(); ++id)
  {
    m_menus[id]->render(this);
  }

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::drawDebug(const RenderDesc &res)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::Pixel(255, 255, 255, alpha::Transparent));

  // In case we're not in game mode, just render the state.
  if (m_state->getScreen() != Screen::Game)
  {
    m_state->render(this);
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  renderLattice(res.cf);

  // Draw cursor's position.
  olc::vi2d mp = GetMousePos();
  olc::vf2d it;
  olc::vi2d mtp = res.cf.pixelsToTilesAndIntra(mp, &it);

  int h       = GetDrawTargetHeight();
  int dOffset = 15;
  DrawString(olc::vi2d(0, h / 2), "Mouse coords      : " + mp.str(), olc::CYAN);
  DrawString(olc::vi2d(0, h / 2 + 1 * dOffset), "World cell coords : " + mtp.str(), olc::CYAN);
  DrawString(olc::vi2d(0, h / 2 + 2 * dOffset), "Intra cell        : " + it.str(), olc::CYAN);

  const auto &map = m_game->map();
  const olc::vf2d pTile(mtp.x + it.x, mtp.y + it.y);
  DrawString(olc::vi2d(0, h / 2 + 3 * dOffset),
             "Height            : " + std::to_string(map.height(pTile.x, pTile.y)),
             olc::CYAN);

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::renderCursor(const RenderDesc &res)
{
  olc::vf2d it;
  const auto mouseTilePosition = res.cf.pixelsToTilesAndIntra(GetMousePos(), &it);

  SpriteDesc s;
  s.radius      = 1.0f;
  s.x           = mouseTilePosition.x;
  s.y           = mouseTilePosition.y;
  s.sprite.tint = CURSOR_COLOR;
  drawWarpedRect(s, res.cf);
}

inline void App::drawSprite(const SpriteDesc &t, const CoordinateFrame &cf)
{
  olc::vf2d p = cf.tilesToPixels(t.x, t.y);

  m_packs->draw(this, t.sprite, p, t.radius * cf.tileSize());
}

inline void App::drawWarpedSprite(const SpriteDesc &t, const CoordinateFrame &cf)
{
  auto p0 = cf.tilesToPixels(t.x, t.y + t.radius);
  auto p1 = cf.tilesToPixels(t.x, t.y);
  auto p2 = cf.tilesToPixels(t.x + t.radius, t.y);
  auto p3 = cf.tilesToPixels(t.x + t.radius, t.y + t.radius);

  auto p = std::array<olc::vf2d, 4>{p0, p1, p2, p3};
  m_packs->draw(this, t.sprite, p);
}

inline void App::drawRect(const SpriteDesc &t, const CoordinateFrame &cf)
{
  olc::vf2d p = cf.tilesToPixels(t.x, t.y);
  FillRectDecal(p, t.radius * cf.tileSize(), t.sprite.tint);
}

inline void App::drawWarpedRect(const SpriteDesc &t, const CoordinateFrame &cf)
{
  auto p0 = cf.tilesToPixels(t.x, t.y + t.radius);
  auto p1 = cf.tilesToPixels(t.x, t.y);
  auto p2 = cf.tilesToPixels(t.x + t.radius, t.y);
  auto p3 = cf.tilesToPixels(t.x + t.radius, t.y + t.radius);

  // See: FillRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel col)
  // in the pixel game engine file.
  auto p = std::array<olc::vf2d, 4>{p0, p1, p2, p3};
  std::array<olc::vf2d, 4> uvs;
  uvs.fill({0, 0});

  std::array<olc::Pixel, 4> colors;
  colors.fill(t.sprite.tint);

  DrawExplicitDecal(nullptr, p.data(), uvs.data(), colors.data());
}

inline void App::renderTerrain(const CoordinateFrame &cf)
{
  const auto &map = m_game->map();

  const auto vp     = cf.tilesViewport();
  const auto center = vp.center();
  const auto dims   = vp.dims();

  const auto xMin = static_cast<int>(std::floor(center.x - dims.x / 2.0f));
  const auto xMax = static_cast<int>(std::ceil(center.x + dims.x / 2.0f));
  const auto yMin = static_cast<int>(std::floor(center.y - dims.y / 2.0f));
  const auto yMax = static_cast<int>(std::ceil(center.y + dims.y / 2.0f));

  for (auto y = yMin; y <= yMax; ++y)
  {
    for (auto x = xMin; x <= xMax; ++x)
    {
      SpriteDesc sp;
      sp.x      = 1.0f * x;
      sp.y      = 1.0f * y + 1.0f;
      sp.radius = 1.0f;
      if (DisplayMode::HEIGHT == m_game->displayMode())
      {
        sp.sprite.tint = colorFromHeight(map.height(x, y));
      }
      else
      {
        sp.sprite.tint = colorFromTerrain(map.at(x, y));
      }

      drawRect(sp, cf);
    }
  }
}

inline void App::renderLattice(const CoordinateFrame &cf)
{
  const auto scale = m_game->map().scale();

  const auto vp     = cf.tilesViewport();
  const auto center = vp.center();
  const auto dims   = vp.dims();

  auto xMin       = static_cast<int>(std::floor(center.x - dims.x / 2.0f));
  const auto xMax = static_cast<int>(std::ceil(center.x + dims.x / 2.0f));
  auto yMin       = static_cast<int>(std::floor(center.y - dims.y / 2.0f));
  const auto yMax = static_cast<int>(std::ceil(center.y + dims.y / 2.0f));

  xMin -= (xMin % scale);
  yMin -= (yMin % scale);

  for (auto y = yMin; y <= yMax; y += scale)
  {
    for (auto x = xMin; x <= xMax; x += scale)
    {
      const auto values = m_game->latticeAt(x, y);
      const auto center = cf.tilesToPixels(x + 0.5f, y + 0.5f);

      if (1 == values.size())
      {
        const auto str  = std::to_string(values[0]);
        const auto size = GetTextSize(str);
        const auto sPos = center - size / 2.0f;
        DrawString(sPos, str, olc::DARK_RED);
      }
      else if (3 == values.size())
      {
        // y
        auto str  = std::to_string(values[1]);
        auto size = GetTextSize(str);
        auto sPos = center - size / 2.0f;
        DrawString(sPos, str, olc::DARK_GREEN);

        const olc::vi2d refSize{0, size.y};

        // x
        str  = std::to_string(values[0]);
        size = GetTextSize(str);
        sPos = center - refSize - size / 2.0f;
        DrawString(sPos, str, olc::DARK_RED);

        // z
        str  = std::to_string(values[2]);
        size = GetTextSize(str);
        sPos = center + refSize - olc::vi2d{size.x / 2, 0};
        DrawString(sPos, str, olc::DARK_BLUE);
      }
    }
  }
}

} // namespace pge
