
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class ValueLattice : public AbstractLattice<float>
{
  public:
  ValueLattice(IHasher2dPtr hasher, INoisePtr noise, IInterpolator2dPtr interpolator);
  ~ValueLattice() override = default;
};

} // namespace pge::terrain
