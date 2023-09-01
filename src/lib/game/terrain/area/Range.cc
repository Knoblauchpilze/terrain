
#include "Range.hh"
#include <cmath>

namespace pge::lattice {

auto surroundWithIntegers(const float val) -> Range
{
  const auto min = static_cast<int>(std::floor(val));
  // https://stackoverflow.com/questions/61756878/how-to-find-the-next-greater-value-generically-in-c-for-integers-and-floats
  const auto max = static_cast<int>(
    std::ceil(std::nextafter(val, std::numeric_limits<float>::infinity())));

  return Range{min, max};
}

} // namespace pge::lattice
