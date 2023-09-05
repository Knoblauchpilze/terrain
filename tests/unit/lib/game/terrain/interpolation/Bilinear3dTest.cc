
#include "Bilinear3d.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
namespace {
constexpr auto FRONT_TOP_LEFT     = 0.0f;
constexpr auto FRONT_TOP_RIGHT    = 1.0f;
constexpr auto FRONT_BOTTOM_LEFT  = 2.0f;
constexpr auto FRONT_BOTTOM_RIGHT = 3.0f;

constexpr auto BACK_TOP_LEFT     = 4.0f;
constexpr auto BACK_TOP_RIGHT    = 5.0f;
constexpr auto BACK_BOTTOM_LEFT  = 6.0f;
constexpr auto BACK_BOTTOM_RIGHT = 7.0f;

auto generateInterpolationData(const float dx, const float dy, const float dz)
  -> InterpolationData3d
{
  InterpolationData3d data;
  data.axes[Bilinear3d::FRONT_BOTTOM] = InterpolationAxis(FRONT_BOTTOM_LEFT, FRONT_BOTTOM_RIGHT, dx);
  data.axes[Bilinear3d::FRONT_TOP]    = InterpolationAxis(FRONT_TOP_LEFT, FRONT_TOP_RIGHT, dx);
  data.axes[Bilinear3d::BACK_BOTTOM]  = InterpolationAxis(BACK_BOTTOM_LEFT, BACK_BOTTOM_RIGHT, dx);
  data.axes[Bilinear3d::BACK_TOP]     = InterpolationAxis(BACK_TOP_LEFT, BACK_TOP_RIGHT, dx);

  data.deltas[Bilinear3d::Z] = dz;
  data.deltas[Bilinear3d::Y] = dy;

  return data;
}
} // namespace

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Bottom_Left)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.0f, 0.0f, 0.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(FRONT_BOTTOM_LEFT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Bottom_Right)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(1.0f, 0.0f, 0.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(FRONT_BOTTOM_RIGHT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Top_Left)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.0f, 0.0f, 1.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(FRONT_TOP_LEFT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Top_Right)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(1.0f, 0.0f, 1.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(FRONT_TOP_RIGHT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Bottom_Left)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.0f, 1.0f, 0.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BACK_BOTTOM_LEFT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Bottom_Right)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(1.0f, 1.0f, 0.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BACK_BOTTOM_RIGHT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Top_Left)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.0f, 1.0f, 1.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BACK_TOP_LEFT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Top_Right)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(1.0f, 1.0f, 1.0f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BACK_TOP_RIGHT, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Bottom_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.5f, 0.0f, 0.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_BOTTOM_LEFT + FRONT_BOTTOM_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Top_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.5f, 0.0f, 1.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_TOP_LEFT + FRONT_TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Left_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.0f, 0.0f, 0.5f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_BOTTOM_LEFT + FRONT_TOP_LEFT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Right_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(1.0f, 0.0f, 0.5f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_BOTTOM_RIGHT + FRONT_TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Bottom_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.5f, 1.0f, 0.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (BACK_BOTTOM_LEFT + BACK_BOTTOM_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Top_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.5f, 1.0f, 1.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (BACK_TOP_LEFT + BACK_TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Left_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.0f, 1.0f, 0.5f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (BACK_BOTTOM_LEFT + BACK_TOP_LEFT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Right_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(1.0f, 1.0f, 0.5f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (BACK_BOTTOM_RIGHT + BACK_TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Bottom_Left_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.0f, 0.5f, 0.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_BOTTOM_LEFT + BACK_BOTTOM_LEFT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Bottom_Right_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(1.0f, 0.5f, 0.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_BOTTOM_RIGHT + BACK_BOTTOM_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Top_Left_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(0.0f, 0.5f, 1.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_TOP_LEFT + BACK_TOP_LEFT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Top_Right_Edge)
{
  const auto interpolator = Bilinear3d();

  const auto data     = generateInterpolationData(1.0f, 0.5f, 1.0f);
  const auto out      = interpolator.interpolate(data);
  const auto expected = (FRONT_TOP_RIGHT + BACK_TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Bottom_Left_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.2f, 0.4f, 0.1f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(3.6f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Bottom_Right_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.98f, 0.3f, 0.05f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(4.08f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Bottom_Left_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.4f, 0.72f, 0.49f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(4.3f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Bottom_Right_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.51f, 0.72f, 0.17f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(5.05f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Top_Left_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.08f, 0.49f, 0.99f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(2.06f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Front_Top_Right_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.88f, 0.23f, 0.501f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(2.798f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Top_Left_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.14f, 0.78f, 0.52f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(4.22f, out, REASONABLE_COMPARISON_THRESHOLD);
}

TEST(Unit_Terrain_Bilinear3d, Test_Interpolate_Back_Top_Right_Quadrant)
{
  const auto interpolator = Bilinear3d();

  const auto data = generateInterpolationData(0.64f, 0.67f, 0.64f);
  const auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(4.04f, out, REASONABLE_COMPARISON_THRESHOLD);
}

} // namespace pge::terrain
