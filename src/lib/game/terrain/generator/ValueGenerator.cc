
#include "ValueGenerator.hh"

namespace pge::lattice {

ValueGenerator::ValueGenerator(IHasherPtr hasher, noise::INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto ValueGenerator::at(const utils::Vector2i &latticePoint) const noexcept -> float
{
  m_noise->seed(m_hasher->hash(latticePoint.x(), latticePoint.y()));
  return m_noise->next();
}

auto ValueGenerator::generateFor(const utils::Vector2i &latticePoint,
                                 const utils::Vector2f & /*point*/) const noexcept -> float
{
  return at(latticePoint);
}

} // namespace pge::lattice
