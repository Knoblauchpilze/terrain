
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

    const Point p1 = Point::Zero();
    Point p2       = Point::Zero();
    Point p3       = Point::Zero();

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

template<int Dimension>
struct TestCase
{
  IPoint<Dimension> in;
  float expected;
};

template<int Dimension, typename Interpolator>
class PeriodicPerlinTestSuiteAt : public TestWithParam<TestCase<Dimension>>
{
  protected:
  void SetUp() override {}

  void testAt(const TestCase<Dimension> &testCase)
  {
    auto interpolator = std::make_unique<Interpolator>();
    auto lattice = std::make_unique<PeriodicPerlinLattice>(PERIOD, SEED, std::move(interpolator));

    const auto actual = lattice->at(testCase.in);
    EXPECT_NEAR(actual, testCase.expected, REASONABLE_COMPARISON_THRESHOLD);
  }
};

namespace dim2d {
using PeriodicPerlinAt2d = PeriodicPerlinTestSuiteAt<2, Bilinear2d>;

TEST_P(PeriodicPerlinAt2d, Test_At)
{
  const auto param = GetParam();
  this->testAt(param);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicPerlinLattice,
                         PeriodicPerlinAt2d,
                         Values(TestCase{Point2d{0.0f, 0.0f}, 0.5f},
                                TestCase{Point2d{0.0f, 1.0f}, 0.5f},
                                TestCase{Point2d{0.5f, 0.5f}, 0.375f},
                                TestCase{Point2d{0.1f, 0.32f}, 0.297120f},
                                TestCase{Point2d{0.49f, 0.98f}, 0.254706f},
                                TestCase{Point2d{0.67f, 0.51f}, 0.472205f},
                                TestCase{Point2d{0.01f, 0.79f}, 0.329597f}),
                         testNameFromSingleInputPoint<TestCase<2>>);
} // namespace dim2d
} // namespace at

} // namespace pge::terrain
