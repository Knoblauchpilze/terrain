
#pragma once

#include "GradientGenerator.hh"

namespace pge::terrain {

template<int Dimension>
inline GradientGenerator<Dimension>::GradientGenerator(IHasherPtr<Dimension> hasher,
                                                       INoisePtr noise,
                                                       const int cacheSize)
  : AbstractGradientGenerator<Dimension>(cacheSize)
  , m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

template<int Dimension>
inline auto GradientGenerator<Dimension>::at(
  const ILatticePoint<Dimension> &latticePoint) const noexcept -> Point3d
{
  m_noise->seed(m_hasher->hash(latticePoint));

  Point3d grad;
  grad(0) = m_noise->next();
  grad(1) = m_noise->next();
  grad(2) = m_noise->next();

  grad.normalize();

  return grad;
}

} // namespace pge::terrain
