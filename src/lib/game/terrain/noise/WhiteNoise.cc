
#include "WhiteNoise.hh"

namespace pge::noise {

WhiteNoise::WhiteNoise(const Seed seed)
  : Noise2d(Type::White)
  , m_generator(seed)
  , m_distribution(0.0f, 1.0f)
{}

auto WhiteNoise::at(float /*x*/, float /*y*/) const noexcept -> float
{
  return m_distribution(m_generator);
}

} // namespace pge::noise
