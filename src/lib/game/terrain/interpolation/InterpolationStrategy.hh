
#pragma once

#include <string>

namespace pge::terrain {

enum class InterpolationStrategy
{
  LINEAR,
  SMOOTHSTEP
};

auto str(const InterpolationStrategy strategy) noexcept -> std::string;
auto nextInterpolationStrategy(const InterpolationStrategy strategy) noexcept
  -> InterpolationStrategy;
auto previousInterpolationStrategy(const InterpolationStrategy strategy) noexcept
  -> InterpolationStrategy;

} // namespace pge::terrain
