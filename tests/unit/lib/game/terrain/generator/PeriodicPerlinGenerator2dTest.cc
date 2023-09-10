
#include "PeriodicPerlinGenerator.hh"
#include "TestName.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto PERIOD = 8;
constexpr auto SEED   = 2023;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

namespace behavior {
template<typename PeriodicPerlinGeneratorToTest>
class Unit_Terrain_PeriodicPerlinGenerator : public Test
{
  using LatticePoint = ILatticePoint<PeriodicPerlinGeneratorToTest::DIMENSION>;

  protected:
  void SetUp() override {}

  void testOddPeriodThrowException()
  {
    EXPECT_THROW(PeriodicPerlinGeneratorToTest(3, SEED), std::invalid_argument);
  }

  void testPeriodic(const int axis)
  {
    ASSERT_GE(PeriodicPerlinGeneratorToTest::DIMENSION, axis);

    const LatticePoint p1 = LatticePoint::Zero();
    LatticePoint p2       = LatticePoint::Zero();
    LatticePoint p3       = LatticePoint::Zero();

    p2(axis) = PERIOD;
    p3(axis) = -5.0f * PERIOD;

    PeriodicPerlinGeneratorToTest generator(PERIOD, SEED);

    const auto v1 = generator.at(p1);
    const auto v2 = generator.at(p2);
    const auto v3 = generator.at(p3);

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v1, v3);
  }
};

enum Axis
{
  X = 0,
  Y = 1,
  Z = 2
};

namespace dim2d {
using Unit_Terrain_PeriodicPerlinGenerator2d
  = Unit_Terrain_PeriodicPerlinGenerator<PeriodicPerlinGenerator2d>;

TEST_F(Unit_Terrain_PeriodicPerlinGenerator2d, Test_OddPeriodThrowException)
{
  this->testOddPeriodThrowException();
}

TEST_F(Unit_Terrain_PeriodicPerlinGenerator2d, Test_PeriodicX)
{
  this->testPeriodic(Axis::X);
}

TEST_F(Unit_Terrain_PeriodicPerlinGenerator2d, Test_PeriodicY)
{
  this->testPeriodic(Axis::Y);
}
} // namespace dim2d

namespace dim3d {
using Unit_Terrain_PeriodicPerlinGenerator3d
  = Unit_Terrain_PeriodicPerlinGenerator<PeriodicPerlinGenerator3d>;

TEST_F(Unit_Terrain_PeriodicPerlinGenerator3d, Test_OddPeriodThrowException)
{
  this->testOddPeriodThrowException();
}

TEST_F(Unit_Terrain_PeriodicPerlinGenerator3d, Test_PeriodicX)
{
  this->testPeriodic(Axis::X);
}

TEST_F(Unit_Terrain_PeriodicPerlinGenerator3d, Test_PeriodicY)
{
  this->testPeriodic(Axis::Y);
}

TEST_F(Unit_Terrain_PeriodicPerlinGenerator3d, Test_PeriodicZ)
{
  this->testPeriodic(Axis::Z);
}
} // namespace dim3d

} // namespace behavior

using PeriodicPerlinGeneratorToTest = PeriodicPerlinGenerator2d;
using LatticePoint                  = ILatticePoint<PeriodicPerlinGeneratorToTest::DIMENSION>;

namespace at {
struct TestCase
{
  LatticePoint latticePoint;

  Point3d expected;

  int period{PERIOD};
  Seed seed{SEED};
};

using PeriodicPerlinAtTestSuite = TestWithParam<TestCase>;

TEST_P(PeriodicPerlinAtTestSuite, Test_At)
{
  const auto param = GetParam();
  PeriodicPerlinGeneratorToTest generator{param.period, param.seed};

  const auto actual = generator.at(param.latticePoint);
  EXPECT_NEAR(actual(0), param.expected(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(actual(1), param.expected(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(actual(2), param.expected(2), REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinGenerator2d,
                         PeriodicPerlinAtTestSuite,
                         Values(TestCase{LatticePoint{0, 1}, Point3d{1.0f, 0.0f, -1.0f}},
                                TestCase{LatticePoint{1, 2}, Point3d{1.0f, 1.0f, 0.0f}}),
                         testNameFromLatticePointAndExpected<TestCase>);
} // namespace at

namespace generate_for {
struct TestCase
{
  Point2d inPoint;
  LatticePoint latticePoint;

  float expected;

  int period{PERIOD};
  Seed seed{SEED};
};

using PeriodicPerlinGenerateForTestSuite = TestWithParam<TestCase>;

TEST_P(PeriodicPerlinGenerateForTestSuite, Test_GenerateFor)
{
  const auto param = GetParam();
  PeriodicPerlinGeneratorToTest generator{param.period, param.seed};

  const auto actual = generator.generateFor(param.latticePoint, param.inPoint);
  EXPECT_NEAR(actual, param.expected, REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinGenerator2d,
                         PeriodicPerlinGenerateForTestSuite,
                         Values(TestCase{Point2d{0.2f, 0.3f}, LatticePoint{0, 1}, 0.2f},
                                TestCase{Point2d{1.2f, 2.3f}, LatticePoint{1, 2}, 0.5f},
                                TestCase{Point2d{-0.2f, 1.45f}, LatticePoint{-1, 2}, -1.35f},
                                TestCase{Point2d{-0.89f, -0.37f}, LatticePoint{-1, 0}, -0.11f},
                                TestCase{Point2d{0.78f, -0.37f}, LatticePoint{1, -1}, 0.22f}),
                         testNameFromPointLatticePointAndExpected<TestCase>);
} // namespace generate_for
} // namespace pge::terrain
