
#pragma once

#include "AbstractLattice.hh"
#include "INoise.hh"

namespace pge::terrain {

class PeriodicPerlinLattice : public AbstractLattice<2>
{
  public:
  PeriodicPerlinLattice(const int period, const Seed seed, IInterpolatorPtr interpolator);
  ~PeriodicPerlinLattice() override = default;
};

} // namespace pge::terrain
