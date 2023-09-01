
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class GradientLattice : public AbstractLattice<utils::Vector2f>
{
  public:
  GradientLattice(IHasher2dPtr hasher, INoisePtr noise, IInterpolatorPtr interpolator);
  ~GradientLattice() override = default;
};

} // namespace pge::terrain
