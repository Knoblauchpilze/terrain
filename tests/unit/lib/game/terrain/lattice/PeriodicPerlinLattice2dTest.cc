
#include "Bilinear2d.hh"
#include "IPoint.hh"
#include "PeriodicLatticePreparer.hh"
#include "PeriodicPerlinLattice.hh"
#include "TestName.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto PERIOD = 8;
constexpr auto SEED   = 1993;

namespace behavior {
class Unit_Terrain_PeriodicPerlinLattice_Behavior
  : public PeriodicLatticePreparer<PeriodicPerlinLattice, PeriodicPerlinLattice::DIMENSION>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice(PERIOD, SEED);
  }

  void testUseInterpolate()
  {
    EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
    lattice->at(IPoint<PeriodicPerlinLattice::DIMENSION>::Zero());
  }
};

TEST_F(Unit_Terrain_PeriodicPerlinLattice_Behavior, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(Point2d::Zero());
}
} // namespace behavior

namespace periodic {
class Unit_Terrain_PeriodicPerlinLattice_Periodic
  : public PeriodicLatticePreparer<PeriodicPerlinLattice, PeriodicPerlinLattice::DIMENSION>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice(PERIOD, SEED);
  }

  void testPeriodic(const int axis)
  {
    ASSERT_GE(PeriodicPerlinLattice::DIMENSION, axis);
    using Point = IPoint<PeriodicPerlinLattice::DIMENSION>;

    const Point p1 = IPoint<PeriodicPerlinLattice::DIMENSION>::Zero();
    Point p2       = IPoint<PeriodicPerlinLattice::DIMENSION>::Zero();
    Point p3       = IPoint<PeriodicPerlinLattice::DIMENSION>::Zero();

    p2(axis) = PERIOD;
    p3(axis) = -5.0f * PERIOD;

    auto interpolator = std::make_unique<Bilinear2d>();
    auto lattice = std::make_unique<PeriodicPerlinLattice>(PERIOD, SEED, std::move(interpolator));

    const auto v1 = lattice->at(p1);
    const auto v2 = lattice->at(p2);
    const auto v3 = lattice->at(p3);

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

TEST_F(Unit_Terrain_PeriodicPerlinLattice_Periodic, Test_X)
{
  this->testPeriodic(Axis::X);
}

TEST_F(Unit_Terrain_PeriodicPerlinLattice_Periodic, Test_Y)
{
  this->testPeriodic(Axis::Y);
}
} // namespace periodic

namespace interpolate {
struct TestCaseInterpolate
{
  Point2d in;

  float interpolatedX;
  float interpolatedY;
};

class PeriodicPerlinLatticeInterpolateTestSuite
  : public PeriodicLatticePreparer<PeriodicPerlinLattice, 2>,
    public TestWithParam<TestCaseInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice(PERIOD, SEED);
  }
};

TEST_P(PeriodicPerlinLatticeInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(param.in);
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[0].delta());
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[1].delta());
  EXPECT_EQ(param.interpolatedY, mockInterpolator->data.deltas[0]);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinLattice2d,
                         PeriodicPerlinLatticeInterpolateTestSuite,
                         Values(TestCaseInterpolate{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseInterpolate{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseInterpolate{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseInterpolate{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseInterpolate{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseInterpolate{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseInterpolate{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         testNameFromSingleInputPoint<TestCaseInterpolate>);

} // namespace interpolate

namespace at {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCaseValue
{
  Point2d in;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using PeriodicPerlinLatticeAtTestSuite = TestWithParam<TestCaseValue>;

TEST_P(PeriodicPerlinLatticeAtTestSuite, Test_At)
{
  const auto param = GetParam();

  auto interpolator = std::make_unique<Bilinear2d>();
  auto lattice = std::make_unique<PeriodicPerlinLattice>(PERIOD, SEED, std::move(interpolator));

  const auto actual = lattice->at(param.in);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinLattice2d,
                         PeriodicPerlinLatticeAtTestSuite,
                         Values(TestCaseValue{Point2d{0.0f, 0.0f}, 0.5f},
                                TestCaseValue{Point2d{0.0f, 1.0f}, 0.5f},
                                TestCaseValue{Point2d{0.5f, 0.5f}, 0.375f},
                                TestCaseValue{Point2d{0.1f, 0.32f}, 0.297120f},
                                TestCaseValue{Point2d{0.49f, 0.98f}, 0.254706f},
                                TestCaseValue{Point2d{0.67f, 0.51f}, 0.472205f},
                                TestCaseValue{Point2d{0.01f, 0.79f}, 0.329597f}),
                         testNameFromSingleInputPoint<TestCaseValue>);
} // namespace at
} // namespace pge::terrain
