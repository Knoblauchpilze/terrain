
#pragma once

#include "IHasher.hh"
#include "Seed.hh"

namespace pge::terrain {

class Hasher2d : public IHasher<2>
{
  public:
  Hasher2d(const Seed seed) noexcept;
  ~Hasher2d() override = default;

  auto hash(const LatticePoint2d &p) -> int override;

  private:
  Seed m_seed;
};

} // namespace pge::terrain
