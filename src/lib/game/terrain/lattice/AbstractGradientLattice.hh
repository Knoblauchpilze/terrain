
#pragma once

#include "AbstractLattice.hh"
#include "IValueGenerator.hh"

namespace pge::terrain {

class AbstractGradientLattice : public AbstractLattice<Point3d>
{
  public:
  AbstractGradientLattice(IValueGeneratorPtr<Point3d> valueGenerator, IInterpolatorPtr interpolator);
  ~AbstractGradientLattice() override = default;
};

} // namespace pge::terrain
