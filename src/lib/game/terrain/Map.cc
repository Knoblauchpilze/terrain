
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
  m_terrains[HEIGHT]      = std::make_unique<Terrain>();
  m_terrains[MOISTURE]    = std::make_unique<Terrain>();
  m_terrains[TEMPERATURE] = std::make_unique<Terrain>();
}

auto Map::at(const float x, const float y) const -> Type
{
  return heightToTerrainType(height(x, y));
}

auto Map::height(const float x, const float y) const -> float
{
  /// TODO: Handle this.
  return defaultTerrain().height(x, y);
}

void Map::load(const std::string &fileName)
{
  warn("Should load from \"" + fileName + "\"");
}

void Map::save(const std::string &fileName) const
{
  warn("Should save to \"" + fileName + "\"");
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
}

auto Map::lattice() const noexcept -> LatticeType
{
  return defaultTerrain().lattice();
}

auto Map::interpolation() const noexcept -> InterpolationStrategy
{
  return defaultTerrain().interpolation();
}

auto Map::scale() const noexcept -> int
{
  return defaultTerrain().scale();
}

auto Map::period() const noexcept -> int
{
  return defaultTerrain().period();
}

auto Map::cacheSize() const noexcept -> int
{
  return defaultTerrain().cacheSize();
}

auto Map::seed() const noexcept -> Seed
{
  return defaultTerrain().seed();
}

void Map::nextLattice(bool prev)
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextLattice(prev); });
}

void Map::nextInterpolation(bool prev)
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextInterpolation(prev); });
}

void Map::nextScale(bool prev)
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextScale(prev); });
}

void Map::nextPeriod(bool prev)
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextPeriod(prev); });
}

void Map::nextCacheSize(bool prev)
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextCacheSize(prev); });
}

void Map::nextSeed()
{
  applyToTerrain([](Terrain &terrain) { terrain.nextSeed(); });
}

auto Map::layersCount() const noexcept -> int
{
  return defaultTerrain().layersCount();
}

auto Map::lacunarity() const noexcept -> int
{
  return defaultTerrain().lacunarity();
}

auto Map::gain() const noexcept -> float
{
  return defaultTerrain().gain();
}

void Map::nextLayersCount(bool prev) noexcept
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextLayersCount(prev); });
}

void Map::nextLacunarity(bool prev) noexcept
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextLacunarity(prev); });
}

void Map::nextGain(bool prev) noexcept
{
  applyToTerrain([prev](Terrain &terrain) { terrain.nextGain(prev); });
}

auto Map::defaultTerrain() const noexcept -> const Terrain &
{
  return *m_terrains.at(HEIGHT);
}

void Map::applyToTerrain(const TerrainProcess &process)
{
  for (auto &terrain : m_terrains)
  {
    process(*(terrain.second));
  }
}

} // namespace pge::terrain
