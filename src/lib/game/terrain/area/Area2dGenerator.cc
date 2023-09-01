
#include "Area2dGenerator.hh"
#include "Range.hh"

namespace pge::terrain {

auto Area2dGenerator::areaSurrounding(const Point2d &p) const noexcept -> Area2d
{
  const auto xRange = surroundWithIntegers(p(0));
  const auto yRange = surroundWithIntegers(p(1));

  Area2d area;
  area.points.resize(COUNT);

  area.points[TOP_LEFT]     = LatticePoint2d(xRange.first, yRange.second);
  area.points[TOP_RIGHT]    = LatticePoint2d(xRange.second, yRange.second);
  area.points[BOTTOM_RIGHT] = LatticePoint2d(xRange.second, yRange.first);
  area.points[BOTTOM_LEFT]  = LatticePoint2d(xRange.first, yRange.first);

  return area;
}

} // namespace pge::terrain
