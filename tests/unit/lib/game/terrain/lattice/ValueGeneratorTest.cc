
#include "ValueGenerator.hh"
#include "HasherMock.hh"
#include "IValueGeneratorPreparer.hh"
#include "NoiseMock.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::lattice {
class Unit_ValueGenerator : public GeneratorPreparer<ValueGenerator>, public Test
{
  protected:
  void SetUp() override
  {
    prepareGenerator();
  }
};

TEST_F(Unit_ValueGenerator, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_, _)).Times(1);
  generator->generateFor(utils::Vector2i(), utils::Vector2f());
}

TEST_F(Unit_ValueGenerator, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_)).Times(1);
  EXPECT_CALL(*mockNoise, next()).Times(1);
  generator->generateFor(utils::Vector2i(), utils::Vector2f());
}

} // namespace pge::lattice
