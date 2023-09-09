
#pragma once

#include "PeriodicPerlinGenerator.hh"

namespace pge::terrain {

template<int Dimension>
PeriodicPerlinGenerator<Dimension>::PeriodicPerlinGenerator(const int period, const Seed seed)
  : AbstractPeriodicGradientGenerator<Dimension>(period, seed)
{}

template<int Dimension>
auto PeriodicPerlinGenerator<Dimension>::gradientAt(const int id) const noexcept -> Point3d
{
  return DEFAULT_GRADIENTS[id % DEFAULT_GRADIENTS.size()];
}

} // namespace pge::terrain
