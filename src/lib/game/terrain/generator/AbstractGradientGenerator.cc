
#include "AbstractGradientGenerator.hh"

namespace pge::terrain {

auto AbstractGradientGenerator::generateFor(const LatticePoint2d &latticePoint,
                                            const Point2d &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  const Point2d grad = this->at(latticePoint);

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  // https://stackoverflow.com/questions/31131116/vector2f-to-vector2d-explicit-type-conversion-eigen
  const Point2d dist = point - latticePoint.cast<float>();
  // https://eigen.tuxfamily.org/dox/classEigen_1_1MatrixBase.html#adfd32bf5fcf6ee603c924dde9bf7bc39
  const float dot = grad.dot(dist);

  return dot;
}

} // namespace pge::terrain
