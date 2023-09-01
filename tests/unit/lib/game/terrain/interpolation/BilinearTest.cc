
#include "Bilinear.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {

TEST(Unit_Terrain_Bilinear, Test_Interpolate_LatticePoints)
{
  auto interpolator = Bilinear();

  auto tl = 0.0f;
  auto tr = 1.0f;
  auto bl = 2.0f;
  auto br = 3.0f;

  auto out = interpolator.interpolate(tl, tr, br, bl, 0.0f, 0.0f);
  EXPECT_EQ(bl, out);

  out = interpolator.interpolate(tl, tr, br, bl, 1.0f, 0.0f);
  EXPECT_EQ(br, out);

  out = interpolator.interpolate(tl, tr, br, bl, 1.0f, 1.0f);
  EXPECT_EQ(tr, out);

  out = interpolator.interpolate(tl, tr, br, bl, 0.0f, 1.0f);
  EXPECT_EQ(tl, out);
}

TEST(Unit_Terrain_Bilinear, Test_Interpolate_X_Edges)
{
  auto interpolator = Bilinear();

  auto tl = 0.0f;
  auto tr = 1.0f;
  auto bl = 2.0f;
  auto br = 3.0f;

  auto out      = interpolator.interpolate(tl, tr, br, bl, 0.5f, 0.0f);
  auto expected = (bl + br) / 2.0f;
  EXPECT_EQ(expected, out);

  out      = interpolator.interpolate(tl, tr, br, bl, 0.5f, 1.0f);
  expected = (tl + tr) / 2.0f;
  EXPECT_EQ(expected, out);
}

TEST(Unit_Terrain_Bilinear, Test_Interpolate_Y_Edges)
{
  auto interpolator = Bilinear();

  auto tl = 0.0f;
  auto tr = 1.0f;
  auto bl = 2.0f;
  auto br = 3.0f;

  auto out      = interpolator.interpolate(tl, tr, br, bl, 0.0f, 0.5f);
  auto expected = (tl + bl) / 2.0f;
  EXPECT_EQ(expected, out);

  out      = interpolator.interpolate(tl, tr, br, bl, 1.0f, 0.5f);
  expected = (br + tr) / 2.0f;
  EXPECT_EQ(expected, out);
}

constexpr auto REASONABLE_COMPARISON_THRESHOLD = 0.0001f;

TEST(Unit_Terrain_Bilinear, Test_Interpolate_Quadrants)
{
  auto interpolator = Bilinear();

  auto tl = 0.0f;
  auto tr = 1.0f;
  auto bl = 2.0f;
  auto br = 3.0f;

  auto out = interpolator.interpolate(tl, tr, br, bl, 0.2f, 0.2f);
  EXPECT_NEAR(1.8f, out, REASONABLE_COMPARISON_THRESHOLD);

  out = interpolator.interpolate(tl, tr, br, bl, 0.6f, 0.2f);
  EXPECT_NEAR(2.2f, out, REASONABLE_COMPARISON_THRESHOLD);

  out = interpolator.interpolate(tl, tr, br, bl, 0.85f, 0.7f);
  EXPECT_NEAR(1.45f, out, REASONABLE_COMPARISON_THRESHOLD);

  out = interpolator.interpolate(tl, tr, br, bl, 0.1f, 0.9f);
  EXPECT_NEAR(0.3f, out, REASONABLE_COMPARISON_THRESHOLD);
}

} // namespace pge::terrain
