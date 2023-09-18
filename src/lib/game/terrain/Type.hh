
#pragma once

#include <string>

namespace pge::terrain {

enum class Type
{
  OCEAN,
  COAST,
  PLAIN,
  MOUNTAIN,
  ICE
};

enum class TerrainMode
{
  NOISE,
  BIOME
};

auto str(const TerrainMode &mode) noexcept -> std::string;

} // namespace pge::terrain
