
#include "Area3dGenerator.hh"
#include "Range.hh"

namespace pge::terrain {

auto Area3dGenerator::areaSurrounding(const Point3d &p) const noexcept -> Area3d
{
  const auto xRange = surroundWithIntegers(p(0));
  const auto yRange = surroundWithIntegers(p(1));
  const auto zRange = surroundWithIntegers(p(2));

  Area3d area;
  area.points.resize(COUNT);

  area.points[FRONT_TOP_LEFT]     = LatticePoint3d(xRange.first, yRange.first, zRange.second);
  area.points[FRONT_TOP_RIGHT]    = LatticePoint3d(xRange.second, yRange.first, zRange.second);
  area.points[FRONT_BOTTOM_RIGHT] = LatticePoint3d(xRange.second, yRange.first, zRange.first);
  area.points[FRONT_BOTTOM_LEFT]  = LatticePoint3d(xRange.first, yRange.first, zRange.first);

  area.points[BACK_TOP_LEFT]     = LatticePoint3d(xRange.first, yRange.second, zRange.second);
  area.points[BACK_TOP_RIGHT]    = LatticePoint3d(xRange.second, yRange.second, zRange.second);
  area.points[BACK_BOTTOM_RIGHT] = LatticePoint3d(xRange.second, yRange.second, zRange.first);
  area.points[BACK_BOTTOM_LEFT]  = LatticePoint3d(xRange.first, yRange.second, zRange.first);

  return area;
}

} // namespace pge::terrain
