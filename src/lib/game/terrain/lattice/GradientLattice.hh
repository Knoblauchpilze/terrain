
#pragma once

#include "AbstractLattice.hh"
#include "INoise.hh"

namespace pge::lattice {

class GradientLattice : public AbstractLattice
{
  public:
  GradientLattice(noise::INoisePtr noise, interpolation::IInterpolatorPtr interpolator);
  ~GradientLattice() override = default;
};

} // namespace pge::lattice
