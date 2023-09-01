
#include "AbstractGradientGenerator.hh"

namespace pge::terrain {

auto AbstractGradientGenerator::generateFor(const LatticePoint2d &latticePoint,
                                            const Point2d &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  const auto grad = at(latticePoint);

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto distX = point(0) - latticePoint(0);
  const auto distY = point(1) - latticePoint(1);

  const auto dot = grad(0) * distX + grad(1) * distY;

  return dot;
}

} // namespace pge::terrain
