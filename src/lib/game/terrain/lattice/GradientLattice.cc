
#include "GradientLattice.hh"
#include "GradientGenerator.hh"
#include "Hasher.hh"

namespace pge::lattice {

GradientLattice::GradientLattice(IHasherPtr hasher,
                                 noise::INoisePtr noise,
                                 interpolation::IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<GradientGenerator>(std::move(hasher), std::move(noise)),
                    std::move(interpolator))
{}

} // namespace pge::lattice
