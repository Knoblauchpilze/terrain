
#include "GradientGenerator.hh"

namespace pge::terrain {

GradientGenerator::GradientGenerator(IHasher2dPtr hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto GradientGenerator::at(const LatticePoint2d &latticePoint) const noexcept -> Point2d
{
  /// TODO: Should be dynamic based on how many values need to be hashed.
  m_noise->seed(m_hasher->hash(latticePoint));

  // https://eigen.tuxfamily.org/dox/group__TutorialAdvancedInitialization.html
  Point2d grad;
  std::generate(grad.begin(), grad.end(), [this]() { return m_noise->next(); });

  /// TODO: Should maybe not be normalized.
  grad.normalize();

  return grad;
}

} // namespace pge::terrain
