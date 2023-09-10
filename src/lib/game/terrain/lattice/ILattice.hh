
#pragma once

#include "IPoint.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class ILattice
{
  public:
  virtual ~ILattice() = default;

  virtual auto at(const IPoint<Dimension> &p) -> float = 0;

  static constexpr auto DIMENSION = Dimension;
};

using ILattice2d = ILattice<2>;
using ILattice3d = ILattice<3>;

template<int Dimension>
using ILatticePtr = std::unique_ptr<ILattice<Dimension>>;

using ILattice2dPtr = ILatticePtr<2>;
using ILattice3dPtr = ILatticePtr<3>;

} // namespace pge::terrain
