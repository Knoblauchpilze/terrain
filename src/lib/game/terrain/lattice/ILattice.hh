
#pragma once

#include "IPoint.hh"
#include <memory>

namespace pge::terrain {

class ILattice
{
  public:
  virtual ~ILattice() = default;

  virtual auto at(const Point2d &p) -> float = 0;
};

using ILatticePtr = std::unique_ptr<ILattice>;

} // namespace pge::terrain
