
#pragma once

#include "ValueGenerator.hh"

namespace pge::terrain {

template<int Dimension>
inline ValueGenerator<Dimension>::ValueGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

template<int Dimension>
inline auto ValueGenerator<Dimension>::at(const LatticePoint &latticePoint) const noexcept
  -> Point1d
{
  m_noise->seed(m_hasher->hash(latticePoint));
  return Point1d(m_noise->next());
}

template<int Dimension>
inline auto ValueGenerator<Dimension>::generateFor(const LatticePoint &latticePoint,
                                                   const Point & /*point*/) const noexcept -> float
{
  return at(latticePoint).value();
}

} // namespace pge::terrain
