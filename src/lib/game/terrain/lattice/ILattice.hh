
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

using ILattice2dPtr = std::unique_ptr<ILattice2d>;
using ILattice3dPtr = std::unique_ptr<ILattice3d>;

} // namespace pge::terrain
