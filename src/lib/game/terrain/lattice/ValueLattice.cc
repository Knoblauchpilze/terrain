
#include "ValueLattice.hh"
#include "ValueGenerator.hh"

namespace pge::terrain {

ValueLattice::ValueLattice(IHasher2dPtr hasher, INoisePtr noise, IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<ValueGenerator>(std::move(hasher), std::move(noise)),
                    std::move(interpolator),
                    {})
{}

} // namespace pge::terrain
