
#include "ValueGenerator.hh"

namespace pge::lattice {

ValueGenerator::ValueGenerator(noise::INoisePtr noise)
  : m_noise(std::move(noise))
{}

auto ValueGenerator::generateFor(const utils::Vector2i &latticePoint,
                                 const utils::Vector2f & /*point*/) const noexcept -> float
{
  m_noise->seed(latticePoint.x(), latticePoint.y());
  return m_noise->at(latticePoint.x(), latticePoint.y());
}

} // namespace pge::lattice
