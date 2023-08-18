
#include "LatticeGenerator.hh"

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

auto LatticeGenerator::areaSurrounding(const float x, const float y) const noexcept -> LatticeArea
{
  const auto xRange = surroundWithIntegers(x);
  const auto yRange = surroundWithIntegers(y);

  LatticeArea area;
  area.topLeft     = utils::Vector2f(xRange.first, yRange.second);
  area.topRight    = utils::Vector2f(xRange.second, yRange.second);
  area.bottomRight = utils::Vector2f(xRange.second, yRange.first);
  area.bottomLeft  = utils::Vector2f(xRange.first, yRange.first);

  return area;
}

} // namespace pge::lattice
