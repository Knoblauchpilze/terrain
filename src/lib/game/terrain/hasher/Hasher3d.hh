
#pragma once

#include "IHasher.hh"
#include "Seed.hh"

namespace pge::terrain {

class Hasher3d : public IHasher<3>
{
  public:
  Hasher3d(const Seed seed) noexcept;
  ~Hasher3d() override = default;

  auto hash(const LatticePoint3d &p) -> int override;

  private:
  Seed m_seed;

  auto hash2d(const int p1, const int p2) const -> int;
};

} // namespace pge::terrain
