
#include "Type.hh"

namespace pge::terrain {

auto str(const TerrainMode &mode) noexcept -> std::string
{
  switch (mode)
  {
    case TerrainMode::NOISE:
      return "noise";
    case TerrainMode::BIOME:
      return "biome";
    default:
      return "unknown";
  }
};

} // namespace pge::terrain
