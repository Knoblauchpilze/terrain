
#include "AbstractGradientGenerator.hh"

namespace pge::terrain {

auto AbstractGradientGenerator::generateFor(const utils::Vector2i &latticePoint,
                                            const utils::Vector2f &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  const auto grad = at(latticePoint);

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto distX = point.x() - latticePoint.x();
  const auto distY = point.y() - latticePoint.y();

  const auto dot = grad.x() * distX + grad.y() * distY;

  return dot;
}

} // namespace pge::terrain
