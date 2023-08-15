
#pragma once

#include <memory>

namespace pge::interpolation {

class IInterpolator
{
  public:
  virtual ~IInterpolator() = default;

  virtual auto interpolate(const float tl,
                           const float tr,
                           const float br,
                           const float bl,
                           const float px,
                           const float py) const -> float
    = 0;
};

using IInterpolatorPtr = std::unique_ptr<IInterpolator>;

} // namespace pge::interpolation
