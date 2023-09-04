
#include "GradientLattice.hh"
#include "Bilinear2d.hh"
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
  lattice->at(Point2d::Zero());
}

TEST_F(Unit_Terrain_GradientLattice, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, next()).Times(12);
  lattice->at(Point2d::Zero());
}

TEST_F(Unit_Terrain_GradientLattice, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(Point2d::Zero());
}

namespace interpolate {
struct TestCaseInterpolate
{
  Point2d p;

  float interpolatedX;
  float interpolatedY;
};

class GradientLatticeInterpolateTestSuite : public LatticePreparer<GradientLattice>,
                                            public TestWithParam<TestCaseInterpolate>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

namespace {
auto generateTestName(const TestParamInfo<TestCaseInterpolate> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}
} // namespace

TEST_P(GradientLatticeInterpolateTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_)).Times(1);
  lattice->at(param.p);
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[0].delta());
  EXPECT_EQ(param.interpolatedX, mockInterpolator->data.axes[1].delta());
  EXPECT_EQ(param.interpolatedY, mockInterpolator->data.deltas[0]);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_GradientLattice,
                         GradientLatticeInterpolateTestSuite,
                         Values(TestCaseInterpolate{Point2d{0.0f, 0.0f}, 0.0f, 0.0f},
                                TestCaseInterpolate{Point2d{0.5f, 0.0f}, 0.5f, 0.0f},
                                TestCaseInterpolate{Point2d{0.0f, 0.5f}, 0.0f, 0.5f},
                                TestCaseInterpolate{Point2d{0.2f, 0.3f}, 0.2f, 0.3f},
                                TestCaseInterpolate{Point2d{0.7f, 0.1f}, 0.7f, 0.1f},
                                TestCaseInterpolate{Point2d{0.9f, 0.51f}, 0.9f, 0.51f},
                                TestCaseInterpolate{Point2d{0.02f, 0.98f}, 0.02f, 0.98f}),
                         generateTestName);

} // namespace interpolate

namespace {
auto createGradientLattice() -> ILatticePtr
{
  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<Hasher2d>(SEED);
  auto noise          = std::make_unique<WhiteNoise>(-1.0f, 1.0f);
  auto interpolator   = std::make_unique<Bilinear2d>();
  return std::make_unique<GradientLattice>(std::move(hasher),
                                           std::move(noise),
                                           std::move(interpolator));
}

auto createGradientLatticeWithMockedNoise(INoisePtr mockNoise) -> ILatticePtr
{
  constexpr auto SEED = 1993;
  auto hasher         = std::make_unique<Hasher2d>(SEED);
  auto interpolator   = std::make_unique<Bilinear2d>();
  return std::make_unique<GradientLattice>(std::move(hasher),
                                           std::move(mockNoise),
                                           std::move(interpolator));
}
} // namespace

namespace at {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCaseValue
{
  Point2d p;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using GradientLatticeAtTestSuite = TestWithParam<TestCaseValue>;

namespace {
auto generateTestName(const TestParamInfo<TestCaseValue> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}
} // namespace

TEST_P(GradientLatticeAtTestSuite, Test_At)
{
  const auto param = GetParam();

  auto lattice      = createGradientLattice();
  const auto actual = lattice->at(param.p);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_GradientLattice,
                         GradientLatticeAtTestSuite,
                         Values(TestCaseValue{Point2d{0.0f, 0.0f}, 0.5f},
                                TestCaseValue{Point2d{0.0f, 1.0f}, 0.5f},
                                TestCaseValue{Point2d{0.5f, 0.5f}, 0.483331f},
                                TestCaseValue{Point2d{0.1f, 0.32f}, 0.32799f},
                                TestCaseValue{Point2d{0.49f, 0.98f}, 0.504369f},
                                TestCaseValue{Point2d{0.67f, 0.51f}, 0.570583f},
                                TestCaseValue{Point2d{0.01f, 0.79f}, 0.352243f}),
                         generateTestName);

} // namespace at

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

} // namespace pge::terrain
