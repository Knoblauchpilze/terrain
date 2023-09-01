
#pragma once

#include "AbstractLattice.hh"
#include "Seed.hh"

namespace pge::terrain {

class PeriodicPerlinLattice : public AbstractLattice<utils::Vector2f>
{
  public:
  PeriodicPerlinLattice(const int period, const Seed seed, IInterpolatorPtr interpolator);
  ~PeriodicPerlinLattice() override = default;
};

} // namespace pge::terrain
