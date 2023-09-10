
#include "GradientGenerator.hh"
#include "IValueGeneratorPreparer.hh"
#include "TestName.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {

using GradientGeneratorToTest = GradientGenerator2d;

namespace behavior {
class Unit_Terrain_GradientGenerator
  : public GeneratorPreparer<GradientGeneratorToTest, GradientGeneratorToTest::DIMENSION, Point3d>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }

  void testUseHasher()
  {
    EXPECT_CALL(*mockHasher, hash(_)).Times(1);
    generator->generateFor(ILatticePoint<GradientGeneratorToTest::DIMENSION>::Zero(),
                           IPoint<GradientGeneratorToTest::DIMENSION>::Zero());
  }

  void testUseNoise()
  {
    EXPECT_CALL(*mockNoise, seed(_)).Times(1);
    EXPECT_CALL(*mockNoise, next()).Times(3);
    generator->generateFor(ILatticePoint<GradientGeneratorToTest::DIMENSION>::Zero(),
                           IPoint<GradientGeneratorToTest::DIMENSION>::Zero());
  }
};

TEST_F(Unit_Terrain_GradientGenerator, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_GradientGenerator, Test_UseNoise)
{
  this->testUseNoise();
}
} // namespace behavior

namespace {
constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

using NoiseValues = std::vector<float>;

struct TestCase
{
  Point2d inPoint;
  LatticePoint2d latticePoint;

  NoiseValues noise{};

  float expected;
};

class GenerateForTestSuite
  : public GeneratorPreparer<GradientGeneratorToTest, GradientGeneratorToTest::DIMENSION, Point3d>,
    public TestWithParam<TestCase>
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

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

  const auto actual = generator->generateFor(param.latticePoint, param.inPoint);
  EXPECT_NEAR(param.expected, actual, REASONABLE_COMPARISON_THRESHOLD);
}

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
  testNameFromPointLatticePointAndExpected<TestCase>);
} // namespace
} // namespace pge::terrain
