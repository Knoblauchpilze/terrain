
#pragma once

#include "AbstractLattice3d.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class ValueLattice : public AbstractLattice3d<float>
{
  public:
  ValueLattice(IHasher3dPtr hasher, INoisePtr noise, IInterpolator3dPtr interpolator);
  ~ValueLattice() override = default;
};

} // namespace pge::terrain
