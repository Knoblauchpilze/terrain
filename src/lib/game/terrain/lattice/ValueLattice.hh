
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class ValueLattice : public AbstractLattice<1>
{
  public:
  ValueLattice(IHasher2dPtr hasher, INoisePtr noise, IInterpolatorPtr interpolator);
  ~ValueLattice() override = default;
};

} // namespace pge::terrain
