
#include "GradientGenerator.hh"
#include "IValueGeneratorPreparer.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
class Unit_Terrain_GradientGenerator : public GeneratorPreparer<GradientGenerator, Point2d>,
                                       public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

TEST_F(Unit_Terrain_GradientGenerator, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_)).Times(1);
  generator->generateFor({}, {});
}

TEST_F(Unit_Terrain_GradientGenerator, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_)).Times(1);
  EXPECT_CALL(*mockNoise, next()).Times(2);
  generator->generateFor({}, {});
}

namespace {
using Point        = Point2d;
using LatticePoint = LatticePoint2d;
using NoiseValues  = std::vector<float>;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

struct TestCase
{
  Point point;
  LatticePoint latticePoint;

  NoiseValues noise;

  float expected;
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

class GenerateForTestSuite : public GeneratorPreparer<GradientGenerator, Point2d>,
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
  Unit_Terrain_GradientGenerator,
  GenerateForTestSuite,
  Values(TestCase{Point{0.2f, 0.3f}, LatticePoint{0, 1}, NoiseValues{1.0f, 0.0f}, 0.2f},
         TestCase{Point{0.2f, 0.3f}, LatticePoint{0, 1}, NoiseValues{0.0f, 1.0f}, -0.7f},
         TestCase{Point{0.0f, 0.0f}, LatticePoint{0, 0}, NoiseValues{0.5f, 0.6f}, 0.0f},
         TestCase{Point{-0.1f, 0.5f}, LatticePoint{0, 1}, NoiseValues{0.8f, 0.6f}, -0.38f}),
  generateTestName);

} // namespace pge::terrain
