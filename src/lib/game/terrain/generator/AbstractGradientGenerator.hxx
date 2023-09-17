
#pragma once

#include "AbstractGradientGenerator.hh"

namespace pge::terrain {

template<int PointDimension, int GradientDimension>
inline AbstractGradientGenerator<PointDimension, GradientDimension>::AbstractGradientGenerator(
  const int cacheSize)
  : AbstractCachedGenerator<PointDimension, IPoint<GradientDimension>>(cacheSize)
{}

template<int PointDimension, int GradientDimension>
inline auto AbstractGradientGenerator<PointDimension, GradientDimension>::combine(
  const ILatticePoint<PointDimension> &latticePoint,
  const IPoint<GradientDimension> &latticeValue,
  const IPoint<PointDimension> &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  // https://stackoverflow.com/questions/12676190/how-to-call-a-template-member-function
  const auto dist = point - latticePoint.template cast<float>();
  const auto dot  = latticeValue.head(PointDimension).dot(dist);

  return dot;
}

} // namespace pge::terrain
