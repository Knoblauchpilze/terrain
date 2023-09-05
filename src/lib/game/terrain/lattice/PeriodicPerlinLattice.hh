
#pragma once

#include "AbstractLattice2d.hh"
#include "Seed.hh"

namespace pge::terrain {

class PeriodicPerlinLattice : public AbstractLattice2d<Point3d>
{
  public:
  PeriodicPerlinLattice(const int period, const Seed seed, IInterpolator2dPtr interpolator);
  ~PeriodicPerlinLattice() override = default;
};

} // namespace pge::terrain
