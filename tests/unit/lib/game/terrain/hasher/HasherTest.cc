
#include "Hasher.hh"
#include "ILatticePoint.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::terrain {
constexpr auto DEFAULT_SEED = 1993;

template<int Dimension>
struct TestCase
{
  ILatticePoint<Dimension> p;
  int expected;
};

template<int Dimension>
using HasherTestSuite = TestWithParam<TestCase<Dimension>>;

template<int Dimension>
auto generateHasherTestName(const TestParamInfo<TestCase<Dimension>> &info) -> std::string
{
  std::string str;
  for (auto i = 0; i < Dimension; ++i)
  {
    if (!str.empty())
    {
      str += "x";
    }
    str += std::to_string(info.param.p(i));
  }

  str += "_";
  str += std::to_string(info.param.expected);

  std::replace(str.begin(), str.end(), '-', '_');
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

namespace test_2d {
using Hasher2dTestSuite = HasherTestSuite<2>;
using TestCase2d        = TestCase<2>;

TEST(Unit_Terrain_Hasher2d, Test_ConsistentHashing)
{
  Hasher hash(DEFAULT_SEED);
  const auto h1 = hash.hash(0, 1);
  const auto h2 = hash.hash(0, 1);

  EXPECT_EQ(h1, h2);
}

TEST_P(Hasher2dTestSuite, Test_Hash)
{
  const auto param = GetParam();

  Hasher hash(DEFAULT_SEED);
  const auto actual = hash.hash(param.p(0), param.p(1));
  EXPECT_EQ(actual, param.expected);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_Hasher,
                         Hasher2dTestSuite,
                         Values(TestCase2d{LatticePoint2d(0, 1), 133065},
                                TestCase2d{LatticePoint2d(12, -6), 853969},
                                TestCase2d{LatticePoint2d(-40, 32), 4196248},
                                TestCase2d{LatticePoint2d(-84, -120), 15796064}),
                         generateHasherTestName<2>);
} // namespace test_2d

} // namespace pge::terrain
