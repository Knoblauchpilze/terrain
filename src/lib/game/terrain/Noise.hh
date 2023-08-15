
#pragma once

#include <memory>
#include <random>

namespace pge::noise {

class Noise
{
  public:
  using Seed = int;

  Noise() noexcept;
  ~Noise() = default;

  void seed(const Seed seed);
  auto next() const noexcept -> float;

  private:
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

using NoisePtr = std::unique_ptr<Noise>;

} // namespace pge::noise
