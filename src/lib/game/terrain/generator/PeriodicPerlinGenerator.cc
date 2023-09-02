
#include "PeriodicPerlinGenerator.hh"

namespace pge::terrain {

PeriodicPerlinGenerator::PeriodicPerlinGenerator(const int period, const Seed seed)
  : AbstractPeriodicGradientGenerator(period, seed)
{}

namespace {
/// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
const std::vector<Point3d> DEFAULT_GRADIENTS = {Point3d(1.0f, 1.0f, 0.0f),
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
} // namespace

auto PeriodicPerlinGenerator::gradientAt(const int id) const noexcept -> Point3d
{
  return DEFAULT_GRADIENTS[id % DEFAULT_GRADIENTS.size()];
}

} // namespace pge::terrain
