
#include "Map.hh"

namespace pge::terrain {
namespace {
constexpr auto OCEAN_THRESHOLD    = 0.2f;
constexpr auto COAST_THRESHOLD    = 0.5f;
constexpr auto PLAIN_THRESHOLD    = 0.6f;
constexpr auto MOUNTAIN_THRESHOLD = 0.85f;

auto noiseToTerrainType(const float height, const float moisture, const float temperature) noexcept
  -> Type
{
  /// https://gamedev.stackexchange.com/questions/178084/map-generation-biome-3d-zonation-altitude-temperature-moisture
  if (height < 0.1f)
  {
    return Type::ABYSS;
  }
  else if (height < 0.2f)
  {
    return Type::OCEAN;
  }
  else if (height < 0.45f)
  {
    if (temperature < 0.5f)
    {
      return Type::ICE;
    }
    else
    {
      return Type::SEA;
    }
  }
  else if (height < 0.55f)
  {
    if (temperature < 0.5f)
    {
      return Type::ICE_PACK;
    }
    else
    {
      return Type::COAST;
    }
  }
  else if (height < 0.70f)
  {
    if (temperature < 0.5f)
    {
      if (moisture < 0.5f)
      {
        return Type::TOUNDRA;
      }
      else
      {
        return Type::TAIGA;
      }
    }
    else
    {
      if (moisture < 0.3f)
      {
        return Type::DESERT;
      }
      else if (moisture < 0.6f)
      {
        return Type::PLAIN;
      }
      else
      {
        return Type::FOREST;
      }
    }
  }
  else if (height < 0.90f)
  {
    if (moisture < 0.5f)
    {
      return Type::MOUNTAIN;
    }
    else
    {
      return Type::ROCKS;
    }
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
  auto terrain                    = std::make_unique<Terrain>();
  m_terrains[TerrainMode::HEIGHT] = std::move(terrain);

  terrain = std::make_unique<Terrain>();
  terrain->nextSeed();
  terrain->nextSeed();
  m_terrains[TerrainMode::MOISTURE] = std::move(terrain);

  terrain = std::make_unique<Terrain>();
  terrain->nextSeed();
  terrain->nextSeed();
  terrain->nextSeed();
  terrain->nextSeed();
  m_terrains[TerrainMode::TEMPERATURE] = std::move(terrain);
}

auto Map::at(const float x, const float y) const -> Type
{
  const auto h     = m_terrains.at(TerrainMode::HEIGHT)->height(x, y);
  const auto moist = m_terrains.at(TerrainMode::MOISTURE)->height(x, y);
  const auto temp  = m_terrains.at(TerrainMode::TEMPERATURE)->height(x, y);

  return noiseToTerrainType(h, moist, temp);
}

auto Map::height(const float x, const float y) const -> float
{
  return m_terrains.at(m_mode)->height(x, y);
}

void Map::load(const std::string &fileName)
{
  warn("Should load from \"" + fileName + "\"");
}

void Map::save(const std::string &fileName) const
{
  warn("Should save to \"" + fileName + "\"");
}

auto Map::terrain() const noexcept -> TerrainMode
{
  return m_mode;
}

void Map::nextTerrain(bool prev) noexcept
{
  if (prev)
  {
    m_mode = previousTerrainMode(m_mode);
  }
  else
  {
    m_mode = nextTerrainMode(m_mode);
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
  return *m_terrains.at(TerrainMode::HEIGHT);
}

void Map::applyToTerrain(const TerrainProcess &process)
{
  for (auto &terrain : m_terrains)
  {
    process(*(terrain.second));
  }
}

} // namespace pge::terrain
