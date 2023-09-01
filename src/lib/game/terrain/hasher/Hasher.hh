
#pragma once

#include "IHasher.hh"
#include "Seed.hh"

namespace pge::terrain {

template<int Dimension>
class Hasher : public IHasher<Dimension>
{
  public:
  Hasher(const Seed seed) noexcept;
  ~Hasher() override = default;

  using Point = ILatticePoint<Dimension>;

  auto hash(const Point &p) -> int override;

  private:
  Seed m_seed;

  auto abs(const int v) const noexcept -> int;
  auto hash2d(const int v1, const int v2) -> int;
};

using Hasher2d = Hasher<2>;
using Hasher3d = Hasher<3>;

} // namespace pge::terrain

#include "Hasher.hxx"
