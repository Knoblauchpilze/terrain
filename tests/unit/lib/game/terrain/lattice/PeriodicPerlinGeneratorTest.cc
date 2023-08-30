
#include "PeriodicPerlinGenerator.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::lattice {
constexpr auto DEFAULT_PERIOD = 8;
constexpr auto DEFAULT_SEED   = 2023;

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

using Point        = utils::Vector2f;
using LatticePoint = utils::Vector2i;

TEST(Unit_Lattice_PeriodicPerlinGenerator, Test_PeriodOddThrowException)
{
  EXPECT_THROW(PeriodicPerlinGenerator(3, DEFAULT_SEED), std::invalid_argument);
}

TEST(Unit_Lattice_PeriodicPerlinGenerator, Test_PeriodicX)
{
  PeriodicPerlinGenerator generator{DEFAULT_PERIOD, DEFAULT_SEED};

  auto p        = utils::Vector2i(0, 1);
  const auto v1 = generator.at(p);

  p             = utils::Vector2i(0 + DEFAULT_PERIOD, 1);
  const auto v2 = generator.at(p);
  EXPECT_NEAR(v1.x(), v2.x(), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1.y(), v2.y(), REASONABLE_COMPARISON_THRESHOLD);

  p             = utils::Vector2i(0 - 5 * DEFAULT_PERIOD, 1);
  const auto v3 = generator.at(p);
  EXPECT_NEAR(v1.x(), v3.x(), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1.y(), v3.y(), REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Lattice_PeriodicPerlinGenerator, Test_PeriodicY)
{
  PeriodicPerlinGenerator generator{DEFAULT_PERIOD, DEFAULT_SEED};

  auto p        = utils::Vector2i(0, 1);
  const auto v1 = generator.at(p);

  p             = utils::Vector2i(0, 1 + DEFAULT_PERIOD);
  const auto v2 = generator.at(p);
  EXPECT_NEAR(v1.x(), v2.x(), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1.y(), v2.y(), REASONABLE_COMPARISON_THRESHOLD);

  p             = utils::Vector2i(0, 1 - 3 * DEFAULT_PERIOD);
  const auto v3 = generator.at(p);
  EXPECT_NEAR(v1.x(), v3.x(), REASONABLE_COMPARISON_THRESHOLD);
  EXPECT_NEAR(v1.y(), v3.y(), REASONABLE_COMPARISON_THRESHOLD);
}

namespace at {
struct TestCase
{
  LatticePoint latticePoint;

  utils::Vector2f expected;

  int period{DEFAULT_PERIOD};
  noise::Seed seed{DEFAULT_SEED};
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using AtTestSuite = TestWithParam<TestCase>;

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;

  str += std::to_string(info.param.latticePoint.x());
  str += "x";
  str += std::to_string(info.param.latticePoint.y());

  str += "_";

  str += std::to_string(info.param.expected.x());
  str += "x";
  str += std::to_string(info.param.expected.y());

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}

TEST_P(AtTestSuite, Test_At)
{
  const auto param = GetParam();
  PeriodicPerlinGenerator generator{param.period, param.seed};

  const auto actual = generator.at(param.latticePoint);
  EXPECT_NEAR(actual.x(), param.expected.x(), param.threshold);
  EXPECT_NEAR(actual.y(), param.expected.y(), param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_PeriodicPerlinGenerator,
                         AtTestSuite,
                         Values(TestCase{LatticePoint(0, 1),
                                         utils::Vector2f(-0.842704f, -0.538378f)},
                                TestCase{LatticePoint(1, 2), utils::Vector2f(0.456030f, 0.889964f)}),
                         generateTestName);
} // namespace at

namespace generate_for {
struct TestCase
{
  Point point;
  LatticePoint latticePoint;

  float expected;

  int period{DEFAULT_PERIOD};
  noise::Seed seed{DEFAULT_SEED};
  float threshold{REASONABLE_COMPARISON_THRESHOLD};
};

using PerlinGenerateForTestSuite = TestWithParam<TestCase>;

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;
  str += std::to_string(info.param.point.x());
  str += "x";
  str += std::to_string(info.param.point.y());

  str += "_";

  str += std::to_string(info.param.latticePoint.x());
  str += "x";
  str += std::to_string(info.param.latticePoint.y());

  str += "_";

  str += std::to_string(info.param.expected);

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}

TEST_P(PerlinGenerateForTestSuite, Test_GenerateFor)
{
  const auto param = GetParam();
  PeriodicPerlinGenerator generator{param.period, param.seed};

  const auto actual = generator.generateFor(param.latticePoint, param.point);
  EXPECT_NEAR(actual, param.expected, param.threshold);
}

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_PeriodicPerlinGenerator,
                         PerlinGenerateForTestSuite,
                         Values(TestCase{Point(0.2f, 0.3f), LatticePoint(0, 1), 0.208323f},
                                TestCase{Point(1.2f, 2.3f), LatticePoint(1, 2), 0.358195f},
                                TestCase{Point(-0.2f, 1.45f), LatticePoint(-1, 2), 0.874921f},
                                TestCase{Point(-0.89f, -0.37f), LatticePoint(-1, 0), 0.004732f},
                                TestCase{Point(0.78f, -0.37f), LatticePoint(1, -1), -0.575866f}),
                         generateTestName);
} // namespace generate_for
} // namespace pge::lattice