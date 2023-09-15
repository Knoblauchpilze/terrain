
#include "GradientLattice.hh"
#include "GradientGenerator.hh"
#include <numbers>

namespace pge::terrain {

GradientLattice::GradientLattice(IHasher2dPtr hasher,
                                 INoisePtr noise,
                                 IInterpolator2dPtr interpolator,
                                 const int cacheSize)
  : AbstractGradientLattice(std::make_unique<GradientGenerator2d>(std::move(hasher),
                                                                  std::move(noise),
                                                                  cacheSize),
                            std::move(interpolator))
{}

} // namespace pge::terrain
