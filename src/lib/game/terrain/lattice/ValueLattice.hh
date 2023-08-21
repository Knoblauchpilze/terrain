
#pragma once

#include "AbstractLattice.hh"
#include "INoise.hh"

namespace pge::lattice {

class ValueLattice : public AbstractLattice
{
  public:
  ValueLattice(noise::INoisePtr noise, interpolation::IInterpolatorPtr interpolator);
  ~ValueLattice() override = default;
};

} // namespace pge::lattice
