
#include "GradientGenerator.hh"

namespace pge::lattice {

GradientGenerator::GradientGenerator(IHasherPtr hasher, noise::INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto GradientGenerator::at(const utils::Vector2i &latticePoint) const noexcept -> utils::Vector2f
{
  utils::Vector2f grad;
  m_noise->seed(m_hasher->hash(latticePoint.x(), latticePoint.y()));
  grad.x() = m_noise->next();
  grad.y() = m_noise->next();

  grad.normalize();

  return grad;
}

} // namespace pge::lattice
