
#include "ValueLattice.hh"
#include "ValueGenerator.hh"

namespace pge::lattice {

ValueLattice::ValueLattice(IHasherPtr hasher,
                           noise::INoisePtr noise,
                           interpolation::IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<ValueGenerator>(std::move(hasher), std::move(noise)),
                    std::move(interpolator),
                    {})
{}

} // namespace pge::lattice
