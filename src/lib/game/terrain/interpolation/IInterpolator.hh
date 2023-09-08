
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

template<int Dimension>
using IInterpolatorPtr = std::unique_ptr<IInterpolator<Dimension>>;

using IInterpolator2dPtr = IInterpolatorPtr<2>;
using IInterpolator3dPtr = IInterpolatorPtr<3>;

} // namespace pge::terrain
