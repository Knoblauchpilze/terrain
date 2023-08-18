
#pragma once

#include "ILatticeGenerator.hh"

namespace pge::lattice {

class LatticeGenerator : public ILatticeGenerator
{
  public:
  ~LatticeGenerator() override = default;

  auto areaSurrounding(const float x, const float y) const noexcept -> LatticeArea override;
};

} // namespace pge::lattice
