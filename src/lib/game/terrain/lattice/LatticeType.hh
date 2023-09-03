
#pragma once

#include <string>

namespace pge::terrain {

/// @brief - The type of lattice to use for terrain generation.
enum class LatticeType
{
  VALUE,
  GRADIENT,
  PERIODIC_GRADIENT,
  PERIODIC_PERLIN,
};

auto str(const LatticeType type) noexcept -> std::string;
auto nextLatticeType(const LatticeType type) noexcept -> LatticeType;

} // namespace pge::terrain
