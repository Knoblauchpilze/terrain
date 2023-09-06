
#include "ValueLattice.hh"
#include "ValueGenerator.hh"

namespace pge::terrain {

ValueLattice::ValueLattice(IHasher3dPtr hasher, INoisePtr noise, IInterpolator3dPtr interpolator)
  : AbstractLattice3d(std::make_unique<ValueGenerator>(std::move(hasher), std::move(noise)),
                      std::move(interpolator),
                      {})
{}

} // namespace pge::terrain
