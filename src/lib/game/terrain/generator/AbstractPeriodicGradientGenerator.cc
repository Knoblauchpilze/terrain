
#include "AbstractPeriodicGradientGenerator.hh"
#include <random>

namespace pge::terrain {

AbstractPeriodicGradientGenerator::AbstractPeriodicGradientGenerator(const int period,
                                                                     const Seed seed)
  : m_period(period)
  , m_modulusMask(m_period - 1)
{
  if (period % 2 != 0)
  {
    throw std::invalid_argument("Period " + std::to_string(period) + " is not a multiple of 2");
  }
  generatePermutationsTable(seed);
}

auto AbstractPeriodicGradientGenerator::at(const utils::Vector2i &latticePoint) const noexcept
  -> utils::Vector2f
{
  // https://stackoverflow.com/questions/3072665/bitwise-and-in-place-of-modulus-operator
  const auto xMod = latticePoint.x() & m_modulusMask;
  const auto yMod = latticePoint.y() & m_modulusMask;

  const auto id   = m_permutations[m_permutations[xMod] + yMod];
  const auto grad = gradientAt(id);

  return grad;
}

void AbstractPeriodicGradientGenerator::generatePermutationsTable(const Seed seed)
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

} // namespace pge::terrain
