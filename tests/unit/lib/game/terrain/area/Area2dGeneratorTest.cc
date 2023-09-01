
#include "Area2dGenerator.hh"
#include "IPoint.hh"
#include "Range.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
namespace {
struct TestCase
{
  Point2d p;

  Range xRange;
  Range yRange;
};

using Area2dTestSuite = TestWithParam<TestCase>;

auto generateTestname(const TestParamInfo<TestCase> &info) -> std::string
{
  auto str = std::to_string(info.param.p(0)) + "x" + std::to_string(info.param.p(1));
  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}
} // namespace

TEST_P(Area2dTestSuite, Test)
{
  const auto param = GetParam();

  Area2dGenerator generator;
  const auto area = generator.areaSurrounding(param.p);

  EXPECT_EQ(area.points[Area2dGenerator::TOP_LEFT](0), param.xRange.first);
  EXPECT_EQ(area.points[Area2dGenerator::TOP_LEFT](1), param.yRange.second);

  EXPECT_EQ(area.points[Area2dGenerator::TOP_RIGHT](0), param.xRange.second);
  EXPECT_EQ(area.points[Area2dGenerator::TOP_RIGHT](1), param.yRange.second);

  EXPECT_EQ(area.points[Area2dGenerator::BOTTOM_LEFT](0), param.xRange.first);
  EXPECT_EQ(area.points[Area2dGenerator::BOTTOM_LEFT](1), param.yRange.first);

  EXPECT_EQ(area.points[Area2dGenerator::BOTTOM_RIGHT](0), param.xRange.second);
  EXPECT_EQ(area.points[Area2dGenerator::BOTTOM_RIGHT](1), param.yRange.first);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_AreaGenerator,
                         Area2dTestSuite,
                         Values(TestCase{Point2d{0.0f, 0.0f}, Range{0, 1}, Range{0, 1}},
                                TestCase{Point2d{0.2f, 0.3f}, Range{0, 1}, Range{0, 1}},
                                TestCase{Point2d{0.7f, 0.1f}, Range{0, 1}, Range{0, 1}},
                                TestCase{Point2d{0.9f, 0.51f}, Range{0, 1}, Range{0, 1}},
                                TestCase{Point2d{0.02f, 0.98f}, Range{0, 1}, Range{0, 1}},
                                TestCase{Point2d{1.0f, 0.0f}, Range{1, 2}, Range{0, 1}},
                                TestCase{Point2d{-0.6f, 1.4f}, Range{-1, 0}, Range{1, 2}},
                                TestCase{Point2d{-1.7f, -1.99f}, Range{-2, -1}, Range{-2, -1}}),
                         generateTestname);

} // namespace pge::terrain
