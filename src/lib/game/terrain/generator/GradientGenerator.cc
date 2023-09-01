
#include "GradientGenerator.hh"

namespace pge::terrain {

GradientGenerator::GradientGenerator(IHasher2dPtr hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto GradientGenerator::at(const LatticePoint2d &latticePoint) const noexcept -> utils::Vector2f
{
  utils::Vector2f grad;
  m_noise->seed(m_hasher->hash(latticePoint));
  grad.x() = m_noise->next();
  grad.y() = m_noise->next();

  grad.normalize();

  return grad;
}

} // namespace pge::terrain
