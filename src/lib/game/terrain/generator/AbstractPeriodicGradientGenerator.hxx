
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include <random>

namespace pge::terrain {

template<int Dimension>
inline AbstractPeriodicGradientGenerator<Dimension>::AbstractPeriodicGradientGenerator(
  const int period,
  const Seed seed)
  : AbstractGradientGenerator<Dimension>(NO_CACHE_SIZE_REQUIRED)
  , m_period(period)
  , m_modulusMask(m_period - 1)
{
  if (period % 2 != 0)
  {
    throw std::invalid_argument("Period " + std::to_string(period) + " is not a multiple of 2");
  }
  generatePermutationsTable(seed);
}

template<int Dimension>
inline auto AbstractPeriodicGradientGenerator<Dimension>::at(
  const ILatticePoint<Dimension> &latticePoint) const noexcept -> Point3d
{
  const auto id   = hash(latticePoint);
  const auto grad = gradientAt(id);

  return grad;
}

template<int Dimension>
inline void AbstractPeriodicGradientGenerator<Dimension>::generatePermutationsTable(const Seed seed)
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
  }

  for (auto i = 0; i < m_period; ++i)
  {
    m_permutations[i + m_period] = m_permutations[i];
  }
}

template<int Dimension>
inline auto AbstractPeriodicGradientGenerator<Dimension>::hash(
  const ILatticePoint<Dimension> &latticePoint) const -> int
{
  // https://stackoverflow.com/questions/3072665/bitwise-and-in-place-of-modulus-operator
  int seed = latticePoint(0) & m_modulusMask;

  for (int i = 1; i < latticePoint.size(); ++i)
  {
    const auto mod = latticePoint(i) & m_modulusMask;
    seed           = m_permutations[seed] + mod;
  }

  return m_permutations[seed];
}

} // namespace pge::terrain
