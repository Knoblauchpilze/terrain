
#pragma once

#include <utility>

namespace pge::lattice {

using Range = std::pair<int, int>;

auto surroundWithIntegers(const float val) -> Range;

} // namespace pge::lattice
