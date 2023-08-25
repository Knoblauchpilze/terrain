
#pragma once

#include "INoise.hh"
#include <vector>

namespace pge::noise {

class PeriodicNoise : public INoise
{
  public:
  PeriodicNoise(const int period, const Seed seed) noexcept;
  PeriodicNoise(const int period, const Seed seed, const float min, const float max) noexcept;
  ~PeriodicNoise() override = default;

  void seed(const int x, const int y) override;
  auto at(const int x, const int y) const noexcept -> float override;

  private:
  int m_period;
  int m_modulusMask;
  float m_min{0.0f};
  float m_max{1.0f};
  Seed m_seed;
  std::vector<float> m_values{};
  std::vector<int> m_permutations{};

  void generate();
  void generatePermutationsTable();
};

} // namespace pge::noise
