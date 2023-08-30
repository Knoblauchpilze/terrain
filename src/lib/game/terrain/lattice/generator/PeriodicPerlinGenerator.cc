
#include "PeriodicPerlinGenerator.hh"
#include <random>

#include <chrono>

namespace pge::lattice {

PeriodicPerlinGenerator::PeriodicPerlinGenerator(const int period, const noise::Seed seed)
  : m_period(period)
  , m_modulusMask(m_period - 1)
{
  if (period % 2 != 0)
  {
    throw std::invalid_argument("Period " + std::to_string(period) + " is not a multiple of 2");
  }
  generate(seed);
}

auto PeriodicPerlinGenerator::at(const utils::Vector2i &latticePoint) const noexcept
  -> utils::Vector2f
{
  this->modulusDuration = 0;
  this->permDuration    = 0;
  this->gradDuration    = 0;
  const auto st         = std::chrono::steady_clock::now();

  // https://stackoverflow.com/questions/3072665/bitwise-and-in-place-of-modulus-operator
  const auto xMod = latticePoint.x() & m_modulusMask;
  const auto yMod = latticePoint.y() & m_modulusMask;

  const auto p1 = std::chrono::steady_clock::now();

  const auto id = m_permutations[m_permutations[xMod] + yMod];

  const auto p2 = std::chrono::steady_clock::now();

  const auto grad = m_gradients[id];

  const auto p3         = std::chrono::steady_clock::now();
  this->modulusDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(p1 - st).count();
  this->permDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count();
  this->gradDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(p3 - p2).count();

  return grad;
}

void PeriodicPerlinGenerator::generate(const noise::Seed seed)
{
  std::mt19937 generator(seed);
  /// TODO: The gradient should not be completely random, see here:
  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

  m_gradients.resize(m_period);
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  std::for_each(m_gradients.begin(),
                m_gradients.end(),
                [&distribution, &generator](utils::Vector2f &grad) {
                  grad.x() = distribution(generator);
                  grad.y() = distribution(generator);

                  grad.normalize();
                });

  auto id = 0;
  for (const auto &v : m_gradients)
  {
    std::cout << "grad[" << id << "]: " << v.toString() << std::endl;
    ++id;
  }

  generatePermutationsTable(seed);
}

void PeriodicPerlinGenerator::generatePermutationsTable(const noise::Seed seed)
{
  std::mt19937 generator(seed);
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

} // namespace pge::lattice
