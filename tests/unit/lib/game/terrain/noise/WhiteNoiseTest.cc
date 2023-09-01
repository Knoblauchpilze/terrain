
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto DEFAULT_SEED = 10;

TEST(Unit_Noise_WhiteNoise, Test_ReturnSameValueWithSameSeed)
{
  auto n = std::make_unique<WhiteNoise>();

  n->seed(DEFAULT_SEED);
  const auto v1 = n->next();

  n->seed(DEFAULT_SEED);
  const auto v2 = n->next();

  EXPECT_EQ(v1, v2);
}

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.00001f;

struct TestCase
{
  Seed seed;
  float expected;

  float min{0.0f};
  float max{1.0f};

  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using WhiteNoiseTestSuite = TestWithParam<TestCase>;

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;

  str += std::to_string(info.param.min);
  str += "_";
  str += std::to_string(info.param.max);

  str += "_";

  str += std::to_string(info.param.seed);

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}

TEST_P(WhiteNoiseTestSuite, Test_Next)
{
  const auto param = GetParam();

  auto n = std::make_unique<WhiteNoise>(param.min, param.max);
  n->seed(param.seed);
  EXPECT_NEAR(param.expected, n->next(), param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Noise_WhiteNoise,
                         WhiteNoiseTestSuite,
                         Values(TestCase{0, 0.548814f},
                                TestCase{1, 0.417022f},
                                TestCase{2, 0.435995f},
                                TestCase{3, 0.101596f, -1.0f, 1.0f},
                                TestCase{4, 0.93406f, -1.0f, 1.0f},
                                TestCase{5, -0.822405f, -1.0f, -0.2f}),
                         generateTestName);

} // namespace pge::terrain
