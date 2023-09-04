
#pragma once

#include "InterpolationAxis.hh"
#include <array>
#include <memory>

namespace pge::terrain {

template<int Dimension>
struct InterpolationData
{
  std::array<InterpolationAxis, Dimension> axes{};
  std::array<float, Dimension - 1> deltas{};
};

template<int Dimension>
class IInterpolator
{
  public:
  virtual ~IInterpolator() = default;

  virtual auto interpolate(const InterpolationData<Dimension> &data) const -> float = 0;
};

template<int Dimension>
using IInterpolatorPtr = std::unique_ptr<IInterpolator<Dimension>>;

using IInterpolator2dPtr = IInterpolatorPtr<2>;

} // namespace pge::terrain
