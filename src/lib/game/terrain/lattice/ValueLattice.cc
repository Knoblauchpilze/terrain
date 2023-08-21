
#include "ValueLattice.hh"
#include "Hasher.hh"
#include "ValueGenerator.hh"

namespace pge::lattice {

ValueLattice::ValueLattice(noise::INoisePtr noise, interpolation::IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<ValueGenerator>(std::move(noise)), std::move(interpolator), {})
{}

} // namespace pge::lattice
