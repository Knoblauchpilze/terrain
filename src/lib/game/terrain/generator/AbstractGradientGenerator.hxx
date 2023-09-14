
#pragma once

#include "AbstractGradientGenerator.hh"

#include <iostream>

namespace pge::terrain {

template<int Dimension>
inline auto AbstractGradientGenerator<Dimension>::generateFor(
  const ILatticePoint<Dimension> &latticePoint,
  const IPoint<Dimension> &point) const noexcept -> float
{
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  const auto grad = this->fromCacheOrGenerate(latticePoint);

  // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  // https://stackoverflow.com/questions/12676190/how-to-call-a-template-member-function
  const auto dist = point - latticePoint.template cast<float>();
  const auto dot  = grad.head(Dimension).dot(dist);

  return dot;
}

template<int Dimension>
inline auto AbstractGradientGenerator<Dimension>::fromCacheOrGenerate(
  const ILatticePoint<Dimension> &lp) const -> Point3d
{
  const auto key = std::make_pair(lp(0), lp(1));
  if (const auto it = m_cache.find(key); it != m_cache.end())
  {
    return it->second;
  }

  const auto grad = this->at(lp);
  m_cache[key]    = grad;
  m_keys.push_back(key);
  if (m_keys.size() > MAX_CACHE_SIZE)
  {
    m_cache.erase(m_keys.front());
    m_keys.pop_front();
  }

  return grad;
}

} // namespace pge::terrain
