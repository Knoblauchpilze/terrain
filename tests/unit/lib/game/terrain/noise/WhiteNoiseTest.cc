
#include "WhiteNoise.hh"
#include "Hasher.hh"
#include "MockHasher.hh"
#include <gtest/gtest.h>

using namespace ::testing;

namespace pge::noise {

TEST(Unit_Noise_WhiteNoise, Test_SeedUsesHasher)
{
  auto hasher = std::make_unique<MockHasher>();
  EXPECT_CALL(*hasher, hash(0, 1)).Times(1);

  auto n = std::make_unique<WhiteNoise>(std::move(hasher));
  n->seed(0, 1);
}

namespace {
constexpr auto DEFAULT_SEED = 10;
auto createWhiteNoise() -> INoisePtr
{
  auto hasher = std::make_unique<Hasher>(DEFAULT_SEED);
  auto out    = std::make_unique<WhiteNoise>(std::move(hasher));
  return out;
}
} // namespace

TEST(Unit_Noise_WhiteNoise, Test_ReturnSameValueAtAnyPoint)
{
  auto n = createWhiteNoise();

  n->seed(0, 1);
  const auto v1 = n->at(2, 3);

  n->seed(0, 1);
  const auto v2 = n->at(3, 4);

  EXPECT_EQ(v1, v2);
}

} // namespace pge::noise
