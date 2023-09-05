
#include "Bilinear2d.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
namespace {
constexpr auto TOP_LEFT     = 0.0f;
constexpr auto TOP_RIGHT    = 1.0f;
constexpr auto BOTTOM_LEFT  = 2.0f;
constexpr auto BOTTOM_RIGHT = 3.0f;
auto generateInterpolationData(const float dx, const float dy) -> InterpolationData2d
{
  InterpolationData2d data;
  data.axes[Bilinear2d::BOTTOM] = InterpolationAxis(BOTTOM_LEFT, BOTTOM_RIGHT, dx);
  data.axes[Bilinear2d::TOP]    = InterpolationAxis(TOP_LEFT, TOP_RIGHT, dx);
  data.deltas[Bilinear2d::Y]    = dy;
  return data;
}
} // namespace

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Bottom_Left)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(0.0f, 0.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BOTTOM_LEFT, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Bottom_Right)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(1.0f, 0.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BOTTOM_RIGHT, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Top_Left)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(0.0f, 1.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(TOP_LEFT, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Top_Right)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(1.0f, 1.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(TOP_RIGHT, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Bottom_Edge)
{
  const auto interpolator = Bilinear2d();

  const auto data     = generateInterpolationData(0.5f, 0.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (BOTTOM_LEFT + BOTTOM_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Top_Edge)
{
  const auto interpolator = Bilinear2d();

  const auto data     = generateInterpolationData(0.5f, 1.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (TOP_LEFT + TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Left_Edge)
{
  const auto interpolator = Bilinear2d();

  const auto data     = generateInterpolationData(0.0f, 0.5f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (TOP_LEFT + BOTTOM_LEFT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Right_Edge)
{
  const auto interpolator = Bilinear2d();

  const auto data     = generateInterpolationData(1.0f, 0.5f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (BOTTOM_RIGHT + TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Bottom_Left_Quadrant)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(0.2f, 0.2f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(1.8f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Bottom_Right_Quadrant)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(0.6f, 0.2f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(2.2f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Top_Left_Quadrant)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(0.1f, 0.9f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(0.3f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Top_Right_Quadrant)
{
  const auto interpolator = Bilinear2d();

  const auto data = generateInterpolationData(0.85f, 0.7f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(1.45f, out, REASONABLE_COMPARISON_THRESHOLD);
}

} // namespace pge::terrain
