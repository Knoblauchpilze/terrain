
#include "TerrainMode.hh"

namespace pge::terrain {

auto str(const TerrainMode &terrain) noexcept -> std::string
{
  switch (terrain)
  {
    case TerrainMode::HEIGHT:
      return "height";
    case TerrainMode::MOISTURE:
      return "moisture";
    case TerrainMode::TEMPERATURE:
      return "temperatue";
    default:
      return "unknown";
  }
}

auto nextTerrainMode(const TerrainMode mode) noexcept -> TerrainMode
{
  switch (mode)
  {
    case TerrainMode::HEIGHT:
      return TerrainMode::MOISTURE;
    case TerrainMode::MOISTURE:
      return TerrainMode::TEMPERATURE;
    case TerrainMode::TEMPERATURE:
    default:
      return TerrainMode::HEIGHT;
  }
}

auto previousTerrainMode(const TerrainMode mode) noexcept -> TerrainMode
{
  switch (mode)
  {
    case TerrainMode::HEIGHT:
      return TerrainMode::TEMPERATURE;
    case TerrainMode::MOISTURE:
      return TerrainMode::HEIGHT;
    case TerrainMode::TEMPERATURE:
    default:
      return TerrainMode::MOISTURE;
  }
}

} // namespace pge::terrain
