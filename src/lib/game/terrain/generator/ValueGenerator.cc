
#include "ValueGenerator.hh"

namespace pge::terrain {

ValueGenerator::ValueGenerator(IHasher2dPtr hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto ValueGenerator::at(const utils::Vector2i &latticePoint) const noexcept -> float
{
  m_noise->seed(m_hasher->hash(LatticePoint2d(latticePoint.x(), latticePoint.y())));
  return m_noise->next();
}

auto ValueGenerator::generateFor(const utils::Vector2i &latticePoint,
                                 const utils::Vector2f & /*point*/) const noexcept -> float
{
  return at(latticePoint);
}

} // namespace pge::terrain
