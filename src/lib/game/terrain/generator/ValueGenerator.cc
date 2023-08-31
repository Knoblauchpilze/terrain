
#include "ValueGenerator.hh"

namespace pge::terrain {

ValueGenerator::ValueGenerator(IHasher2dPtr hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto ValueGenerator::at(const LatticePoint2d &latticePoint) const noexcept -> Point1d
{
  m_noise->seed(m_hasher->hash(latticePoint));
  return Point1d(m_noise->next());
}

auto ValueGenerator::generateFor(const LatticePoint2d &latticePoint,
                                 const Point2d & /*point*/) const noexcept -> float
{
  return at(latticePoint).value();
}

} // namespace pge::terrain
