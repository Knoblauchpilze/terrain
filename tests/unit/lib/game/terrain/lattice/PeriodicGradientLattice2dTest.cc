
#include "Bilinear2d.hh"
#include "IPoint.hh"
#include "PeriodicGradientLattice.hh"
#include "PeriodicLatticePreparer.hh"
#include "TestName.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto PERIOD = 8;
constexpr auto SEED   = 1993;

class Unit_Terrain_PeriodicGradientLattice2d
  : public PeriodicLatticePreparer<PeriodicGradientLattice, 2>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice(PERIOD, SEED);
  }
};

TEST_F(Unit_Terrain_PeriodicGradientLattice2d, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(Point2d::Zero());
}

namespace {
auto createLattice() -> ILattice2dPtr
{
  auto interpolator = std::make_unique<Bilinear2d>();
  return std::make_unique<PeriodicGradientLattice>(PERIOD, SEED, std::move(interpolator));
}
} // namespace

TEST_F(Unit_Terrain_PeriodicGradientLattice2d, Test_PeriodicX)
{
  auto lattice = createLattice();

  auto p        = Point2d(0.0f, 1.0f);
  const auto v1 = lattice->at(p);

  p             = Point2d(0.0f + PERIOD, 1.0f);
  const auto v2 = lattice->at(p);

  p             = Point2d(0.0f - 5.0f * PERIOD, 1.0f);
  const auto v3 = lattice->at(p);

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v1, v3);
}

TEST_F(Unit_Terrain_PeriodicGradientLattice2d, Test_PeriodicY)
{
  auto lattice = createLattice();

  auto p        = Point2d(-1.0f, -2.0f);
  const auto v1 = lattice->at(p);

  p             = Point2d(-1.0f, -2.0f + PERIOD);
  const auto v2 = lattice->at(p);

  p             = Point2d(-1.0f, -2.0f - 5.0f * PERIOD);
  const auto v3 = lattice->at(p);

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v1, v3);
}

namespace interpolate {
struct TestCaseInterpolate
{
  Point2d in;

  float interpolatedX;
  float interpolatedY;
};

class PeriodicGradientLatticeInterpolateTestSuite
  : public PeriodicLatticePreparer<PeriodicGradientLattice, 2>,
    public TestWithParam<TestCaseInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice(PERIOD, SEED);
  }
};

TEST_P(PeriodicGradientLatticeInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(param.in);
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[0].delta());
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[1].delta());
  EXPECT_EQ(param.interpolatedY, mockInterpolator->data.deltas[0]);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicGradientLattice2d,
                         PeriodicGradientLatticeInterpolateTestSuite,
                         Values(TestCaseInterpolate{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseInterpolate{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseInterpolate{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseInterpolate{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseInterpolate{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseInterpolate{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseInterpolate{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         testNameForSingleInputPoint<TestCaseInterpolate>);

} // namespace interpolate

namespace at {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCaseValue
{
  Point2d in;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using PeriodicGradientLatticeAtTestSuite = TestWithParam<TestCaseValue>;

TEST_P(PeriodicGradientLatticeAtTestSuite, Test_At)
{
  const auto param = GetParam();

  auto interpolator = std::make_unique<Bilinear2d>();
  auto lattice = std::make_unique<PeriodicGradientLattice>(PERIOD, SEED, std::move(interpolator));

  const auto actual = lattice->at(param.in);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_PeriodicGradientLattice2d,
                         PeriodicGradientLatticeAtTestSuite,
                         Values(TestCaseValue{Point2d{0.0f, 0.0f}, 0.5f},
                                TestCaseValue{Point2d{0.0f, 1.0f}, 0.5f},
                                TestCaseValue{Point2d{0.5f, 0.5f}, 0.602046f},
                                TestCaseValue{Point2d{0.1f, 0.32f}, 0.383933f},
                                TestCaseValue{Point2d{0.49f, 0.98f}, 0.656713f},
                                TestCaseValue{Point2d{0.67f, 0.51f}, 0.671274f},
                                TestCaseValue{Point2d{0.01f, 0.79f}, 0.37766f}),
                         testNameForSingleInputPoint<TestCaseValue>);

} // namespace at
} // namespace pge::terrain
