
#include "GradientLattice.hh"
#include "Bilinear.hh"
#include "Hasher.hh"
#include "ILatticePreparer.hh"
#include "IPoint.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
class Unit_Terrain_GradientLattice : public LatticePreparer<GradientLattice>, public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_F(Unit_Terrain_GradientLattice, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_)).Times(4);
  lattice->at({});
}

TEST_F(Unit_Terrain_GradientLattice, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, next()).Times(12);
  lattice->at({});
}

TEST_F(Unit_Terrain_GradientLattice, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, _, _)).Times(1);
  lattice->at({});
}

namespace {
struct TestCaseInterpolate
{
  Point2d p;

  float interpolatedX;
  float interpolatedY;
};

class InterpolateGradientTestSuite : public LatticePreparer<GradientLattice>,
                                     public TestWithParam<TestCaseInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

auto generateTestNameForInterpolate(const TestParamInfo<TestCaseInterpolate> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(InterpolateGradientTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, param.interpolatedX, param.interpolatedY))
    .Times(1);
  lattice->at(param.p);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_GradientLattice,
                         InterpolateGradientTestSuite,
                         Values(TestCaseInterpolate{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseInterpolate{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseInterpolate{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseInterpolate{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseInterpolate{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseInterpolate{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseInterpolate{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         generateTestNameForInterpolate);

namespace {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCaseValue
{
  Point2d p;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using GradientTestSuite = TestWithParam<TestCaseValue>;

auto generateTestNameForValue(const TestParamInfo<TestCaseValue> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(GradientTestSuite, Test_Value)
{
  const auto param = GetParam();

  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<Hasher2d>(SEED);
  auto noise          = std::make_unique<WhiteNoise>(-1.0f, 1.0f);
  auto interpolator   = std::make_unique<Bilinear>();
  auto lattice        = std::make_unique<GradientLattice>(std::move(hasher),
                                                   std::move(noise),
                                                   std::move(interpolator));

  const auto actual = lattice->at(param.p);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_GradientLattice,
                         GradientTestSuite,
                         Values(TestCaseValue{Point2d{0.0f, 0.0f}, 0.5f},
                                TestCaseValue{Point2d{0.0f, 1.0f}, 0.5f},
                                TestCaseValue{Point2d{0.5f, 0.5f}, 0.483331f},
                                TestCaseValue{Point2d{0.1f, 0.32f}, 0.32799f},
                                TestCaseValue{Point2d{0.49f, 0.98f}, 0.504369f},
                                TestCaseValue{Point2d{0.67f, 0.51f}, 0.570583f},
                                TestCaseValue{Point2d{0.01f, 0.79f}, 0.352243f}),
                         generateTestNameForValue);

} // namespace pge::terrain
