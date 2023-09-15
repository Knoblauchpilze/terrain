
#pragma once

#include "AbstractCachedGenerator.hh"

#include <iostream>

namespace pge::terrain {

template<int Dimension, typename ValueType>
inline AbstractCachedGenerator<Dimension, ValueType>::AbstractCachedGenerator(const int cacheSize)

{
  if (cacheSize < 0)
  {
    throw std::invalid_argument("Expected cache size to be positive, got "
                                + std::to_string(cacheSize));
  }
  m_cacheSize = cacheSize;
}

template<int Dimension, typename ValueType>
inline auto AbstractCachedGenerator<Dimension, ValueType>::generateFor(
  const ILatticePoint<Dimension> &latticePoint,
  const IPoint<Dimension> &point) const noexcept -> float
{
  if (0u == m_cacheSize)
  {
    const auto value = this->at(latticePoint);
    return this->combine(value, point);
  }

  return this->fromCacheOrGenerate(latticePoint, point);
}

template<int Dimension, typename ValueType>
inline auto AbstractCachedGenerator<Dimension, ValueType>::fromCacheOrGenerate(
  const ILatticePoint<Dimension> &lp,
  const IPoint<Dimension> &p) const -> float
{
  /// TODO: Make key generic.
  const auto key = std::make_pair(lp(0), lp(1));
  if (const auto it = this->m_cache.find(key); it != m_cache.end())
  {
    return this->combine(it->second, p);
  }

  const auto value   = this->at(lp);
  this->m_cache[key] = value;
  this->m_keys.push_back(key);
  if (m_keys.size() > this->m_cacheSize)
  {
    this->m_cache.erase(this->m_keys.front());
    this->m_keys.pop_front();
  }

  return this->combine(value, p);
}

} // namespace pge::terrain
