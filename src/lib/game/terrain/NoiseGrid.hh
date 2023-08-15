
#pragma once

#include "IInterpolator.hh"
#include "INoise.hh"
#include <memory>

namespace pge::noise {

class NoiseGrid
{
  public:
  NoiseGrid(const Seed seed) noexcept;
  ~NoiseGrid() = default;

  void seed(const Seed seed);
  auto at(const float x, const float y) -> float;

  private:
  Seed m_seed{};
  INoisePtr m_noise;
  interpolation::IInterpolatorPtr m_interpolator;

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

using NoiseGridPtr = std::unique_ptr<NoiseGrid>;

} // namespace pge::noise
