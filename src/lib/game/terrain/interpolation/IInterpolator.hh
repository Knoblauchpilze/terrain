
#pragma once

#include <memory>

namespace pge::terrain {

class IInterpolator
{
  public:
  virtual ~IInterpolator() = default;

  /// @brief - Interpolate the value given the lattice points in argument using a
  /// bilinear interpolation algorithm.
  /// @param tl - the top left corner of the lattice.
  /// @param tr - the top right corner of the lattice.
  /// @param br - the bottom right corner of the lattice.
  /// @param bl - the bottom left corner of the lattice.
  /// @param px - the position of the point to interpolate along the top axis. This
  /// value must lie in the range [0; 1].
  /// @param py - the position of the point to interpolate along the bottom axis. This
  /// value must lie in the range [0; 1].
  /// @return - the interpolated value based on the input parameters.
  virtual auto interpolate(const float tl,
                           const float tr,
                           const float br,
                           const float bl,
                           const float px,
                           const float py) const -> float
    = 0;
};

using IInterpolatorPtr = std::unique_ptr<IInterpolator>;

} // namespace pge::terrain
