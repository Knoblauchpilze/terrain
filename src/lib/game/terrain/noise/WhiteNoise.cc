
#include "WhiteNoise.hh"

namespace pge::noise {

WhiteNoise::WhiteNoise(const Seed seed)
  : Noise2d(Type::White, seed)
  , m_generator()
  , m_distribution(0.0f, 1.0f)
{}

auto WhiteNoise::next() const noexcept -> float
{
  // https://stackoverflow.com/questions/22923551/generating-number-0-1-using-mersenne-twister-c
  return m_distribution(m_generator);
}

void WhiteNoise::seed(const Seed seed)
{
  m_generator.seed(seed);
}

} // namespace pge::noise
