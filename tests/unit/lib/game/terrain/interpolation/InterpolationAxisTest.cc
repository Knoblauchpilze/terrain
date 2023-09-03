
#include "InterpolationAxis.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {

TEST(Unit_Terrain_InterpolationAxis, InvalidRangeThrowException)
{
  EXPECT_THROW(InterpolationAxis(2.0f, 1.0f, 0.5f), std::invalid_argument);
}

TEST(Unit_Terrain_InterpolationAxis, NullRangeIsValid)
{
  EXPECT_NO_THROW(InterpolationAxis(1.0f, 1.0f, 0.5f));
}

TEST(Unit_Terrain_InterpolationAxis, InvalidPercentageThrowException)
{
  EXPECT_THROW(InterpolationAxis(2.0f, 1.0f, -0.5f), std::invalid_argument);
  EXPECT_THROW(InterpolationAxis(2.0f, 1.0f, 1.01f), std::invalid_argument);
}

namespace evaluate {
struct TestCase
{
  std::string name;

  float low;
  float high;
  float perc;

  float expected;
};

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  return info.param.name;
}

using InterpolationAxisTestSuite = TestWithParam<TestCase>;

TEST_P(InterpolationAxisTestSuite, Test_Evaluate)
{
  const auto param = GetParam();

  InterpolationAxis axis(param.low, param.high, param.perc);
  constexpr auto REASONABLE_COMPARISON_THRESHOLD = 1e-7f;
  EXPECT_NEAR(axis.evaluate(), param.expected, REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_InterpolationAxis,
                         InterpolationAxisTestSuite,
                         Values(TestCase{"low", 1.2f, 2.4f, 0.0f, 1.2f},
                                TestCase{"high", -2.8f, -2.5f, 1.0f, -2.5f},
                                TestCase{"inside", -0.1f, 0.9f, 0.2f, 0.1f},
                                TestCase{"null_range_low", 32.5f, 32.5f, 0.0f, 32.5f},
                                TestCase{"null_range_high", -28.7f, -28.7f, 1.0f, -28.7f},
                                TestCase{"null_range_inside", 17.4f, 17.4f, 0.2f, 17.4f}),
                         generateTestName);
} // namespace evaluate
} // namespace pge::terrain
