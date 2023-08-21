
#pragma once

#include "IHasher.hh"
#include "INoise.hh"

namespace pge::noise {

class Hasher : public IHasher
{
  public:
  Hasher(const noise::Seed seed) noexcept;
  ~Hasher() override = default;

  auto hash(const int x, const int y) -> float override;

  private:
  noise::Seed m_seed;
};

} // namespace pge::noise
