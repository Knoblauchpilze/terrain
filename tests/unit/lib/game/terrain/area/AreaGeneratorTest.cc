
#include "AreaGenerator.hh"
#include <gtest/gtest.h>
#include <maths_utils/Vector2.hh>

using namespace ::testing;

namespace pge::terrain {
namespace {
struct TestCase
{
  float x;
  float y;

  int minX;
  int maxX;
  int minY;
  int maxY;
};

using AreaTestSuite = TestWithParam<TestCase>;

auto generateTestname(const TestParamInfo<TestCase> &info) -> std::string
{
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}
} // namespace

TEST_P(AreaTestSuite, Test)
{
  const auto param = GetParam();

  AreaGenerator generator;
  const auto area = generator.areaSurrounding(param.x, param.y);

  EXPECT_EQ(area.topLeft.x(), param.minX);
  EXPECT_EQ(area.topLeft.y(), param.maxY);

  EXPECT_EQ(area.topRight.x(), param.maxX);
  EXPECT_EQ(area.topRight.y(), param.maxY);

  EXPECT_EQ(area.bottomLeft.x(), param.minX);
  EXPECT_EQ(area.bottomLeft.y(), param.minY);

  EXPECT_EQ(area.bottomRight.x(), param.maxX);
  EXPECT_EQ(area.bottomRight.y(), param.minY);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_AreaGenerator,
                         AreaTestSuite,
                         Values(TestCase{0.0f, 0.0f, 0, 1, 0, 1},
                                TestCase{0.2f, 0.3f, 0, 1, 0, 1},
                                TestCase{0.7f, 0.1f, 0, 1, 0, 1},
                                TestCase{0.9f, 0.51f, 0, 1, 0, 1},
                                TestCase{0.02f, 0.98f, 0, 1, 0, 1},
                                TestCase{1.0f, 0.0f, 1, 2, 0, 1},
                                TestCase{-0.6f, 1.4f, -1, 0, 1, 2},
                                TestCase{-1.7f, -1.99f, -2, -1, -2, -1}),
                         generateTestname);

} // namespace pge::terrain
