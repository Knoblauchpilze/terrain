
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::lattice {

class ValueLattice : public AbstractLattice<float>
{
  public:
  ValueLattice(IHasherPtr hasher,
               noise::INoisePtr noise,
               interpolation::IInterpolatorPtr interpolator);
  ~ValueLattice() override = default;
};

} // namespace pge::lattice
