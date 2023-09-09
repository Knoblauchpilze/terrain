
#include "PeriodicPerlinGenerator.hh"

namespace pge::terrain {
/// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
template<>
const std::vector<Point3d> PeriodicPerlinGenerator<2>::DEFAULT_GRADIENTS
  = {Point3d(1.0f, 1.0f, 0.0f),
     Point3d(-1.0f, 1.0f, 0.0f),
     Point3d(1.0f, -1.0f, 0.0f),
     Point3d(-1.0f, -1.0f, 0.0f),
     Point3d(1.0f, 0.0f, 1.0f),
     Point3d(-1.0f, 0.0f, 1.0f),
     Point3d(1.0f, 0.0f, -1.0f),
     Point3d(-1.0f, 0.0f, -1.0f),
     Point3d(0.0f, 1.0f, 1.0f),
     Point3d(0.0f, -1.0f, 1.0f),
     Point3d(0.0f, 1.0f, -1.0f),
     Point3d(0.0f, -1.0f, -1.0f),
     // Additional padding
     Point3d(1.0f, 1.0f, 0.0f),
     Point3d(-1.0f, 1.0f, 0.0f),
     Point3d(0.0f, -1.0f, 1.0f),
     Point3d(0.0f, -1.0f, -1.0f)};

} // namespace pge::terrain
