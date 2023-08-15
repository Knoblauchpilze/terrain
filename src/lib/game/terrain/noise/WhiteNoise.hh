
#pragma once

#include "Noise2d.hh"
#include <random>

namespace pge::noise {

class WhiteNoise : public Noise2d
{
  public:
  WhiteNoise(const Seed seed);
  ~WhiteNoise() override = default;

  auto next() const noexcept -> float override;

  protected:
  void seed(const Seed seed) override;

  private:
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

} // namespace pge::noise
