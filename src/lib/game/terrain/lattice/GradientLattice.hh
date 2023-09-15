
#pragma once

#include "AbstractGradientLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class GradientLattice : public AbstractGradientLattice
{
  public:
  GradientLattice(IHasher2dPtr hasher,
                  INoisePtr noise,
                  IInterpolator2dPtr interpolator,
                  const int cacheSize);
  ~GradientLattice() override = default;
};

} // namespace pge::terrain
