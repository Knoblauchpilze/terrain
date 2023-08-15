
#include "Noise.hh"
#include <chrono>

namespace pge::noise {

constexpr auto MIN_NOISE_VALUE = 0.0f;
constexpr auto MAX_NOISE_VALUE = 1.0f;

Noise::Noise() noexcept
  : INoise()
  , m_generator(std::chrono::system_clock::now().time_since_epoch().count())
  , m_distribution(MIN_NOISE_VALUE, MAX_NOISE_VALUE)
{}

void Noise::seed(const Seed seed)
{
  m_generator.seed(seed);
}

auto Noise::next() const noexcept -> float
{
  // https://stackoverflow.com/questions/22923551/generating-number-0-1-using-mersenne-twister-c
  return m_distribution(m_generator);
}

} // namespace pge::noise
