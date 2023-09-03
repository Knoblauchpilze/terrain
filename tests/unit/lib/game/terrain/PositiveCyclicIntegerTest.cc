
#include "PositiveCyclicInteger.hh"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace ::testing;

namespace pge::terrain {

TEST(Unit_Terrain_PositiveCyclicInteger, InvalidMinThrowException)
{
  EXPECT_THROW(PositiveCyclicInteger(-1, 2, 3, 2), std::invalid_argument);
}

TEST(Unit_Terrain_PositiveCyclicInteger, InvalidMaxThrowException)
{
  EXPECT_THROW(PositiveCyclicInteger(1, 2, -2, 2), std::invalid_argument);
}

TEST(Unit_Terrain_PositiveCyclicInteger, InvalidStepThrowException)
{
  EXPECT_THROW(PositiveCyclicInteger(1, 2, 3, -1), std::invalid_argument);
  EXPECT_THROW(PositiveCyclicInteger(1, 2, 3, 0), std::invalid_argument);
  EXPECT_THROW(PositiveCyclicInteger(1, 2, 3, 1), std::invalid_argument);
}

TEST(Unit_Terrain_PositiveCyclicInteger, InvalidValueThrowException)
{
  EXPECT_THROW(PositiveCyclicInteger(1, 0, 3, 2), std::invalid_argument);
  EXPECT_THROW(PositiveCyclicInteger(1, 4, 3, 2), std::invalid_argument);
}

TEST(Unit_Terrain_PositiveCyclicInteger, ConstructorAssignExpectedValue)
{
  auto ci = PositiveCyclicInteger(1, 1, 3, 2);
  EXPECT_EQ(1, ci.current());

  ci = PositiveCyclicInteger(1, 2, 3, 2);
  EXPECT_EQ(2, ci.current());

  ci = PositiveCyclicInteger(1, 3, 3, 2);
  EXPECT_EQ(3, ci.current());
}

TEST(Unit_Terrain_PositiveCyclicInteger, NextUpdateValue)
{
  auto ci = PositiveCyclicInteger(1, 1, 3, 2);
  EXPECT_EQ(1, ci.current());

  ci.next();
  EXPECT_EQ(2, ci.current());
}

TEST(Unit_Terrain_PositiveCyclicInteger, WhenValueExceedMaxExpectReturnToMin)
{
  auto ci = PositiveCyclicInteger(1, 2, 3, 2);
  EXPECT_EQ(2, ci.current());

  ci.next();
  EXPECT_EQ(1, ci.current());
}

TEST(Unit_Terrain_PositiveCyclicInteger, WhenValueIsMaxExpectNoCycling)
{
  auto ci = PositiveCyclicInteger(1, 2, 4, 2);
  EXPECT_EQ(2, ci.current());

  ci.next();
  EXPECT_EQ(4, ci.current());
}

} // namespace pge::terrain
