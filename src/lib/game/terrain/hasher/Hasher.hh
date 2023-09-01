
#pragma once

#include "IHasher.hh"
#include "Seed.hh"

namespace pge::terrain {

class Hasher : public IHasher
{
  public:
  Hasher(const Seed seed) noexcept;
  ~Hasher() override = default;

  auto hash(const int x, const int y) -> float override;

  private:
  Seed m_seed;
};

} // namespace pge::terrain
