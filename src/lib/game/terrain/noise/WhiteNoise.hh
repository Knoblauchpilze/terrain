
#pragma once

#include "INoise.hh"
#include <random>

namespace pge::noise {

class WhiteNoise : public INoise
{
  public:
  WhiteNoise() noexcept;
  ~WhiteNoise() override = default;

  void seed(const Seed seed) override;
  auto next() const noexcept -> float override;
  auto nextRange(const float min, const float max) const noexcept -> float override;

  private:
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

} // namespace pge::noise
