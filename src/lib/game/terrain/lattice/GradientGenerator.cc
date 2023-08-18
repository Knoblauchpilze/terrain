
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
  const auto gradX = m_noise->next();
  const auto gradY = m_noise->next();

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto distX = point.x() - latticePoint.x();
  const auto distY = point.y() - latticePoint.y();

  const auto dot = gradX * distX + gradY * distY;

  return dot;
}

} // namespace pge::lattice