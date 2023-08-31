
#pragma once

#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class ILattice
{
  public:
  virtual ~ILattice() = default;

  using LatticePoint = ILatticePoint<Dimension>;
  using Point        = IPoint<Dimension>;

  virtual auto at(const Point &point) -> float = 0;
};

template<int Dimension>
using ILatticePtr = std::unique_ptr<ILattice<Dimension>>;

using ILattice2dPtr = ILatticePtr<2>;

} // namespace pge::terrain
