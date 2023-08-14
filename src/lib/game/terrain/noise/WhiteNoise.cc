
#include "WhiteNoise.hh"

namespace pge::noise {

WhiteNoise::WhiteNoise(const Seed seed)
  : Noise2d(Type::White)
  , m_generator(seed)
  , m_distribution(0.0f, 1.0f)
{}

auto WhiteNoise::at(float /*x*/, float /*y*/) const noexcept -> float
{
  // https://stackoverflow.com/questions/22923551/generating-number-0-1-using-mersenne-twister-c
  return m_distribution(m_generator);
}

} // namespace pge::noise
