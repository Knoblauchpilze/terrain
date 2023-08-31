
#include "Hasher2d.hh"

namespace pge::terrain {

Hasher2d::Hasher2d(const Seed seed) noexcept
  : m_seed(seed)
{}

auto Hasher2d::hash(const LatticePoint2d &p) -> int
{
  // https://gamedev.stackexchange.com/questions/183142/how-can-i-create-a-persistent-seed-for-each-chunk-of-an-infinite-procedural-worl
  const auto px = (p(0) < 0 ? -2 * p(0) + 1 : 2 * p(0));
  const auto py = (p(1) < 0 ? -2 * p(1) + 1 : 2 * p(1));

  auto hash = px;
  hash ^= py << 16;
  hash ^= py >> 16;

  return hash ^ m_seed;
}

} // namespace pge::terrain
