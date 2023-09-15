
#pragma once

#include "AbstractLattice2d.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class ValueLattice : public AbstractLattice2d<float>
{
  public:
  ValueLattice(IHasher2dPtr hasher,
               INoisePtr noise,
               IInterpolator2dPtr interpolator,
               const int cacheSize);
  ~ValueLattice() override = default;
};

} // namespace pge::terrain
