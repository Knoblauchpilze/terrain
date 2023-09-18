
#include "Map.hh"

namespace pge::terrain {
namespace {
constexpr auto OCEAN_THRESHOLD    = 0.2f;
constexpr auto COAST_THRESHOLD    = 0.5f;
constexpr auto PLAIN_THRESHOLD    = 0.6f;
constexpr auto MOUNTAIN_THRESHOLD = 0.85f;
constexpr auto ICE_THRESHOLD      = 1.0f;

auto heightToTerrainType(const float height) noexcept -> Type
{
  if (height < OCEAN_THRESHOLD)
  {
    return Type::OCEAN;
  }
  else if (height < COAST_THRESHOLD)
  {
    return Type::COAST;
  }
  else if (height < PLAIN_THRESHOLD)
  {
    return Type::PLAIN;
  }
  else if (height < MOUNTAIN_THRESHOLD)
  {
    return Type::MOUNTAIN;
  }
  else
  {
    return Type::ICE;
  }
}

} // namespace

Map::Map() noexcept
  : utils::CoreObject("2d")
{
  setService("2d");
}

auto Map::at(const float x, const float y) const -> Type
{
  return heightToTerrainType(height(x, y));
}

auto Map::height(const float x, const float y) const -> float
{
  return m_terrain.height(x, y);
}

void Map::load(const std::string &fileName)
{
  m_terrain.load(fileName);
}

void Map::save(const std::string &fileName) const
{
  m_terrain.save(fileName);
}

auto Map::mode() const noexcept -> TerrainMode
{
  return m_mode;
}

void Map::toggleMode(bool /*prev*/)
{
  switch (m_mode)
  {
    case TerrainMode::NOISE:
      m_mode = TerrainMode::BIOME;
      break;
    case TerrainMode::BIOME:
    default:
      m_mode = TerrainMode::NOISE;
      break;
  }

  // TODO: Handle this.
}

auto Map::lattice() const noexcept -> LatticeType
{
  return m_terrain.lattice();
}

auto Map::interpolation() const noexcept -> InterpolationStrategy
{
  return m_terrain.interpolation();
}

auto Map::scale() const noexcept -> int
{
  return m_terrain.scale();
}

auto Map::period() const noexcept -> int
{
  return m_terrain.period();
}

auto Map::cacheSize() const noexcept -> int
{
  return m_terrain.cacheSize();
}

auto Map::seed() const noexcept -> Seed
{
  return m_terrain.seed();
}

void Map::nextLattice(bool prev)
{
  m_terrain.nextLattice(prev);
}

void Map::nextInterpolation(bool prev)
{
  m_terrain.nextInterpolation(prev);
}

void Map::nextScale(bool prev)
{
  m_terrain.nextScale(prev);
}

void Map::nextPeriod(bool prev)
{
  m_terrain.nextPeriod(prev);
}

void Map::nextCacheSize(bool prev)
{
  m_terrain.nextCacheSize(prev);
}

void Map::nextSeed()
{
  m_terrain.nextSeed();
}

auto Map::layersCount() const noexcept -> int
{
  return m_terrain.layersCount();
}

auto Map::lacunarity() const noexcept -> int
{
  return m_terrain.lacunarity();
}

auto Map::gain() const noexcept -> float
{
  return m_terrain.gain();
}

void Map::nextLayersCount(bool prev) noexcept
{
  m_terrain.nextLayersCount(prev);
}

void Map::nextLacunarity(bool prev) noexcept
{
  m_terrain.nextLacunarity(prev);
}

void Map::nextGain(bool prev) noexcept
{
  m_terrain.nextGain(prev);
}

} // namespace pge::terrain
