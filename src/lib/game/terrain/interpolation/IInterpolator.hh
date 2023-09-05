
#pragma once

#include "InterpolationData.hh"
#include <array>
#include <memory>

namespace pge::terrain {

template<int AxisCount, int DeltaCount>
class IInterpolator
{
  public:
  virtual ~IInterpolator() = default;

  virtual auto interpolate(const InterpolationData<AxisCount, DeltaCount> &data) const -> float = 0;
};

using IInterpolator2d = IInterpolator<2, 1>;
using IInterpolator3d = IInterpolator<4, 2>;

using IInterpolator2dPtr = std::unique_ptr<IInterpolator2d>;
using IInterpolator3dPtr = std::unique_ptr<IInterpolator3d>;

} // namespace pge::terrain
