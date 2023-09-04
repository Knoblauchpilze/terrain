
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
  data.axes[0]   = InterpolationAxis(BOTTOM_LEFT, BOTTOM_RIGHT, dx);
  data.axes[1]   = InterpolationAxis(TOP_LEFT, TOP_RIGHT, dx);
  data.deltas[0] = dy;
  return data;
}
} // namespace

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_LatticePoints)
{
  auto interpolator = Bilinear2d();

  auto data = generateInterpolationData(0.0f, 0.0f);
  auto out  = interpolator.interpolate(data);
  EXPECT_EQ(BOTTOM_LEFT, out);

  data = generateInterpolationData(1.0f, 0.0f);
  out  = interpolator.interpolate(data);
  EXPECT_EQ(BOTTOM_RIGHT, out);

  data = generateInterpolationData(1.0f, 1.0f);
  out  = interpolator.interpolate(data);
  EXPECT_EQ(TOP_RIGHT, out);

  data = generateInterpolationData(0.0f, 1.0f);
  out  = interpolator.interpolate(data);
  EXPECT_EQ(TOP_LEFT, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_X_Edges)
{
  auto interpolator = Bilinear2d();

  auto data     = generateInterpolationData(0.5f, 0.0f);
  auto out      = interpolator.interpolate(data);
  auto expected = (BOTTOM_LEFT + BOTTOM_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);

  data     = generateInterpolationData(0.5f, 1.0f);
  out      = interpolator.interpolate(data);
  expected = (TOP_LEFT + TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Y_Edges)
{
  auto interpolator = Bilinear2d();

  auto data     = generateInterpolationData(0.0f, 0.5f);
  auto out      = interpolator.interpolate(data);
  auto expected = (TOP_LEFT + BOTTOM_LEFT) / 2.0f;
  EXPECT_EQ(expected, out);

  data     = generateInterpolationData(1.0f, 0.5f);
  out      = interpolator.interpolate(data);
  expected = (BOTTOM_RIGHT + TOP_RIGHT) / 2.0f;
  EXPECT_EQ(expected, out);
}

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Terrain_Bilinear2d, Test_Interpolate_Quadrants)
{
  auto interpolator = Bilinear2d();

  auto data = generateInterpolationData(0.2f, 0.2f);
  auto out  = interpolator.interpolate(data);
  EXPECT_NEAR(1.8f, out, REASONABLE_COMPARISON_THRESHOLD);

  data = generateInterpolationData(0.6f, 0.2f);
  out  = interpolator.interpolate(data);
  EXPECT_NEAR(2.2f, out, REASONABLE_COMPARISON_THRESHOLD);

  data = generateInterpolationData(0.85f, 0.7f);
  out  = interpolator.interpolate(data);
  EXPECT_NEAR(1.45f, out, REASONABLE_COMPARISON_THRESHOLD);

  data = generateInterpolationData(0.1f, 0.9f);
  out  = interpolator.interpolate(data);
  EXPECT_NEAR(0.3f, out, REASONABLE_COMPARISON_THRESHOLD);
}

} // namespace pge::terrain
