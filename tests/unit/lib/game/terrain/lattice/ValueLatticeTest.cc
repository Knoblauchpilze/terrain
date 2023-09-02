
#include "ValueLattice.hh"
#include "Bilinear.hh"
#include "Hasher.hh"
#include "ILatticePreparer.hh"
#include "IPoint.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
class Unit_Terrain_ValueLattice : public LatticePreparer<ValueLattice>, public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_F(Unit_Terrain_ValueLattice, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_)).Times(4);
  lattice->at({});
}

TEST_F(Unit_Terrain_ValueLattice, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, next()).Times(4);
  lattice->at({});
}

TEST_F(Unit_Terrain_ValueLattice, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, _, _)).Times(1);
  lattice->at({});
}

namespace interpolate {
struct TestCaseForInterpolate
{
  Point2d p;

  float px;
  float py;
};

class ValueLatticeInterpolateTestSuite : public LatticePreparer<ValueLattice>,
                                         public TestWithParam<TestCaseForInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

namespace {
auto generateTestName(const TestParamInfo<TestCaseForInterpolate> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}
} // namespace

TEST_P(ValueLatticeInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, param.px, param.py)).Times(1);
  lattice->at(param.p);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ValueLattice,
                         ValueLatticeInterpolateTestSuite,
                         Values(TestCaseForInterpolate{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseForInterpolate{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseForInterpolate{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseForInterpolate{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseForInterpolate{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseForInterpolate{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseForInterpolate{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         generateTestName);

} // namespace interpolate

namespace at {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCaseValue
{
  Point2d p;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using ValueLatticeAtTestSuite = TestWithParam<TestCaseValue>;

namespace {
auto generateTestName(const TestParamInfo<TestCaseValue> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}
} // namespace

TEST_P(ValueLatticeAtTestSuite, Test_At)
{
  const auto param = GetParam();

  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<Hasher2d>(SEED);
  auto noise          = std::make_unique<WhiteNoise>();
  auto interpolator   = std::make_unique<Bilinear>();
  auto lattice        = std::make_unique<ValueLattice>(std::move(hasher),
                                                std::move(noise),
                                                std::move(interpolator));

  const auto actual = lattice->at(param.p);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ValueLattice,
                         ValueLatticeAtTestSuite,
                         Values(TestCaseValue{Point2d{0.0f, 0.0f}, 0.1004222f},
                                TestCaseValue{Point2d{0.0f, 1.0f}, 0.6273638f},
                                TestCaseValue{Point2d{0.5f, 0.5f}, 0.4484194f},
                                TestCaseValue{Point2d{0.1f, 0.32f}, 0.2887946f},
                                TestCaseValue{Point2d{0.49f, 0.98f}, 0.6624752f},
                                TestCaseValue{Point2d{0.67f, 0.51f}, 0.4813684f},
                                TestCaseValue{Point2d{0.01f, 0.79f}, 0.5179381f}),
                         generateTestName);

} // namespace at

} // namespace pge::terrain
