
#include "PeriodicGradientGenerator.hh"
#include "TestName.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto PERIOD = 8;
constexpr auto SEED   = 2023;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

using PeriodicGradientGeneratorToTest = PeriodicGradientGenerator2d;
using LatticePoint                    = ILatticePoint<PeriodicGradientGeneratorToTest::DIMENSION>;

namespace behavior {
class Unit_Terrain_PeriodicGradientGenerator : public Test
{
  protected:
  void SetUp() override {}

  void testOddPeriodThrowException()
  {
    EXPECT_THROW(PeriodicGradientGeneratorToTest(3, SEED), std::invalid_argument);
  }

  void testPeriodic(const int axis)
  {
    ASSERT_GE(PeriodicGradientGeneratorToTest::DIMENSION, axis);

    const LatticePoint p1 = LatticePoint::Zero();
    LatticePoint p2       = LatticePoint::Zero();
    LatticePoint p3       = LatticePoint::Zero();

    p2(axis) = PERIOD;
    p3(axis) = -5.0f * PERIOD;

    PeriodicGradientGeneratorToTest generator(PERIOD, SEED);

    const auto v1 = generator.at(p1);
    const auto v2 = generator.at(p2);
    const auto v3 = generator.at(p3);

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v1, v3);
  }
};

TEST_F(Unit_Terrain_PeriodicGradientGenerator, Test_OddPeriodThrowException)
{
  this->testOddPeriodThrowException();
}

enum Axis
{
  X = 0,
  Y = 1,
  Z = 2
};

TEST_F(Unit_Terrain_PeriodicGradientGenerator, Test_X)
{
  this->testPeriodic(Axis::X);
}

TEST_F(Unit_Terrain_PeriodicGradientGenerator, Test_Y)
{
  this->testPeriodic(Axis::Y);
}

} // namespace behavior

namespace at {
struct TestCase
{
  LatticePoint latticePoint;

  Point3d expected;

  int period{PERIOD};
  Seed seed{SEED};
};

using PeriodicGradientAtTestSuite = TestWithParam<TestCase>;

TEST_P(PeriodicGradientAtTestSuite, Test_At)
{
  const auto param = GetParam();
  PeriodicGradientGeneratorToTest generator{param.period, param.seed};

  const auto actual = generator.at(param.latticePoint);
  EXPECT_NEAR(actual(0), param.expected(0), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(actual(1), param.expected(1), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(actual(2), param.expected(2), REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(
  Unit_Terrain_PeriodicGradientGenerator2d,
  PeriodicGradientAtTestSuite,
  Values(TestCase{LatticePoint{0, 1}, Point3d{0.261125f, 0.931419f, -0.253521f}},
         TestCase{LatticePoint{1, 2}, Point3d{-0.403105f, 0.236356f, 0.884105f}}),
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

using PeriodicGradientGenerateForTestSuite = TestWithParam<TestCase>;

TEST_P(PeriodicGradientGenerateForTestSuite, Test_GenerateFor)
{
  const auto param = GetParam();
  PeriodicGradientGeneratorToTest generator{param.period, param.seed};

  const auto actual = generator.generateFor(param.latticePoint, param.inPoint);
  EXPECT_NEAR(actual, param.expected, REASONABLE_COMPARISON_THRESHOLD);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicGradientGenerator2d,
                         PeriodicGradientGenerateForTestSuite,
                         Values(TestCase{Point2d{0.2f, 0.3f}, LatticePoint{0, 1}, -0.599768f},
                                TestCase{Point2d{1.2f, 2.3f}, LatticePoint{1, 2}, -0.009714f},
                                TestCase{Point2d{-0.2f, 1.45f}, LatticePoint{-1, 2}, -0.478953f},
                                TestCase{Point2d{-0.89f, -0.37f}, LatticePoint{-1, 0}, -0.10899f},
                                TestCase{Point2d{0.78f, -0.37f}, LatticePoint{1, -1}, 0.006288f}),
                         testNameFromPointLatticePointAndExpected<TestCase>);
} // namespace generate_for
} // namespace pge::terrain
