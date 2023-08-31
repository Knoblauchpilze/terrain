
#pragma once

#include "ILatticePoint.hh"
#include <vector>

namespace pge::terrain {

template<int Dimension>
struct Area
{
  std::vector<ILatticePoint<Dimension>> points;
};

using Area2d = Area<2>;
using Area3d = Area<3>;

} // namespace pge::terrain
