
#include "PeriodicGradientLattice.hh"
#include "PeriodicGradientGenerator.hh"
#include <numbers>

namespace pge::terrain {

PeriodicGradientLattice::PeriodicGradientLattice(const int period,
                                                 const Seed seed,
                                                 IInterpolator2dPtr interpolator)
  : AbstractGradientLattice(std::make_unique<PeriodicGradientGenerator>(period, seed),
                            std::move(interpolator))
{}

} // namespace pge::terrain
