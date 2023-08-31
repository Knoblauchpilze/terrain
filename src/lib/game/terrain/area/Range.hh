
#pragma once

#include <utility>

namespace pge::terrain {

using Range = std::pair<int, int>;

auto surroundWithIntegers(const float val) -> Range;

} // namespace pge::terrain
