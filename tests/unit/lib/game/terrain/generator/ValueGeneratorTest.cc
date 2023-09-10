
#include "IValueGeneratorPreparer.hh"
#include "ValueGenerator.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {

using ValueGeneratorToTest = ValueGenerator2d;

class Unit_Terrain_ValueGenerator
  : public GeneratorPreparer<ValueGeneratorToTest, ValueGeneratorToTest::DIMENSION, float>,
    public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }

  void testUseHasher()
  {
    EXPECT_CALL(*mockHasher, hash(_)).Times(1);
    generator->generateFor(ILatticePoint<ValueGeneratorToTest::DIMENSION>::Zero(),
                           IPoint<ValueGeneratorToTest::DIMENSION>::Zero());
  }

  void testUseNoise()
  {
    EXPECT_CALL(*mockNoise, seed(_)).Times(1);
    EXPECT_CALL(*mockNoise, next()).Times(1);
    generator->generateFor(ILatticePoint<ValueGeneratorToTest::DIMENSION>::Zero(),
                           IPoint<ValueGeneratorToTest::DIMENSION>::Zero());
  }

  void testGeneratFor()
  {
    ON_CALL(*mockHasher, hash(_)).WillByDefault(Return(1));
    ON_CALL(*mockNoise, next()).WillByDefault(Return(1.0f));
    const auto actual = generator->generateFor(ILatticePoint<ValueGeneratorToTest::DIMENSION>::Zero(),
                                               IPoint<ValueGeneratorToTest::DIMENSION>::Zero());
    EXPECT_EQ(1.0f, actual);
  }
};

TEST_F(Unit_Terrain_ValueGenerator, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_ValueGenerator, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_ValueGenerator, Test_GenerateFor)
{
  this->testGeneratFor();
}

} // namespace pge::terrain
