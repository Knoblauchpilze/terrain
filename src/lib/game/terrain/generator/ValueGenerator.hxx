
#pragma once
#include "ValueGenerator.hh"

namespace pge::terrain {

template<int Dimension>
inline ValueGenerator<Dimension>::ValueGenerator(IHasherPtr<Dimension> hasher,
                                                 INoisePtr noise,
                                                 const int cacheSize)
  : AbstractCachedGenerator<Dimension, float>(cacheSize)
  , m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

template<int Dimension>
inline auto ValueGenerator<Dimension>::at(const ILatticePoint<Dimension> &latticePoint) const noexcept
  -> float
{
  m_noise->seed(m_hasher->hash(latticePoint));
  return m_noise->next();
}

template<int Dimension>
inline auto ValueGenerator<Dimension>::combine(const float &latticeValue,
                                               const IPoint<Dimension> & /*point*/) const noexcept
  -> float
{
  return latticeValue;
}

} // namespace pge::terrain
