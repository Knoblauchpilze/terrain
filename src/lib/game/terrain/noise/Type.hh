
#pragma once

#include <string>

namespace pge::noise {

enum class Type
{
  White
};

auto str(const Type &type) noexcept -> std::string;

} // namespace pge::noise
