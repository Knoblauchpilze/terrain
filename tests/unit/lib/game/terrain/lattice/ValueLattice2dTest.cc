
#include "Bilinear2d.hh"
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
class Unit_Terrain_ValueLattice : public LatticePreparer<ValueLattice, ValueLattice::DIMENSION>,
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

TEST_F(Unit_Terrain_ValueLattice, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_ValueLattice, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_ValueLattice, Test_UseInterpolate)
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

struct TestCaseValue
{
  Point2d in;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using ValueLatticeAtTestSuite = TestWithParam<TestCaseValue>;

TEST_P(ValueLatticeAtTestSuite, Test_At)
{
  const auto param = GetParam();

  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<Hasher2d>(SEED);
  auto noise          = std::make_unique<WhiteNoise>();
  auto interpolator   = std::make_unique<Bilinear2d>();
  auto lattice        = std::make_unique<ValueLattice>(std::move(hasher),
                                                std::move(noise),
                                                std::move(interpolator));

  const auto actual = lattice->at(param.in);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ValueLattice2d,
                         ValueLatticeAtTestSuite,
                         Values(TestCaseValue{Point2d{0.0f, 0.0f}, 0.1004222f},
                                TestCaseValue{Point2d{0.0f, 1.0f}, 0.6273638f},
                                TestCaseValue{Point2d{0.5f, 0.5f}, 0.4484194f},
                                TestCaseValue{Point2d{0.1f, 0.32f}, 0.2887946f},
                                TestCaseValue{Point2d{0.49f, 0.98f}, 0.6624752f},
                                TestCaseValue{Point2d{0.67f, 0.51f}, 0.4813684f},
                                TestCaseValue{Point2d{0.01f, 0.79f}, 0.5179381f}),
                         testNameFromSingleInputPoint<TestCaseValue>);

} // namespace at

} // namespace pge::terrain
