
#pragma once

#include "AbstractLattice.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

template<int Dimension>
class ValueLattice : public AbstractLattice<1>
{
  public:
  ValueLattice(IHasherPtr<Dimension> hasher, INoisePtr noise, IInterpolatorPtr interpolator);
  ~ValueLattice() override = default;
};

using ValueLattice2d = ValueLattice<2>;
using ValueLattice3d = ValueLattice<3>;

} // namespace pge::terrain

#include "ValueLattice.hxx"
