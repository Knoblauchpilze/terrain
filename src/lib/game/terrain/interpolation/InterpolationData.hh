
#pragma once

#include "InterpolationAxis.hh"
#include <array>

namespace pge::terrain {

template<int Dimension>
struct InterpolationData
{
  std::array<InterpolationAxis, Dimension> axes{};
  std::array<float, Dimension - 1> deltas{};
};

using InterpolationData2d = InterpolationData<2>;
using InterpolationData3d = InterpolationData<3>;

} // namespace pge::terrain
