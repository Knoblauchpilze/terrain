
#include "Hasher3d.hh"

namespace pge::terrain {

Hasher3d::Hasher3d(const Seed seed) noexcept
  : m_seed(seed)
{}

auto Hasher3d::hash(const LatticePoint3d &p) -> int
{
  return hash2d(hash2d(p(0), p(1)), p(2));
}

auto Hasher3d::hash2d(const int p1, const int p2) const -> int
{
  const auto px = (p1 < 0 ? -2 * p1 + 1 : 2 * p1);
  const auto py = (p2 < 0 ? -2 * p2 + 1 : 2 * p2);

  auto hash = px;
  hash ^= py << 16;
  hash ^= py >> 16;

  return hash ^ m_seed;
}

} // namespace pge::terrain
