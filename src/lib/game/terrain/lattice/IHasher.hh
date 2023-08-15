
#pragma once

#include <memory>

namespace pge::lattice {

class IHasher
{
  public:
  virtual ~IHasher() = default;

  virtual auto hash(const int x, const int y) -> float = 0;
};

using IHasherPtr = std::unique_ptr<IHasher>;

} // namespace pge::lattice
