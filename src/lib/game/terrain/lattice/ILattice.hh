
#pragma once

#include <memory>

namespace pge::terrain {

class ILattice
{
  public:
  virtual ~ILattice() = default;

  virtual auto at(const float x, const float y) -> float = 0;
};

using ILatticePtr = std::unique_ptr<ILattice>;

} // namespace pge::terrain
