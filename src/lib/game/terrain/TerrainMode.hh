
#pragma once

#include <string>

namespace pge::terrain {

enum class TerrainMode
{
  HEIGHT,
  MOISTURE,
  TEMPERATURE
};

auto str(const TerrainMode &terrain) noexcept -> std::string;
auto nextTerrainMode(const TerrainMode mode) noexcept -> TerrainMode;
auto previousTerrainMode(const TerrainMode mode) noexcept -> TerrainMode;

} // namespace pge::terrain
