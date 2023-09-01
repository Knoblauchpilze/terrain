
#pragma once

#include "AbstractLattice.hh"
#include "Seed.hh"
#include <maths_utils/Vector2.hh>

namespace pge::terrain {

class PeriodicGradientLattice : public AbstractLattice<utils::Vector2f>
{
  public:
  PeriodicGradientLattice(const int period, const Seed seed, IInterpolatorPtr interpolator);
  ~PeriodicGradientLattice() override = default;
};

} // namespace pge::terrain
