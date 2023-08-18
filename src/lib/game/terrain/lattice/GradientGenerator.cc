
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
  const auto gradX = 2.0f * m_noise->next() - 1.0f;
  const auto gradY = 2.0f * m_noise->next() - 1.0f;

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  const auto distX = point.x() - latticePoint.x();
  const auto distY = point.y() - latticePoint.y();

  const auto dot = gradX * distX + gradY * distY;

  return 0.5f * (dot + 1.0f);
}

} // namespace pge::lattice
