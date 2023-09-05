
#pragma once

#include "AbstractLattice2d.hh"
#include "IValueGenerator.hh"

namespace pge::terrain {

class AbstractGradientLattice : public AbstractLattice2d<Point3d>
{
  public:
  AbstractGradientLattice(IValueGenerator2dPtr<Point3d> valueGenerator,
                          IInterpolator2dPtr interpolator);
  ~AbstractGradientLattice() override = default;
};

} // namespace pge::terrain
