
#pragma once
#include "ValueGenerator.hh"

namespace pge::terrain {

template<int Dimension>
inline ValueGenerator<Dimension>::ValueGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise)
  : m_hasher(std::move(hasher))
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
inline auto ValueGenerator<Dimension>::generateFor(const ILatticePoint<Dimension> &latticePoint,
                                                   const IPoint<Dimension> & /*point*/) const noexcept
  -> float
{
  return this->fromCacheOrGenerate(latticePoint);
}

template<int Dimension>
inline auto ValueGenerator<Dimension>::fromCacheOrGenerate(const ILatticePoint<Dimension> &lp) const
  -> float
{
  const auto key = std::make_pair(lp(0), lp(1));
  if (const auto it = m_cache.find(key); it != m_cache.end())
  {
    return it->second;
  }

  const auto value = this->at(lp);
  m_cache[key]     = value;
  m_keys.push_back(key);
  if (m_keys.size() > MAX_CACHE_SIZE)
  {
    m_cache.erase(m_keys.front());
    m_keys.pop_front();
  }

  return value;
}

} // namespace pge::terrain
