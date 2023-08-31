
#pragma once

#include "ValueGenerator.hh"
#include "ValueLattice.hh"

namespace pge::terrain {

template<int Dimension>
inline ValueLattice<Dimension>::ValueLattice(IHasherPtr<Dimension> hasher,
                                             INoisePtr noise,
                                             IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<ValueGenerator<Dimension>>(std::move(hasher), std::move(noise)),
                    std::move(interpolator),
                    {})
{}

} // namespace pge::terrain
