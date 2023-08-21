
#include "GradientLattice.hh"
#include "Bilinear.hh"
#include "Hasher.hh"
#include "ILatticePreparer.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::lattice {
class Unit_Lattice_GradientLattice : public LatticePreparer<GradientLattice>, public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_F(Unit_Lattice_GradientLattice, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, at(_, _)).Times(8);
  lattice->at(0, 0);
}

TEST_F(Unit_Lattice_GradientLattice, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, _, _)).Times(1);
  lattice->at(0, 0);
}

namespace {
struct TestCaseInterpolate
{
  float x;
  float y;

  float px;
  float py;
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
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(InterpolateGradientTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, param.px, param.py)).Times(1);
  lattice->at(param.x, param.y);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_GradientLattice,
                         InterpolateGradientTestSuite,
                         Values(TestCaseInterpolate{0.0f, 0.0f, 0.0f, 0.0f},
                                TestCaseInterpolate{0.5f, 0.0f, 0.5f, 0.0f},
                                TestCaseInterpolate{0.0f, 0.5f, 0.0f, 0.5f},
                                TestCaseInterpolate{0.2f, 0.3f, 0.2f, 0.3f},
                                TestCaseInterpolate{0.7f, 0.1f, 0.7f, 0.1f},
                                TestCaseInterpolate{0.9f, 0.51f, 0.9f, 0.51f},
                                TestCaseInterpolate{0.02f, 0.98f, 0.02f, 0.98f}),
                         generateTestNameForInterpolate);

namespace {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCaseValue
{
  float x;
  float y;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using GradientTestSuite = TestWithParam<TestCaseValue>;

auto generateTestNameForValue(const TestParamInfo<TestCaseValue> &info) -> std::string
{
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(GradientTestSuite, Test_Value)
{
  const auto param = GetParam();

  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<noise::Hasher>(SEED);
  auto noise          = std::make_unique<noise::WhiteNoise>(std::move(hasher), -1.0f, 1.0f);
  auto interpolator   = std::make_unique<interpolation::Bilinear>();
  auto lattice        = std::make_unique<lattice::GradientLattice>(std::move(noise),
                                                            std::move(interpolator));

  const auto actual = lattice->at(param.x, param.y);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_GradientLattice,
                         GradientTestSuite,
                         Values(TestCaseValue{0.0f, 0.0f, 0.5f},
                                TestCaseValue{0.0f, 1.0f, 0.5f},
                                TestCaseValue{0.5f, 0.5f, 0.4747550f},
                                TestCaseValue{0.1f, 0.32f, 0.3119567f},
                                TestCaseValue{0.49f, 0.98f, 0.4773225f},
                                TestCaseValue{0.67f, 0.51f, 0.5752330f},
                                TestCaseValue{0.01f, 0.79f, 0.3415382f}),
                         generateTestNameForValue);

} // namespace pge::lattice
