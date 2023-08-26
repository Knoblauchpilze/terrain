
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::lattice {

class GradientLattice : public AbstractLattice<utils::Vector2f>
{
  public:
  GradientLattice(IHasherPtr hasher,
                  noise::INoisePtr noise,
                  interpolation::IInterpolatorPtr interpolator);
  ~GradientLattice() override = default;
};

} // namespace pge::lattice
