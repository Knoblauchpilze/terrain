
#pragma once

#include <memory>

namespace pge::terrain {

class Noise2d
{
  public:
  virtual ~Noise2d() = default;

  virtual auto at(float x, float y) const noexcept -> float = 0;
};

using Noise2dPtr = std::unique_ptr<Noise2d>;

} // namespace pge::terrain
