
#include "ValueLattice.hh"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Bilinear.hh"
#include "Hasher.hh"
#include "WhiteNoise.hh"

using namespace ::testing;

namespace pge::lattice {
namespace {

// http://google.github.io/googletest/gmock_for_dummies.html#writing-the-mock-class
class MockHasher : public IHasher
{
  public:
  MOCK_METHOD(float, hash, (const int, const int), (override));
};

class MockNoise : public noise::INoise
{
  public:
  MOCK_METHOD(void, seed, (const noise::Seed), (override));
  MOCK_METHOD(float, next, (), (const, noexcept, override));
};

class MockInterpolator : public interpolation::IInterpolator
{
  public:
  MOCK_METHOD(float,
              interpolate,
              (const float, const float, const float, const float, const float, const float),
              (const, override));
};

class ValueLatticePreparer
{
  protected:
  MockHasher *mockHasher{nullptr};
  MockNoise *mockNoise{nullptr};
  MockInterpolator *mockInterpolator{nullptr};

  ILatticePtr lattice{};

  void prepareLattice()
  {
    auto hasher       = std::make_unique<NiceMock<MockHasher>>();
    mockHasher        = hasher.get();
    auto noise        = std::make_unique<NiceMock<MockNoise>>();
    mockNoise         = noise.get();
    auto interpolator = std::make_unique<NiceMock<MockInterpolator>>();
    mockInterpolator  = interpolator.get();

    lattice = std::make_unique<ValueLattice>(std::move(hasher),
                                             std::move(noise),
                                             std::move(interpolator));
  }
};
} // namespace

class ValueLatticeTest : public ValueLatticePreparer, public ::testing::Test
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

TEST_F(ValueLatticeTest, Test_UseHasher)
{
  EXPECT_CALL(*mockHasher, hash(_, _)).Times(4);
  lattice->at(0, 0);
}

TEST_F(ValueLatticeTest, Test_UseNoise)
{
  EXPECT_CALL(*mockNoise, seed(_)).Times(4);
  EXPECT_CALL(*mockNoise, next()).Times(4);
  lattice->at(0, 0);
}

TEST_F(ValueLatticeTest, Test_UseInterpolate)
{
  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, _, _)).Times(1);
  lattice->at(0, 0);
}

template<typename TestCaseType>
auto generateTestNameLattice(const TestParamInfo<TestCaseType> &info) -> std::string
{
  auto str = std::to_string(info.param.x) + "x" + std::to_string(info.param.y);
  std::replace(str.begin(), str.end(), '.', '_');
  return str;
}

template<typename TestCaseType>
class ValueLatticeTestSuite : public ValueLatticePreparer,
                              public ::testing::TestWithParam<TestCaseType>
{
  protected:
  void SetUp() override
  {
    prepareLattice();
  }
};

namespace hasher_test_suite {
struct TestCaseLatticeHasher
{
  int x;
  int y;

  std::vector<int> expectedX;
  std::vector<int> expectedY;
};

using ValueLatticeHasherTestSuite = ValueLatticeTestSuite<TestCaseLatticeHasher>;
TEST_P(ValueLatticeHasherTestSuite, Test_HasherCorrectlyCalled)
{
  const auto param = GetParam();

  ASSERT_EQ(param.expectedX.size(), param.expectedY.size());
  for (auto i = 0u; i < param.expectedX.size(); ++i)
  {
    EXPECT_CALL(*mockHasher, hash(param.expectedX[i], param.expectedY[i])).Times(1);
  }
  lattice->at(param.x, param.y);
}

INSTANTIATE_TEST_SUITE_P(Unit_ValueLattice,
                         ValueLatticeHasherTestSuite,
                         Values(TestCaseLatticeHasher{0, 0, {0, 1, 1, 0}, {0, 0, 1, 1}},
                                TestCaseLatticeHasher{1, 0, {1, 2, 2, 1}, {0, 0, 1, 1}},
                                TestCaseLatticeHasher{1, 1, {1, 2, 2, 1}, {1, 1, 2, 2}},
                                TestCaseLatticeHasher{0, 1, {0, 1, 1, 0}, {1, 1, 2, 2}}),
                         generateTestNameLattice<TestCaseLatticeHasher>);
} // namespace hasher_test_suite

namespace interpolator_test_suite {
struct TestCaseLatticeInterpolator
{
  float x;
  float y;

  float px;
  float py;
};

using ValueLatticeInterpolatorTestSuite = ValueLatticeTestSuite<TestCaseLatticeInterpolator>;
TEST_P(ValueLatticeInterpolatorTestSuite, Test_InterpolateCorrectlyCalled)
{
  const auto param = GetParam();

  EXPECT_CALL(*mockInterpolator, interpolate(_, _, _, _, param.px, param.py)).Times(1);
  lattice->at(param.x, param.y);
}

INSTANTIATE_TEST_SUITE_P(Unit_ValueLattice,
                         ValueLatticeInterpolatorTestSuite,
                         Values(TestCaseLatticeInterpolator{0.0f, 0.0f, 0.0f, 0.0f},
                                TestCaseLatticeInterpolator{0.5f, 0.0f, 0.5f, 0.0f},
                                TestCaseLatticeInterpolator{0.0f, 0.5f, 0.0f, 0.5f},
                                TestCaseLatticeInterpolator{0.2f, 0.3f, 0.2f, 0.3f},
                                TestCaseLatticeInterpolator{0.7f, 0.1f, 0.7f, 0.1f},
                                TestCaseLatticeInterpolator{0.9f, 0.51f, 0.9f, 0.51f},
                                TestCaseLatticeInterpolator{0.02f, 0.98f, 0.02f, 0.98f}),
                         generateTestNameLattice<TestCaseLatticeInterpolator>);
} // namespace interpolator_test_suite

} // namespace pge::lattice
