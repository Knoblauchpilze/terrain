
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"
#include <maths_utils/Vector2.hh>

namespace pge::terrain {

class GradientLattice : public AbstractLattice<Point2d>
{
  public:
  GradientLattice(IHasher2dPtr hasher, INoisePtr noise, IInterpolatorPtr interpolator);
  ~GradientLattice() override = default;
};

} // namespace pge::terrain
