
#pragma once

#include <eigen3/Eigen/Eigen>

namespace pge::terrain {

template<int Dimension>
using ILatticePoint = Eigen::Matrix<int, Dimension, 1>;

using LatticePoint2d = ILatticePoint<2>;
using LatticePoint3d = ILatticePoint<3>;

} // namespace pge::terrain
