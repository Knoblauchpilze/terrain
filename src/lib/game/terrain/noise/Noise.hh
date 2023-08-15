
#pragma once

#include "INoise.hh"
#include <random>

namespace pge::noise {

class Noise : public INoise
{
  public:
  Noise() noexcept;
  ~Noise() override = default;

  void seed(const Seed seed) override;
  auto next() const noexcept -> float override;

  private:
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

} // namespace pge::noise
