
#pragma once

#include "IInterpolator.hh"
#include "ILattice.hh"
#include "INoise.hh"
#include <memory>

namespace pge::lattice {

class ValueLattice : public ILattice
{
  public:
  ValueLattice(const noise::Seed seed) noexcept;
  ~ValueLattice() override = default;

  auto at(const float x, const float y) -> float override;

  private:
  noise::Seed m_seed{};
  noise::INoisePtr m_noise;
  interpolation::IInterpolatorPtr m_interpolator;

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

} // namespace pge::lattice
