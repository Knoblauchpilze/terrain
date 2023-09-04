
#include "GradientLattice.hh"
#include "GradientGenerator.hh"
#include <numbers>

namespace pge::terrain {

GradientLattice::GradientLattice(IHasher2dPtr hasher,
                                 INoisePtr noise,
                                 IInterpolator2dPtr interpolator)
  : AbstractGradientLattice(std::make_unique<GradientGenerator>(std::move(hasher), std::move(noise)),
                            std::move(interpolator))
{}

} // namespace pge::terrain
