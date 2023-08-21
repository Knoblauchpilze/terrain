
#include "GradientGenerator.hh"

namespace pge::lattice {

GradientGenerator::GradientGenerator(noise::INoisePtr noise)
  : m_noise(std::move(noise))
{}

auto GradientGenerator::generateFor(const utils::Vector2i &latticePoint,
                                    const utils::Vector2f &point) const noexcept -> float
{
  /// TODO: The gradient should not be completely random, see here:
  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  utils::Vector2f grad;
  m_noise->seed(latticePoint.x(), latticePoint.y());
  grad.x() = m_noise->at(latticePoint.x(), latticePoint.y());
  grad.y() = m_noise->at(latticePoint.x(), latticePoint.y());
  grad.normalize();

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto distX = point.x() - latticePoint.x();
  const auto distY = point.y() - latticePoint.y();

  const auto dot = grad.x() * distX + grad.y() * distY;

  return dot;
}

} // namespace pge::lattice
