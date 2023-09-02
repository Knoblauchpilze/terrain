
#include "PeriodicGradientGenerator.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto DEFAULT_PERIOD = 8;
constexpr auto DEFAULT_SEED   = 2023;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Terrain_PeriodicGradientGenerator, Test_PeriodOddThrowException)
{
  EXPECT_THROW(PeriodicGradientGenerator(3, DEFAULT_SEED), std::invalid_argument);
}

TEST(Unit_Terrain_PeriodicGradientGenerator, Test_PeriodicX)
{
  PeriodicGradientGenerator generator{DEFAULT_PERIOD, DEFAULT_SEED};

  auto p        = LatticePoint2d(0, 1);
  const auto v1 = generator.at(p);

  p             = LatticePoint2d(0 + DEFAULT_PERIOD, 1);
  const auto v2 = generator.at(p);
  EXPECT_NEAR(v1(0), v2(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(1), v2(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(2), v2(2), REASONABLE_COMPARISON_THRESHOLD);

  p             = LatticePoint2d(0 - 5 * DEFAULT_PERIOD, 1);
  const auto v3 = generator.at(p);
  EXPECT_NEAR(v1(0), v3(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(1), v3(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(2), v3(2), REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_PeriodicGradientGenerator, Test_PeriodicY)
{
  PeriodicGradientGenerator generator{DEFAULT_PERIOD, DEFAULT_SEED};

  auto p        = LatticePoint2d(0, 1);
  const auto v1 = generator.at(p);

  p             = LatticePoint2d(0, 1 + DEFAULT_PERIOD);
  const auto v2 = generator.at(p);
  EXPECT_NEAR(v1(0), v2(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(1), v2(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(2), v2(2), REASONABLE_COMPARISON_THRESHOLD);

  p             = LatticePoint2d(0, 1 - 3 * DEFAULT_PERIOD);
  const auto v3 = generator.at(p);
  EXPECT_NEAR(v1(0), v3(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(1), v3(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1(2), v3(2), REASONABLE_COMPARISON_THRESHOLD);
}

namespace at {
struct TestCase
{
  LatticePoint2d latticePoint;

  Point3d expected;

  int period{DEFAULT_PERIOD};
  Seed seed{DEFAULT_SEED};
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using PeriodicGradientAtTestSuite = TestWithParam<TestCase>;

namespace {
auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;

  str += std::to_string(info.param.latticePoint(0));
  str += "x";
  str += std::to_string(info.param.latticePoint(1));

  str += "_";

  str += std::to_string(info.param.expected(0));
  str += "x";
  str += std::to_string(info.param.expected(1));
  str += "x";
  str += std::to_string(info.param.expected(2));

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}
} // namespace

TEST_P(PeriodicGradientAtTestSuite, Test_At)
{
  const auto param = GetParam();
  PeriodicGradientGenerator generator{param.period, param.seed};

  const auto actual = generator.at(param.latticePoint);
  EXPECT_NEAR(actual(0), param.expected(0), param.threshold);
  EXPECT_NEAR(actual(1), param.expected(1), param.threshold);
  EXPECT_NEAR(actual(2), param.expected(2), param.threshold);
}

INSTANTIATE_TEST_SUITE_P(
  Unit_Terrain_PeriodicGradientGenerator,
  PeriodicGradientAtTestSuite,
  Values(TestCase{LatticePoint2d{0, 1}, Point3d{0.261125f, 0.931419f, -0.253521f}},
         TestCase{LatticePoint2d{1, 2}, Point3d{-0.403105f, 0.236356f, 0.884105f}}),
  generateTestName);
} // namespace at

namespace generate_for {
struct TestCase
{
  Point2d point;
  LatticePoint2d latticePoint;

  float expected;

  int period{DEFAULT_PERIOD};
  Seed seed{DEFAULT_SEED};
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using PeriodicGradientGenerateForTestSuite = TestWithParam<TestCase>;

namespace {
auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;
  str += std::to_string(info.param.point(0));
  str += "x";
  str += std::to_string(info.param.point(1));

  str += "_";

  str += std::to_string(info.param.latticePoint(0));
  str += "x";
  str += std::to_string(info.param.latticePoint(1));

  str += "_";

  str += std::to_string(info.param.expected);

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}
} // namespace

TEST_P(PeriodicGradientGenerateForTestSuite, Test_GenerateFor)
{
  const auto param = GetParam();
  PeriodicGradientGenerator generator{param.period, param.seed};

  const auto actual = generator.generateFor(param.latticePoint, param.point);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicGradientGenerator,
                         PeriodicGradientGenerateForTestSuite,
                         Values(TestCase{Point2d{0.2f, 0.3f}, LatticePoint2d{0, 1}, -0.599768f},
                                TestCase{Point2d{1.2f, 2.3f}, LatticePoint2d{1, 2}, -0.009714f},
                                TestCase{Point2d{-0.2f, 1.45f}, LatticePoint2d{-1, 2}, -0.478953f},
                                TestCase{Point2d{-0.89f, -0.37f}, LatticePoint2d{-1, 0}, -0.10899f},
                                TestCase{Point2d{0.78f, -0.37f}, LatticePoint2d{1, -1}, 0.006288f}),
                         generateTestName);
} // namespace generate_for
} // namespace pge::terrain
