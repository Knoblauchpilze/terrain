
#pragma once

#include "IInterpolator.hh"
#include "INoise.hh"
#include <memory>

namespace pge {

class Lattice
{
  public:
  Lattice(const noise::Seed seed) noexcept;
  ~Lattice() = default;

  void seed(const noise::Seed seed);
  auto at(const float x, const float y) -> float;

  private:
  noise::Seed m_seed{};
  noise::INoisePtr m_noise;
  interpolation::IInterpolatorPtr m_interpolator;

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

using LatticePtr = std::unique_ptr<Lattice>;

} // namespace pge
