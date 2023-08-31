
#pragma once

#include "AbstractLattice.hh"
#include "INoise.hh"

namespace pge::terrain {

class PeriodicGradientLattice : public AbstractLattice<2>
{
  public:
  PeriodicGradientLattice(const int period, const Seed seed, IInterpolatorPtr interpolator);
  ~PeriodicGradientLattice() override = default;
};

} // namespace pge::terrain
