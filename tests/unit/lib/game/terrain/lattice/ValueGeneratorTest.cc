
#include "ValueGenerator.hh"
#include "IValueGeneratorPreparer.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::lattice {
class Unit_Lattice_ValueGenerator : public GeneratorPreparer<ValueGenerator>, public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

TEST_F(Unit_Lattice_ValueGenerator, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_, _)).Times(1);
  EXPECT_CALL(*mockNoise, at(_, _)).Times(1);
  generator->generateFor(utils::Vector2i(), utils::Vector2f());
}

TEST_F(Unit_Lattice_ValueGenerator, Test_GenerateFor)
{
  ON_CALL(*mockNoise, at(_, _)).WillByDefault(Return(1.0f));
  const auto actual = generator->generateFor(utils::Vector2i(), utils::Vector2f());
  EXPECT_EQ(1.0f, actual);
}

} // namespace pge::lattice
