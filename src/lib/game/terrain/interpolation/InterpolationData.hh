
#pragma once

#include "ConstexprPowImpl.hh"
#include "InterpolationAxis.hh"
#include <array>

namespace pge::terrain {

template<int Dimension>
struct InterpolationData
{
  // https://stackoverflow.com/questions/58585604/getting-constexpr-to-work-with-pow-in-c17-on-osx
  std::array<InterpolationAxis, details::pow(2, Dimension - 1)> axes{};
  std::array<float, Dimension - 1> deltas{};
};

using InterpolationData2d = InterpolationData<2>;
using InterpolationData3d = InterpolationData<3>;

} // namespace pge::terrain
