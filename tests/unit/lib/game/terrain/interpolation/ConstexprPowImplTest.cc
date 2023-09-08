
#include "ConstexprPowImpl.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain::details {

TEST(Unit_Terrain_ConstexprPowImpl, PositiveToZeroPowerIs1)
{
  EXPECT_EQ(1, pow(1, 0u));
  EXPECT_EQ(1, pow(14, 0u));
}

TEST(Unit_Terrain_ConstexprPowImpl, NegativeToZeroPowerIs1)
{
  EXPECT_EQ(-1, pow(-1, 0u));
  EXPECT_EQ(-1, pow(-17, 0u));
}

TEST(Unit_Terrain_ConstexprPowImpl, ZeroToZeroIsAlways1)
{
  EXPECT_EQ(1, pow(0, 0u));
  EXPECT_EQ(1, pow(-0, 0u));
}

namespace eval {
struct TestCase
{
  int x;
  unsigned exp;

  int expected;
};

auto generateTestName(const TestParamInfo<TestCase> &info) -> std::string
{
  std::string out;

  out += std::to_string(info.param.x);
  out += "_";
  out += std::to_string(info.param.exp);

  std::replace(out.begin(), out.end(), '-', 'm');

  return out;
}

using EvalTestSuite = TestWithParam<TestCase>;

TEST_P(EvalTestSuite, Test_Evaluate)
{
  const auto param = GetParam();

  EXPECT_EQ(param.expected, pow(param.x, param.exp));
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_ConstexprPowImpl,
                         EvalTestSuite,
                         Values(TestCase{1, 1, 1},
                                TestCase{-1, 1, -1},
                                TestCase{2, 1, 2},
                                TestCase{-2, 1, -2},
                                TestCase{1, 2, 1},
                                TestCase{-1, 2, 1},
                                TestCase{2, 2, 4},
                                TestCase{-2, 2, 4},
                                TestCase{9, 3, 729},
                                TestCase{-6, 3, -216}),
                         generateTestName);
} // namespace eval

} // namespace pge::terrain::details
