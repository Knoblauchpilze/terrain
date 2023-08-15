
#include "Hasher.hh"

namespace pge::lattice {

Hasher::Hasher(const noise::Seed seed) noexcept
  : m_seed(seed)
{}

auto Hasher::hash(const int x, const int y) -> float
{
  // // https://gamedev.stackexchange.com/questions/183142/how-can-i-create-a-persistent-seed-for-each-chunk-of-an-infinite-procedural-worl
  const auto px = (x < 0 ? -2 * x + 1 : 2 * x);
  const auto py = (y < 0 ? -2 * y + 1 : 2 * y);

  auto hash = px;
  hash ^= py << 16;
  hash ^= py >> 16;

  return hash ^ m_seed;
}

} // namespace pge::lattice
