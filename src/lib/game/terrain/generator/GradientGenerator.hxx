
#pragma once

#include "GradientGenerator.hh"

namespace pge::terrain {

template<int Dimension>
inline GradientGenerator<Dimension>::GradientGenerator(IHasherPtr<Dimension> hasher,
                                                       INoisePtr noise,
                                                       const int cacheSize)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{
  if (cacheSize < 0)
  {
    throw std::invalid_argument("Expected cache size to be positive, got "
                                + std::to_string(cacheSize));
  }
  m_cacheSize = cacheSize;
}

template<int Dimension>
inline auto GradientGenerator<Dimension>::at(
  const ILatticePoint<Dimension> &latticePoint) const noexcept -> Point3d
{
  const auto key = std::make_pair(latticePoint(0), latticePoint(1));
  if (this->m_cacheSize > 0)
  {
    if (const auto it = this->m_cache.find(key); it != this->m_cache.end())
    {
      return it->second;
    }
  }

  return this->generateAndRegisterInCache(latticePoint);
}

template<int Dimension>
inline auto GradientGenerator<Dimension>::generateAndRegisterInCache(
  const ILatticePoint<Dimension> &lp) const -> Point3d
{
  this->m_noise->seed(this->m_hasher->hash(lp));

  Point3d grad;
  grad(0) = this->m_noise->next();
  grad(1) = this->m_noise->next();
  grad(2) = this->m_noise->next();

  grad.normalize();

  const auto key     = std::make_pair(lp(0), lp(1));
  this->m_cache[key] = grad;
  this->m_keys.push_back(key);
  if (this->m_keys.size() > this->m_cacheSize)
  {
    this->m_cache.erase(this->m_keys.front());
    this->m_keys.pop_front();
  }

  return grad;
}

} // namespace pge::terrain
