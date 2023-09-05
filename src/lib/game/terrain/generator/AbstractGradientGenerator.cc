
#include "AbstractGradientGenerator.hh"

namespace pge::terrain {

auto AbstractGradientGenerator::generateFor(const LatticePoint2d &latticePoint,
                                            const Point2d &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  const auto grad = at(latticePoint);

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto dist = point - latticePoint.cast<float>();
  const auto dot  = grad.head(2).dot(dist);

  return dot;
}

} // namespace pge::terrain
