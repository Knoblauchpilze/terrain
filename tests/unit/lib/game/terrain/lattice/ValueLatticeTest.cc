
#include "ValueLattice.hh"
#include "Bilinear.hh"
#include "Hasher.hh"
#include "ILatticePreparer.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
class Unit_Lattice_ValueLattice : public LatticePreparer<ValueLattice>, public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_F(Unit_Lattice_ValueLattice, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_, _)).Times(4);
  lattice->at(0, 0);
}

TEST_F(Unit_Lattice_ValueLattice, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, next()).Times(4);
  lattice->at(0, 0);
}

TEST_F(Unit_Lattice_ValueLattice, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, _, _)).Times(1);
  lattice->at(0, 0);
}

namespace {
struct TestCaseForInterpolate
{
  float x;
  float y;

  float px;
  float py;
};

class InterpolateValueTestSuite : public LatticePreparer<ValueLattice>,
                                  public TestWithParam<TestCaseForInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

auto generateTestNameForInterpolate(const TestParamInfo<TestCaseForInterpolate> &info)
  -> std::string
{
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(InterpolateValueTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, param.px, param.py)).Times(1);
  lattice->at(param.x, param.y);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_ValueLattice,
                         InterpolateValueTestSuite,
                         Values(TestCaseForInterpolate{0.0f, 0.0f, 0.0f, 0.0f},
                                TestCaseForInterpolate{0.5f, 0.0f, 0.5f, 0.0f},
                                TestCaseForInterpolate{0.0f, 0.5f, 0.0f, 0.5f},
                                TestCaseForInterpolate{0.2f, 0.3f, 0.2f, 0.3f},
                                TestCaseForInterpolate{0.7f, 0.1f, 0.7f, 0.1f},
                                TestCaseForInterpolate{0.9f, 0.51f, 0.9f, 0.51f},
                                TestCaseForInterpolate{0.02f, 0.98f, 0.02f, 0.98f}),
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

using ValueTestSuite = TestWithParam<TestCaseValue>;

auto generateTestNameForValue(const TestParamInfo<TestCaseValue> &info) -> std::string
{
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(ValueTestSuite, Test_Value)
{
  const auto param = GetParam();

  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<Hasher>(SEED);
  auto noise          = std::make_unique<WhiteNoise>();
  auto interpolator   = std::make_unique<Bilinear>();
  auto lattice        = std::make_unique<ValueLattice>(std::move(hasher),
                                                std::move(noise),
                                                std::move(interpolator));

  const auto actual = lattice->at(param.x, param.y);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_ValueLattice,
                         ValueTestSuite,
                         Values(TestCaseValue{0.0f, 0.0f, 0.1004222f},
                                TestCaseValue{0.0f, 1.0f, 0.6273638f},
                                TestCaseValue{0.5f, 0.5f, 0.4484194f},
                                TestCaseValue{0.1f, 0.32f, 0.2887946f},
                                TestCaseValue{0.49f, 0.98f, 0.6624752f},
                                TestCaseValue{0.67f, 0.51f, 0.4813684f},
                                TestCaseValue{0.01f, 0.79f, 0.5179381f}),
                         generateTestNameForValue);

} // namespace pge::terrain
