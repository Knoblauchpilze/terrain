
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include <random>

namespace pge::noise {

class WhiteNoise : public INoise
{
  public:
  WhiteNoise(IHasherPtr hasher) noexcept;
  WhiteNoise(IHasherPtr hasher, const float min, const float max) noexcept;
  ~WhiteNoise() override = default;

  void seed(const int x, const int y) override;
  auto at(const int x, const int y) const noexcept -> float override;

  private:
  IHasherPtr m_hasher;

  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

} // namespace pge::noise
