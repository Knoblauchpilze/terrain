
#pragma once

#include "AbstractGradientLattice.hh"
#include "Seed.hh"

namespace pge::terrain {

class PeriodicGradientLattice : public AbstractGradientLattice
{
  public:
  PeriodicGradientLattice(const int period, const Seed seed, IInterpolator2dPtr interpolator);
  ~PeriodicGradientLattice() override = default;
};

} // namespace pge::terrain
