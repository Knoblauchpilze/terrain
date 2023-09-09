
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

  std::replace(str.begin(), str.end(), '-', 'm');
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

namespace test_2d {
using Hasher2dTestSuite = HasherTestSuite<2>;
using TestCase2d        = TestCase<2>;

TEST(Unit_Terrain_Hasher2d, Test_ConsistentHashing)
{
  Hasher2d hash(DEFAULT_SEED);
  const LatticePoint2d p(0, 1);
  const auto h1 = hash.hash(p);
  const auto h2 = hash.hash(p);

  EXPECT_EQ(h1, h2);
}

TEST_P(Hasher2dTestSuite, Test_Hash)
{
  const auto param = GetParam();

  Hasher2d hash(DEFAULT_SEED);
  const auto actual = hash.hash(param.p);
  EXPECT_EQ(actual, param.expected);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_Hasher2d,
                         Hasher2dTestSuite,
                         Values(TestCase2d{LatticePoint2d(0, 1), 133065},
                                TestCase2d{LatticePoint2d(-40, 32), 4196248},
                                TestCase2d{LatticePoint2d(12, -6), 853969},
                                TestCase2d{LatticePoint2d(-84, -120), 15796064}),
                         generateHasherTestName<2>);
} // namespace test_2d

namespace test_3d {
using Hasher3dTestSuite = HasherTestSuite<3>;
using TestCase3d        = TestCase<3>;

TEST(Unit_Terrain_Hasher3d, Test_ConsistentHashing)
{
  Hasher3d hash(DEFAULT_SEED);
  const LatticePoint3d p(0, 1, 2);
  const auto h1 = hash.hash(p);
  const auto h2 = hash.hash(p);

  EXPECT_EQ(h1, h2);
}

TEST_P(Hasher3dTestSuite, Test_Hash)
{
  const auto param = GetParam();

  Hasher3d hash(DEFAULT_SEED);
  const auto actual = hash.hash(param.p);
  EXPECT_EQ(actual, param.expected);
}

INSTANTIATE_TEST_SUITE_P(Unit_Terrain_Hasher3d,
                         Hasher3dTestSuite,
                         Values(TestCase3d{LatticePoint3d(0, 1, 2), 2139},
                                TestCase3d{LatticePoint3d(-40, 32, 9), 9570553},
                                TestCase3d{LatticePoint3d(12, -6, 7), 1312875},
                                TestCase3d{LatticePoint3d(2, 4, -8), 67667},
                                TestCase3d{LatticePoint3d(-84, -120, 3), 31721737},
                                TestCase3d{LatticePoint3d(-17, 18, -19), 7276573},
                                TestCase3d{LatticePoint3d(8, -9, -21), 854139},
                                TestCase3d{LatticePoint3d(-29, -7, -2021), 265619501}),
                         generateHasherTestName<3>);
} // namespace test_3d

} // namespace pge::terrain
