
#pragma once

#include <string>

namespace pge::noise {

enum class Type
{
  White,
  Value
};

auto str(const Type &type) noexcept -> std::string;

} // namespace pge::noise
