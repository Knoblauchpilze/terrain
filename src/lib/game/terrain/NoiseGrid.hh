
#pragma once

#include "INoise.hh"
#include "Interpolator.hh"
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
  interpolation::Interpolator m_interpolator{interpolation::Algorithm::BILINEAR};

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

using NoiseGridPtr = std::unique_ptr<NoiseGrid>;

} // namespace pge::noise
