
#include "GradientLattice.hh"
#include "ILatticePreparer.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::lattice {
class Unit_Lattice_GradientLattice : public LatticePreparer<GradientLattice>, public Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_F(Unit_Lattice_GradientLattice, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_, _)).Times(4);
  lattice->at(0, 0);
}

TEST_F(Unit_Lattice_GradientLattice, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_)).Times(4);
  EXPECT_CALL(*mockNoise, next()).Times(8);
  lattice->at(0, 0);
}

TEST_F(Unit_Lattice_GradientLattice, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, _, _)).Times(1);
  lattice->at(0, 0);
}

namespace {
struct TestCase
{
  float x;
  float y;

  float px;
  float py;
};

class InterpolateGradientTestSuite : public LatticePreparer<GradientLattice>,
                                     public TestWithParam<TestCase>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

TEST_P(InterpolateGradientTestSuite, Test_Interpolate)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, param.px, param.py)).Times(1);
  lattice->at(param.x, param.y);
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Unit_Lattice_GradientLattice,
                         InterpolateGradientTestSuite,
                         Values(TestCase{0.0f, 0.0f, 0.0f, 0.0f},
                                TestCase{0.5f, 0.0f, 0.5f, 0.0f},
                                TestCase{0.0f, 0.5f, 0.0f, 0.5f},
                                TestCase{0.2f, 0.3f, 0.2f, 0.3f},
                                TestCase{0.7f, 0.1f, 0.7f, 0.1f},
                                TestCase{0.9f, 0.51f, 0.9f, 0.51f},
                                TestCase{0.02f, 0.98f, 0.02f, 0.98f}),
                         generateTestName);

} // namespace pge::lattice
