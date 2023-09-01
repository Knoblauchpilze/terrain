
#include "AreaGenerator.hh"
#include "Range.hh"

namespace pge::terrain {

auto AreaGenerator::areaSurrounding(const float x, const float y) const noexcept -> Area
{
  const auto xRange = surroundWithIntegers(x);
  const auto yRange = surroundWithIntegers(y);

  Area area;
  area.topLeft     = utils::Vector2i(xRange.first, yRange.second);
  area.topRight    = utils::Vector2i(xRange.second, yRange.second);
  area.bottomRight = utils::Vector2i(xRange.second, yRange.first);
  area.bottomLeft  = utils::Vector2i(xRange.first, yRange.first);

  return area;
}

} // namespace pge::terrain
