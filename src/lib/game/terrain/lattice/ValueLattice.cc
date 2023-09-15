
#include "ValueLattice.hh"
#include "ValueGenerator.hh"

namespace pge::terrain {

ValueLattice::ValueLattice(IHasher2dPtr hasher,
                           INoisePtr noise,
                           IInterpolator2dPtr interpolator,
                           const int cacheSize)
  : AbstractLattice2d(std::make_unique<ValueGenerator2d>(std::move(hasher),
                                                         std::move(noise),
                                                         cacheSize),
                      std::move(interpolator),
                      {})
{}

} // namespace pge::terrain
