
#pragma once

#include "AbstractGradientGenerator.hh"

#include <iostream>

namespace pge::terrain {

template<int Dimension>
inline auto AbstractGradientGenerator<Dimension>::generateFor(
  const ILatticePoint<Dimension> &latticePoint,
  const IPoint<Dimension> &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  const auto grad = this->at(latticePoint);

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  // https://stackoverflow.com/questions/12676190/how-to-call-a-template-member-function
  const auto dist = point - latticePoint.template cast<float>();
  const auto dot  = grad.head(Dimension).dot(dist);

  return dot;
}

} // namespace pge::terrain
