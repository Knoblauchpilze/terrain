
#pragma once

#include <eigen3/Eigen/Eigen>

namespace pge::terrain {

template<int Dimension>
using IPoint = Eigen::Matrix<float, Dimension, 1>;

using Point1d = IPoint<1>;
using Point2d = IPoint<2>;
using Point3d = IPoint<3>;

} // namespace pge::terrain
