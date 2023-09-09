
#include "IValueGeneratorPreparer.hh"
#include "ValueGenerator.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
class Unit_Terrain_ValueGenerator2d : public GeneratorPreparer<ValueGenerator2d, 2, float>,
                                      public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

TEST_F(Unit_Terrain_ValueGenerator2d, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_)).Times(1);
  generator->generateFor(LatticePoint2d::Zero(), Point2d::Zero());
}

TEST_F(Unit_Terrain_ValueGenerator2d, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_)).Times(1);
  EXPECT_CALL(*mockNoise, next()).Times(1);
  generator->generateFor(LatticePoint2d::Zero(), Point2d::Zero());
}

TEST_F(Unit_Terrain_ValueGenerator2d, Test_GenerateFor)
{
  ON_CALL(*mockHasher, hash(_)).WillByDefault(Return(1));
  ON_CALL(*mockNoise, next()).WillByDefault(Return(1.0f));
  const auto actual = generator->generateFor(LatticePoint2d::Zero(), Point2d::Zero());
  EXPECT_EQ(1.0f, actual);
}

} // namespace pge::terrain
