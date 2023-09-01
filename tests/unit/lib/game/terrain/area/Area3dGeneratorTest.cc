
#include "Area3dGenerator.hh"
#include "IPoint.hh"
#include "Range.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
namespace {
struct TestCase
{
  Point3d p;

  Range xRange;
  Range yRange;
  Range zRange;
};

using Area3dTestSuite = TestWithParam<TestCase>;

auto generateTestname(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string str;
  str += std::to_string(info.param.p(0));
  str += "x";
  str += std::to_string(info.param.p(1));
  str += "x";
  str += std::to_string(info.param.p(2));

  std::replace(str.begin(), str.end(), '.', '_');
  std::replace(str.begin(), str.end(), '-', 'm');
  return str;
}
} // namespace

TEST_P(Area3dTestSuite, Test)
{
  const auto param = GetParam();

  Area3dGenerator generator;
  const auto area = generator.areaSurrounding(param.p);

  EXPECT_EQ(area.points[Area3dGenerator::FRONT_TOP_LEFT](0), param.xRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_TOP_LEFT](1), param.yRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_TOP_LEFT](2), param.zRange.second);

  EXPECT_EQ(area.points[Area3dGenerator::FRONT_TOP_RIGHT](0), param.xRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_TOP_RIGHT](1), param.yRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_TOP_RIGHT](2), param.zRange.second);

  EXPECT_EQ(area.points[Area3dGenerator::FRONT_BOTTOM_RIGHT](0), param.xRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_BOTTOM_RIGHT](1), param.yRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_BOTTOM_RIGHT](2), param.zRange.first);

  EXPECT_EQ(area.points[Area3dGenerator::FRONT_BOTTOM_LEFT](0), param.xRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_BOTTOM_LEFT](1), param.yRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::FRONT_BOTTOM_LEFT](2), param.zRange.first);

  // Back
  EXPECT_EQ(area.points[Area3dGenerator::BACK_TOP_LEFT](0), param.xRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_TOP_LEFT](1), param.yRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_TOP_LEFT](2), param.zRange.second);

  EXPECT_EQ(area.points[Area3dGenerator::BACK_TOP_RIGHT](0), param.xRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_TOP_RIGHT](1), param.yRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_TOP_RIGHT](2), param.zRange.second);

  EXPECT_EQ(area.points[Area3dGenerator::BACK_BOTTOM_RIGHT](0), param.xRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_BOTTOM_RIGHT](1), param.yRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_BOTTOM_RIGHT](2), param.zRange.first);

  EXPECT_EQ(area.points[Area3dGenerator::BACK_BOTTOM_LEFT](0), param.xRange.first);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_BOTTOM_LEFT](1), param.yRange.second);
  EXPECT_EQ(area.points[Area3dGenerator::BACK_BOTTOM_LEFT](2), param.zRange.first);
}

INSTANTIATE_TEST_SUITE_P(
  Unit_Terrain_AreaGenerator,
  Area3dTestSuite,
  Values(TestCase{Point3d{0.0f, 0.0f, 0.0f}, Range{0, 1}, Range{0, 1}, Range{0, 1}},
         TestCase{Point3d{0.2f, 0.3f, -0.1f}, Range{0, 1}, Range{0, 1}, Range{-1, 0}},
         TestCase{Point3d{0.7f, 0.1f, 0.25f}, Range{0, 1}, Range{0, 1}, Range{0, 1}},
         TestCase{Point3d{0.9f, 0.51f, 0.35f}, Range{0, 1}, Range{0, 1}, Range{0, 1}},
         TestCase{Point3d{0.02f, 0.98f, -0.32f}, Range{0, 1}, Range{0, 1}, Range{-1, 0}},
         TestCase{Point3d{1.0f, 0.0f, -1.98f}, Range{1, 2}, Range{0, 1}, Range{-2, -1}},
         TestCase{Point3d{-0.6f, 1.4f, 7.08f}, Range{-1, 0}, Range{1, 2}, Range{7, 8}},
         TestCase{Point3d{-1.7f, -1.99f, -34.1f}, Range{-2, -1}, Range{-2, -1}, Range{-35, -34}}),
  generateTestname);

} // namespace pge::terrain
