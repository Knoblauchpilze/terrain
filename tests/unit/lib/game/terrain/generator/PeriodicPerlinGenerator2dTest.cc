
#include "PeriodicPerlinGenerator.hh"
#include "TestName.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto DEFAULT_PERIOD = 8;
constexpr auto DEFAULT_SEED   = 2023;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Terrain_PeriodicPerlinGenerator2d, Test_PeriodOddThrowException)
{
  EXPECT_THROW(PeriodicPerlinGenerator2d(3, DEFAULT_SEED), std::invalid_argument);
}

TEST(Unit_Terrain_PeriodicPerlinGenerator2d, Test_PeriodicX)
{
  PeriodicPerlinGenerator2d generator{DEFAULT_PERIOD, DEFAULT_SEED};

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

TEST(Unit_Terrain_PeriodicPerlinGenerator2d, Test_PeriodicY)
{
  PeriodicPerlinGenerator2d generator{DEFAULT_PERIOD, DEFAULT_SEED};

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
};

using PeriodicPerlinAtTestSuite = TestWithParam<TestCase>;

TEST_P(PeriodicPerlinAtTestSuite, Test_At)
{
  const auto param = GetParam();
  PeriodicPerlinGenerator2d generator{param.period, param.seed};

  const auto actual = generator.at(param.latticePoint);
  EXPECT_NEAR(actual(0), param.expected(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(actual(1), param.expected(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(actual(2), param.expected(2), REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinGenerator2d,
                         PeriodicPerlinAtTestSuite,
                         Values(TestCase{LatticePoint2d{0, 1}, Point3d{1.0f, 0.0f, -1.0f}},
                                TestCase{LatticePoint2d{1, 2}, Point3d{1.0f, 1.0f, 0.0f}}),
                         testNameFromLatticePointAndExpected<TestCase>);
} // namespace at

namespace generate_for {
struct TestCase
{
  Point2d inPoint;
  LatticePoint2d latticePoint;

  float expected;

  int period{DEFAULT_PERIOD};
  Seed seed{DEFAULT_SEED};
};

using PeriodicPerlinGenerateForTestSuite = TestWithParam<TestCase>;

TEST_P(PeriodicPerlinGenerateForTestSuite, Test_GenerateFor)
{
  const auto param = GetParam();
  PeriodicPerlinGenerator2d generator{param.period, param.seed};

  const auto actual = generator.generateFor(param.latticePoint, param.inPoint);
  EXPECT_NEAR(actual, param.expected, REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinGenerator2d,
                         PeriodicPerlinGenerateForTestSuite,
                         Values(TestCase{Point2d{0.2f, 0.3f}, LatticePoint2d{0, 1}, 0.2f},
                                TestCase{Point2d{1.2f, 2.3f}, LatticePoint2d{1, 2}, 0.5f},
                                TestCase{Point2d{-0.2f, 1.45f}, LatticePoint2d{-1, 2}, -1.35f},
                                TestCase{Point2d{-0.89f, -0.37f}, LatticePoint2d{-1, 0}, -0.11f},
                                TestCase{Point2d{0.78f, -0.37f}, LatticePoint2d{1, -1}, 0.22f}),
                         testNameFromPointLatticePointAndExpected<TestCase>);
} // namespace generate_for
} // namespace pge::terrain
