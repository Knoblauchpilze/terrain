
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::lattice {

class GradientLattice : public AbstractLattice
{
  public:
  GradientLattice(IHasherPtr hasher,
                  noise::INoisePtr noise,
                  interpolation::IInterpolatorPtr interpolator);
  ~GradientLattice() override = default;
};

} // namespace pge::lattice
