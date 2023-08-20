
#include "GradientGenerator.hh"

namespace pge::lattice {

GradientGenerator::GradientGenerator(IHasherPtr hasher, noise::INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto GradientGenerator::generateFor(const utils::Vector2i &latticePoint,
                                    const utils::Vector2f &point) const noexcept -> float
{
  m_noise->seed(m_hasher->hash(latticePoint.x(), latticePoint.y()));
  /// TODO: The gradient should not be completely random, see here:
  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  utils::Vector2f grad;
  grad.x() = m_noise->nextRange(-1.0f, 1.0f);
  grad.y() = m_noise->nextRange(-1.0f, 1.0f);
  grad.normalize();

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto distX = point.x() - latticePoint.x();
  const auto distY = point.y() - latticePoint.y();

  const auto dot = grad.x() * distX + grad.y() * distY;

  return dot;
}

} // namespace pge::lattice
