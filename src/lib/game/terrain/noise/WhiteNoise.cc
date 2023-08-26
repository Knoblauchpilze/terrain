
#include "WhiteNoise.hh"
#include <chrono>

namespace pge::noise {

constexpr auto MIN_NOISE_VALUE = 0.0f;
constexpr auto MAX_NOISE_VALUE = 1.0f;

WhiteNoise::WhiteNoise() noexcept
  : m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(MIN_NOISE_VALUE, MAX_NOISE_VALUE)
{}

WhiteNoise::WhiteNoise(const float min, const float max) noexcept
  : m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(min, max)
{}

void WhiteNoise::seed(const Seed seed)
{
  m_generator.seed(seed);
}

auto WhiteNoise::next() const noexcept -> float
{
  // https://stackoverflow.com/questions/22923551/generating-number-0-1-using-mersenne-twister-c
  return m_distribution(m_generator);
}

} // namespace pge::noise
