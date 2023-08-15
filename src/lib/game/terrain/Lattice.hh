
#pragma once

#include "IInterpolator.hh"
#include "ILattice.hh"
#include "INoise.hh"
#include <memory>

namespace pge {

class Lattice : public ILattice
{
  public:
  Lattice(const noise::Seed seed) noexcept;
  ~Lattice() override = default;

  auto at(const float x, const float y) -> float override;

  private:
  noise::Seed m_seed{};
  noise::INoisePtr m_noise;
  interpolation::IInterpolatorPtr m_interpolator;

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

using LatticePtr = std::unique_ptr<Lattice>;

} // namespace pge
