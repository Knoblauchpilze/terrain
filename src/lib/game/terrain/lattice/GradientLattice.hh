
#pragma once

#include "IHasher.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "INoise.hh"

namespace pge::lattice {

class GradientLattice : public ILattice
{
  public:
  GradientLattice(IHasherPtr hasher,
                  noise::INoisePtr noise,
                  interpolation::IInterpolatorPtr interpolator) noexcept;
  ~GradientLattice() override = default;

  auto at(const float x, const float y) -> float override;

  private:
  IHasherPtr m_hasher;
  noise::INoisePtr m_noise;
  interpolation::IInterpolatorPtr m_interpolator;

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

} // namespace pge::lattice
