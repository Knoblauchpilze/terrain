
#include "GradientGenerator.hh"

namespace pge::terrain {

GradientGenerator::GradientGenerator(IHasher2dPtr hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto GradientGenerator::at(const LatticePoint2d &latticePoint) const noexcept -> Point2d
{
  m_noise->seed(m_hasher->hash(latticePoint));

  Point2d grad;
  grad(0) = m_noise->next();
  grad(1) = m_noise->next();

  grad.normalize();

  return grad;
}

} // namespace pge::terrain
