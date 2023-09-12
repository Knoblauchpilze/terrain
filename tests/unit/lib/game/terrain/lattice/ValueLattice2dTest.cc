
#include "Bilinear2d.hh"
#include "Bilinear3d.hh"
#include "Hasher.hh"
#include "IPoint.hh"
#include "LatticePreparer.hh"
#include "TestName.hh"
#include "ValueLattice.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
namespace behavior {
class Unit_Terrain_ValueLattice_Behavior
  : public LatticePreparer<ValueLattice, ValueLattice::DIMENSION>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }

  void testUseHasher()
  {
    EXPECT_CALL(*mockHasher, hash(_)).Times(4);
    lattice->at(IPoint<ValueLattice::DIMENSION>::Zero());
  }

  void testUseNoise()
  {
    EXPECT_CALL(*mockNoise, next()).Times(4);
    lattice->at(IPoint<ValueLattice::DIMENSION>::Zero());
  }

  void testUseInterpolate()
  {
    EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
    lattice->at(IPoint<ValueLattice::DIMENSION>::Zero());
  }
};

TEST_F(Unit_Terrain_ValueLattice_Behavior, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_ValueLattice_Behavior, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_ValueLattice_Behavior, Test_UseInterpolate)
{
  this->testUseInterpolate();
}
} // namespace behavior

namespace interpolate {
struct TestCaseForInterpolate
{
  Point2d in;

  float interpolatedX;
  float interpolatedY;
};

class ValueLatticeInterpolateTestSuite : public LatticePreparer<ValueLattice, 2>,
                                         public TestWithParam<TestCaseForInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_P(ValueLatticeInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(param.in);
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[0].delta());
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[1].delta());
  EXPECT_EQ(param.interpolatedY, mockInterpolator->data.deltas[0]);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ValueLattice2d,
                         ValueLatticeInterpolateTestSuite,
                         Values(TestCaseForInterpolate{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseForInterpolate{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseForInterpolate{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseForInterpolate{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseForInterpolate{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseForInterpolate{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseForInterpolate{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         testNameFromSingleInputPoint<TestCaseForInterpolate>);

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
class ValueTestSuiteAt : public TestWithParam<TestCase<Dimension>>
{
  protected:
  void SetUp() override {}

  void testAt(const TestCase<Dimension> &testCase)
  {
    constexpr auto SEED = 1993;
    auto hasher         = std::make_unique<Hasher<Dimension>>(SEED);
    auto noise          = std::make_unique<WhiteNoise>();
    auto interpolator   = std::make_unique<Interpolator>();
    auto lattice        = std::make_unique<ValueLattice>(std::move(hasher),
                                                  std::move(noise),
                                                  std::move(interpolator));

    const auto actual = lattice->at(testCase.in);
    EXPECT_NEAR(actual, testCase.expected, REASONABLE_COMPARISON_THRESHOLD);
  }
};

namespace dim2d {
using TestCase2d = TestCase<2>;
using ValueAt2d  = ValueTestSuiteAt<2, Bilinear2d>;

TEST_P(ValueAt2d, Test_At)
{
  const auto param = GetParam();
  this->testAt(param);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ValueLattice,
                         ValueAt2d,
                         Values(TestCase2d{Point2d{0.0f, 0.0f}, 0.1004222f},
                                TestCase2d{Point2d{0.0f, 1.0f}, 0.6273638f},
                                TestCase2d{Point2d{0.5f, 0.5f}, 0.4484194f},
                                TestCase2d{Point2d{0.1f, 0.32f}, 0.2887946f},
                                TestCase2d{Point2d{0.49f, 0.98f}, 0.6624752f},
                                TestCase2d{Point2d{0.67f, 0.51f}, 0.4813684f},
                                TestCase2d{Point2d{0.01f, 0.79f}, 0.5179381f}),
                         testNameFromSingleInputPoint<TestCase2d>);
} // namespace dim2d
} // namespace at

} // namespace pge::terrain
