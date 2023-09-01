
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include <random>

namespace pge::terrain {

class WhiteNoise : public INoise
{
  public:
  WhiteNoise() noexcept;
  WhiteNoise(const float min, const float max) noexcept;
  ~WhiteNoise() override = default;

  void seed(const Seed seed) override;
  auto next() const noexcept -> float override;

  private:
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

} // namespace pge::terrain
