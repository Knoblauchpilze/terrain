
#pragma once

#include "InterpolationData.hh"
#include <array>
#include <memory>

namespace pge::terrain {

template<int Dimension>
class IInterpolator
{
  public:
  virtual ~IInterpolator() = default;

  virtual auto interpolate(const InterpolationData<Dimension> &data) const -> float = 0;
};

using IInterpolator2d = IInterpolator<2>;
using IInterpolator3d = IInterpolator<3>;

using IInterpolator2dPtr = std::unique_ptr<IInterpolator2d>;
using IInterpolator3dPtr = std::unique_ptr<IInterpolator3d>;

} // namespace pge::terrain
