
#pragma once

#include "AbstractLattice.hh"
#include "INoise.hh"

namespace pge::lattice {

class PeriodicGradientLattice : public AbstractLattice<utils::Vector2f>
{
  public:
  PeriodicGradientLattice(const int period,
                          const noise::Seed seed,
                          interpolation::IInterpolatorPtr interpolator);
  ~PeriodicGradientLattice() override = default;
};

} // namespace pge::lattice
