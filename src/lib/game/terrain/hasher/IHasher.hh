
#pragma once

#include "ILatticePoint.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class IHasher
{
  public:
  virtual ~IHasher() = default;

  virtual auto hash(const ILatticePoint<Dimension> &p) -> int = 0;
};

template<int Dimension>
using IHasherPtr = std::unique_ptr<IHasher<Dimension>>;

using IHasher2dPtr = IHasherPtr<2>;
using IHasher3dPtr = IHasherPtr<3>;

} // namespace pge::terrain
