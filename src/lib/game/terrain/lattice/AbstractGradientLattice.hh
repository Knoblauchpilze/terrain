
#pragma once

#include "AbstractLattice.hh"
#include "IValueGenerator.hh"

namespace pge::terrain {

class AbstractGradientLattice : public AbstractLattice<Point3d>
{
  public:
  AbstractGradientLattice(IValueGeneratorPtr<Point3d> valueGenerator,
                          IInterpolator2dPtr interpolator);
  ~AbstractGradientLattice() override = default;
};

} // namespace pge::terrain
