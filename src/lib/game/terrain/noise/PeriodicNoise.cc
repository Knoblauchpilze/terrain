
#include "PeriodicNoise.hh"
#include <chrono>
#include <random>

#include <iostream>

// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-2D-noise.html

namespace pge::noise {

PeriodicNoise::PeriodicNoise(const int period, const Seed seed) noexcept
  : m_period(period)
  // // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  , m_modulusMask(m_period - 1)
  , m_seed(seed)
{
  generate();
}

PeriodicNoise::PeriodicNoise(const int period,
                             const Seed seed,
                             const float min,
                             const float max) noexcept
  : m_period(period)
  , m_modulusMask(m_period - 1)
  , m_min(min)
  , m_max(max)
  , m_seed(seed)
{
  generate();
}

void PeriodicNoise::seed(const int /*x*/, const int /*y*/)
{
  // No op.
}

auto PeriodicNoise::at(const int x, const int y) const noexcept -> float
{
  // https://stackoverflow.com/questions/3072665/bitwise-and-in-place-of-modulus-operator
  const auto xMod = x & m_modulusMask;
  const auto yMod = y & m_modulusMask;

  const auto id = m_permutations[m_permutations[xMod] + yMod];

  return m_values.at(id);
}

void PeriodicNoise::generate()
{
  std::mt19937 generator(m_seed);
  std::uniform_real_distribution<float> distribution(m_min, m_max);

  m_values.resize(m_period);
  std::for_each(m_values.begin(), m_values.end(), [&distribution, &generator](float &val) {
    val = distribution(generator);
  });

  generatePermutationsTable();
}

void PeriodicNoise::generatePermutationsTable()
{
  std::mt19937 generator(m_seed);
  std::uniform_int_distribution<int> distribution(0, m_period - 1);

  m_permutations.resize(2 * m_period);
  // https://en.cppreference.com/w/cpp/algorithm/iota
  std::iota(m_permutations.begin(), m_permutations.end(), 0);

  for (auto i = 0; i < m_period; ++i)
  {
    auto k = distribution(generator);
    std::swap(m_permutations[i], m_permutations[k]);
    m_permutations[i + m_period] = m_permutations[i];
  }
}

} // namespace pge::noise
