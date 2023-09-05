
#pragma once

#include "InterpolationAxis.hh"
#include <array>

namespace pge::terrain {

template<int AxisCount, int DeltaCount>
struct InterpolationData
{
  std::array<InterpolationAxis, AxisCount> axes{};
  std::array<float, DeltaCount> deltas{};
};

using InterpolationData2d = InterpolationData<2, 1>;
using InterpolationData3d = InterpolationData<4, 2>;

} // namespace pge::terrain
