
#include "WhiteNoise.hh"
#include <chrono>

namespace pge::noise {

constexpr auto MIN_NOISE_VALUE = 0.0f;
constexpr auto MAX_NOISE_VALUE = 1.0f;

WhiteNoise::WhiteNoise(IHasherPtr hasher) noexcept
  : m_hasher(std::move(hasher))
  , m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(MIN_NOISE_VALUE, MAX_NOISE_VALUE)
{}

WhiteNoise::WhiteNoise(IHasherPtr hasher, const float min, const float max) noexcept
  : m_hasher(std::move(hasher))
  , m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(min, max)
{}

void WhiteNoise::seed(const int x, const int y)
{
  m_generator.seed(m_hasher->hash(x, y));
}

auto WhiteNoise::at(const int /*x*/, const int /*y*/) const noexcept -> float
{
  // https://stackoverflow.com/questions/22923551/generating-number-0-1-using-mersenne-twister-c
  return m_distribution(m_generator);
}

} // namespace pge::noise
