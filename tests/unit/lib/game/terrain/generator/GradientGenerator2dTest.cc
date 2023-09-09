
#include "GradientGenerator.hh"
#include "IValueGeneratorPreparer.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
class Unit_Terrain_GradientGenerator2d : public GeneratorPreparer<GradientGenerator2d, 2, Point3d>,
                                         public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

TEST_F(Unit_Terrain_GradientGenerator2d, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_)).Times(1);
  generator->generateFor(LatticePoint2d::Zero(), Point2d::Zero());
}

TEST_F(Unit_Terrain_GradientGenerator2d, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_)).Times(1);
  EXPECT_CALL(*mockNoise, next()).Times(3);
  generator->generateFor(LatticePoint2d::Zero(), Point2d::Zero());
}

namespace {
using NoiseValues = std::vector<float>;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCase
{
  Point2d point;
  LatticePoint2d latticePoint;

  NoiseValues noise;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

class GenerateForTestSuite : public GeneratorPreparer<GradientGenerator2d, 2, Point3d>,
                             public TestWithParam<TestCase>
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;
  str += std::to_string(info.param.point(0));
  str += "x";
  str += std::to_string(info.param.point(1));

  str += "_";

  str += std::to_string(info.param.latticePoint(0));
  str += "x";
  str += std::to_string(info.param.latticePoint(1));

  str += "_";

  str += std::to_string(info.param.expected);

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}

TEST_P(GenerateForTestSuite, Test_GenerateFor)
{
  const auto param = GetParam();

  ON_CALL(*mockNoise, next()).WillByDefault(Invoke([&param]() -> float {
    static auto id = 0u;
    const auto out = param.noise[id];
    ++id;
    if (id >= param.noise.size())
    {
      id = 0u;
    }
    return out;
  }));

  const auto actual = generator->generateFor(param.latticePoint, param.point);
  EXPECT_NEAR(param.expected, actual, param.threshold);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(
  Unit_Terrain_GradientGenerator2d,
  GenerateForTestSuite,
  Values(
    TestCase{Point2d{0.2f, 0.3f}, LatticePoint2d{0, 1}, NoiseValues{1.0f, 0.0f, 0.0f}, 0.2f},
    TestCase{Point2d{0.2f, 0.3f}, LatticePoint2d{0, 1}, NoiseValues{0.0f, 1.0f, 0.0f}, -0.7f},
    TestCase{Point2d{0.0f, 0.0f}, LatticePoint2d{0, 0}, NoiseValues{0.5f, 0.6f, 0.0f}, 0.0f},
    TestCase{Point2d{-0.1f, 0.5f}, LatticePoint2d{0, 1}, NoiseValues{0.8f, 0.6f, 0.0f}, -0.38f},
    // This test is a bit strange as it showcases that the 3d vector is used but not in full
    // to compute the dot product with the 2d point.
    TestCase{Point2d{-0.7f, 1.2f}, LatticePoint2d{0, 1}, NoiseValues{0.4f, -0.5f, 0.2f}, -0.56647f}),
  generateTestName);

} // namespace pge::terrain
