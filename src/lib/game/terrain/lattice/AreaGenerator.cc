
#include "AreaGenerator.hh"

namespace pge::lattice {
namespace {
using Range = std::pair<int, int>;

auto surroundWithIntegers(const float val) -> Range
{
  const auto min = static_cast<int>(std::floor(val));
  // https://stackoverflow.com/questions/61756878/how-to-find-the-next-greater-value-generically-in-c-for-integers-and-floats
  const auto max = static_cast<int>(
    std::ceil(std::nextafter(val, std::numeric_limits<float>::infinity())));

  return Range{min, max};
}
} // namespace

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

} // namespace pge::lattice
