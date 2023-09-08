
#include "ValueGenerator.hh"

namespace pge::terrain {

ValueGenerator::ValueGenerator(IHasher3dPtr hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto ValueGenerator::at(const LatticePoint3d &latticePoint) const noexcept -> float
{
  m_noise->seed(m_hasher->hash(latticePoint));
  return m_noise->next();
}

auto ValueGenerator::generateFor(const LatticePoint3d &latticePoint,
                                 const Point3d & /*point*/) const noexcept -> float
{
  return at(latticePoint);
}

} // namespace pge::terrain
