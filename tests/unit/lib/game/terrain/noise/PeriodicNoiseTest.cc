
#include "PeriodicNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::noise {
constexpr auto PERIOD = 2;
constexpr auto SEED   = 2023;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Noise_PeriodicNoise, Test_PeriodicX)
{
  PeriodicNoise noise(PERIOD, SEED);

  const auto val1 = noise.at(0, 2);
  const auto val2 = noise.at(0 + PERIOD, 2);

  EXPECT_NEAR(val1, val2, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Noise_PeriodicNoise, Test_PeriodicY)
{
  PeriodicNoise noise(PERIOD, SEED);

  const auto val1 = noise.at(12, 4);
  const auto val2 = noise.at(12, 4 + PERIOD);

  EXPECT_NEAR(val1, val2, REASONABLE_COMPARISON_THRESHOLD);
}

} // namespace pge::noise
