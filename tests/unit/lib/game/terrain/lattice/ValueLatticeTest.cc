
#include "ValueLattice.hh"
#include "Bilinear2d.hh"
#include "Hasher.hh"
#include "IPoint.hh"
#include "LatticePreparer.hh"
#include "TestName.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
namespace base {
template<int Dimension>
class Unit_Terrain_ValueLattice : public LatticePreparer<ValueLattice, Dimension>, public Test
{
  protected:
  void SetUp() override
  {
    this->prepareLattice();
  }

  void testUseHasher()
  {
    EXPECT_CALL(*this->mockHasher, hash(_)).Times(4);
    this->lattice->at(IPoint<Dimension>::Zero());
  }

  void testUseNoise()
  {
    EXPECT_CALL(*this->mockHasher, hash(_)).Times(4);
    this->lattice->at(IPoint<Dimension>::Zero());
  }

  void testUseInterpolate()
  {
    EXPECT_CALL(*this->mockInterpolator, interpolate(_)).Times(1);
    this->lattice->at(IPoint<Dimension>::Zero());
  }
};

using Unit_Terrain_ValueLattice2d = Unit_Terrain_ValueLattice<2>;

TEST_F(Unit_Terrain_ValueLattice2d, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_ValueLattice2d, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_ValueLattice2d, Test_UseInterpolate)
{
  this->testUseInterpolate();
}
} // namespace base

namespace interpolate {
template<int Dimension>
struct TestCaseForInterpolate
{
  IPoint<Dimension> in;

  float interpolatedX;
  float interpolatedY;
};

template<int Dimension>
class ValueLatticeInterpolateTestSuite : public LatticePreparer<ValueLattice, Dimension>,
                                         public TestWithParam<TestCaseForInterpolate<Dimension>>
{
  protected:
  void SetUp() override
  {
    this->prepareLattice();
  }

  void testInterpolate(const TestCaseForInterpolate<Dimension> &testCase)
  {
    EXPECT_CALL(*this->mockInterpolator, interpolate(_)).Times(1);
    this->lattice->at(testCase.in);
    EXPECT_EQ(testCase.interpolatedX, this->mockInterpolator->data.axes[0].delta());
    EXPECT_EQ(testCase.interpolatedX, this->mockInterpolator->data.axes[1].delta());
    EXPECT_EQ(testCase.interpolatedY, this->mockInterpolator->data.deltas[0]);
  }
};

using TestCaseForInterpolate2d           = TestCaseForInterpolate<2>;
using ValueLattice2dInterpolateTestSuite = ValueLatticeInterpolateTestSuite<2>;

TEST_P(ValueLattice2dInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();
  this->testInterpolate(param);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ValueLattice2d,
                         ValueLattice2dInterpolateTestSuite,
                         Values(TestCaseForInterpolate2d{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseForInterpolate2d{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseForInterpolate2d{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseForInterpolate2d{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseForInterpolate2d{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseForInterpolate2d{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseForInterpolate2d{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         testNameFromSingleInputPoint<TestCaseForInterpolate2d>);

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
