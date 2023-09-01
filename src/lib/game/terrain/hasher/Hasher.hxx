
#pragma once

#include "Hasher.hh"

namespace pge::terrain {

template<int Dimension>
inline Hasher<Dimension>::Hasher(const Seed seed) noexcept
  : m_seed(seed)
{}

template<int Dimension>
inline auto Hasher<Dimension>::hash(const Point &p) -> int
{
  auto seed = p(0);
  for (auto i = 1; i < Dimension; ++i)
  {
    seed = hash2d(seed, p(i));
  }

  return seed;
}

template<int Dimension>
inline auto Hasher<Dimension>::abs(const int v) const noexcept -> int
{
  return (v < 0 ? -2 * v + 1 : 2 * v);
}

template<int Dimension>
inline auto Hasher<Dimension>::hash2d(const int v1, const int v2) -> int
{
  const auto abs1 = abs(v1);
  const auto abs2 = abs(v2);

  // https://gamedev.stackexchange.com/questions/183142/how-can-i-create-a-persistent-seed-for-each-chunk-of-an-infinite-procedural-worl
  static constexpr auto ENTROPY_BITS = 16;

  auto hash = abs1;
  hash ^= abs2 << ENTROPY_BITS;
  hash ^= abs2 >> ENTROPY_BITS;

  return hash ^ m_seed;
}

} // namespace pge::terrain
