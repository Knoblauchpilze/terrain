
#pragma once

#include "AbstractLattice.hh"
#include "INoise.hh"

namespace pge::lattice {

class PeriodicPerlinLattice : public AbstractLattice<utils::Vector2f>
{
  public:
  PeriodicPerlinLattice(const int period,
                        const noise::Seed seed,
                        interpolation::IInterpolatorPtr interpolator);
  ~PeriodicPerlinLattice() override = default;
};

} // namespace pge::lattice
