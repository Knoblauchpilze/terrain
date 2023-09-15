
#include "Bilinear2d.hh"
#include "GradientLattice.hh"
#include "Hasher.hh"
#include "IPoint.hh"
#include "LatticePreparer.hh"
#include "TestName.hh"
#include "WhiteNoise.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto CACHE_SIZE = 10;
constexpr auto SEED       = 1993;

namespace behavior {
class Unit_Terrain_GradientLattice
  : public LatticePreparer<GradientLattice, GradientLattice::DIMENSION>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice(CACHE_SIZE);
  }

  void testUseHasher()
  {
    EXPECT_CALL(*mockHasher, hash(_)).Times(4);
    lattice->at(IPoint<GradientLattice::DIMENSION>::Zero());
  }

  void testUseNoise()
  {
    EXPECT_CALL(*mockNoise, next()).Times(12);
    lattice->at(IPoint<GradientLattice::DIMENSION>::Zero());
  }

  void testUseInterpolate()
  {
    EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
    lattice->at(IPoint<GradientLattice::DIMENSION>::Zero());
  }
};

namespace {
auto createGradientLatticeWithMockedNoise(INoisePtr mockNoise)
  -> ILatticePtr<GradientLattice::DIMENSION>
{
  auto hasher       = std::make_unique<Hasher2d>(SEED);
  auto interpolator = std::make_unique<Bilinear2d>();
  return std::make_unique<GradientLattice>(std::move(hasher),
                                           std::move(mockNoise),
                                           std::move(interpolator),
                                           CACHE_SIZE);
}
} // namespace

TEST_F(Unit_Terrain_GradientLattice, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_GradientLattice, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_GradientLattice, Test_UseInterpolate)
{
  this->testUseInterpolate();
}

TEST_F(Unit_Terrain_GradientLattice, Test_MinValue)
{
  auto noise     = std::make_unique<NiceMock<MockNoise>>();
  auto mockNoise = noise.get();

  EXPECT_CALL(*mockNoise, next()).Times(12);
  ON_CALL(*mockNoise, next()).WillByDefault(Invoke([]() {
    static const std::vector<float> VECTORS_FOR_MIN_VALUE = {// top left
                                                             -1.0f,
                                                             1.0f,
                                                             0.0f,
                                                             // top right
                                                             1.0f,
                                                             1.0f,
                                                             0.0f,
                                                             // bottom right
                                                             1.0f,
                                                             -1.0f,
                                                             0.0f,
                                                             // bottom left
                                                             -1.0f,
                                                             -1.0f,
                                                             0.0f};

    static auto counter = 0;
    const auto out      = VECTORS_FOR_MIN_VALUE[counter % VECTORS_FOR_MIN_VALUE.size()];
    ++counter;

    return out;
  }));

  auto lattice = createGradientLatticeWithMockedNoise(std::move(noise));
  const auto v = lattice->at({0.5f, 0.5f});

  EXPECT_EQ(0.0f, v);
}

TEST_F(Unit_Terrain_GradientLattice, Test_MaxValue)
{
  auto noise     = std::make_unique<NiceMock<MockNoise>>();
  auto mockNoise = noise.get();

  EXPECT_CALL(*mockNoise, next()).Times(12);
  ON_CALL(*mockNoise, next()).WillByDefault(Invoke([]() {
    static const std::vector<float> VECTORS_FOR_MAX_VALUE = {// top left
                                                             1.0f,
                                                             -1.0f,
                                                             0.0f,
                                                             // top right
                                                             -1.0f,
                                                             -1.0f,
                                                             0.0f,
                                                             // bottom right
                                                             -1.0f,
                                                             1.0f,
                                                             0.0f,
                                                             // bottom left
                                                             1.0f,
                                                             1.0f,
                                                             0.0f};

    static auto counter = 0;
    const auto out      = VECTORS_FOR_MAX_VALUE[counter % VECTORS_FOR_MAX_VALUE.size()];
    ++counter;

    return out;
  }));

  auto lattice = createGradientLatticeWithMockedNoise(std::move(noise));
  const auto v = lattice->at({0.5f, 0.5f});

  EXPECT_EQ(1.0f, v);
}
} // namespace behavior

namespace interpolate {
struct TestCaseInterpolate
{
  Point2d in;

  float interpolatedX;
  float interpolatedY;
};

class GradientLatticeInterpolateTestSuite : public LatticePreparer<GradientLattice, 2>,
                                            public TestWithParam<TestCaseInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice(CACHE_SIZE);
  }
};

TEST_P(GradientLatticeInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(param.in);
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[0].delta());
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[1].delta());
  EXPECT_EQ(param.interpolatedY, mockInterpolator->data.deltas[0]);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_GradientLattice2d,
                         GradientLatticeInterpolateTestSuite,
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
class GradientTestSuiteAt : public TestWithParam<TestCase<Dimension>>
{
  protected:
  void SetUp() override {}

  void testAt(const TestCase<Dimension> &testCase)
  {
    auto hasher       = std::make_unique<Hasher<Dimension>>(SEED);
    auto noise        = std::make_unique<WhiteNoise>(-1.0f, 1.0f);
    auto interpolator = std::make_unique<Interpolator>();
    auto lattice      = std::make_unique<GradientLattice>(std::move(hasher),
                                                     std::move(noise),
                                                     std::move(interpolator),
                                                     CACHE_SIZE);

    const auto actual = lattice->at(testCase.in);
    EXPECT_NEAR(actual, testCase.expected, REASONABLE_COMPARISON_THRESHOLD);
  }
};

namespace dim2d {
using TestCase2d   = TestCase<2>;
using GradientAt2d = GradientTestSuiteAt<2, Bilinear2d>;

TEST_P(GradientAt2d, Test_At)
{
  const auto param = GetParam();
  this->testAt(param);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_GradientLattice,
                         GradientAt2d,
                         Values(TestCase2d{Point2d{0.0f, 0.0f}, 0.5f},
                                TestCase2d{Point2d{0.0f, 1.0f}, 0.5f},
                                TestCase2d{Point2d{0.5f, 0.5f}, 0.483331f},
                                TestCase2d{Point2d{0.1f, 0.32f}, 0.32799f},
                                TestCase2d{Point2d{0.49f, 0.98f}, 0.504369f},
                                TestCase2d{Point2d{0.67f, 0.51f}, 0.570583f},
                                TestCase2d{Point2d{0.01f, 0.79f}, 0.352243f}),
                         testNameFromSingleInputPoint<TestCase2d>);
} // namespace dim2d
} // namespace at

} // namespace pge::terrain
