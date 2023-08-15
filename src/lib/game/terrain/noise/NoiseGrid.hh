
#pragma once

#include "Interpolator.hh"
#include "Noise.hh"
#include <memory>

namespace pge::noise {

class NoiseGrid
{
  public:
  NoiseGrid(const Noise::Seed seed) noexcept;
  ~NoiseGrid() = default;

  void seed(const Noise::Seed seed);
  auto at(const float x, const float y) -> float;

  private:
  Noise::Seed m_seed{};
  NoisePtr m_noise;
  interpolation::Interpolator m_interpolator{interpolation::Algorithm::BILINEAR};

  auto generateLatticePointsAndInterpolate(const float x, const float y) -> float;
};

using NoiseGridPtr = std::unique_ptr<NoiseGrid>;

} // namespace pge::noise
