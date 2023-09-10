
#include "ValueGenerator.hh"
#include "IValueGeneratorPreparer.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {

template<typename ValueGeneratorToTest>
class Unit_Terrain_ValueGenerator
  : public GeneratorPreparer<ValueGeneratorToTest, ValueGeneratorToTest::DIMENSION, float>,
    public Test
{
  using LatticePoint = ILatticePoint<ValueGeneratorToTest::DIMENSION>;
  using Point        = IPoint<ValueGeneratorToTest::DIMENSION>;

  protected:
  void SetUp() override
  {
    this->prepareGenerator();
  }

  void testUseHasher()
  {
    EXPECT_CALL(*this->mockHasher, hash(_)).Times(1);
    this->generator->generateFor(LatticePoint::Zero(), Point::Zero());
  }

  void testUseNoise()
  {
    EXPECT_CALL(*this->mockNoise, seed(_)).Times(1);
    EXPECT_CALL(*this->mockNoise, next()).Times(1);
    this->generator->generateFor(LatticePoint::Zero(), Point::Zero());
  }

  void testGeneratFor()
  {
    ON_CALL(*this->mockHasher, hash(_)).WillByDefault(Return(1));
    ON_CALL(*this->mockNoise, next()).WillByDefault(Return(1.0f));
    const auto actual = this->generator->generateFor(LatticePoint::Zero(), Point::Zero());
    EXPECT_EQ(1.0f, actual);
  }
};

namespace dim2d {
using Unit_Terrain_ValueGenerator2d = Unit_Terrain_ValueGenerator<ValueGenerator2d>;

TEST_F(Unit_Terrain_ValueGenerator2d, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_ValueGenerator2d, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_ValueGenerator2d, Test_GenerateFor)
{
  this->testGeneratFor();
}
} // namespace dim2d

namespace dim3d {
using Unit_Terrain_ValueGenerator3d = Unit_Terrain_ValueGenerator<ValueGenerator3d>;

TEST_F(Unit_Terrain_ValueGenerator3d, Test_UseHasher)
{
  this->testUseHasher();
}

TEST_F(Unit_Terrain_ValueGenerator3d, Test_UseNoise)
{
  this->testUseNoise();
}

TEST_F(Unit_Terrain_ValueGenerator3d, Test_GenerateFor)
{
  this->testGeneratFor();
}
} // namespace dim3d

} // namespace pge::terrain
