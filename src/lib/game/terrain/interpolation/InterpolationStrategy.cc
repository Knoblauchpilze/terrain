
#include "InterpolationStrategy.hh"

namespace pge::terrain {

auto str(const InterpolationStrategy strategy) noexcept -> std::string
{
  switch (strategy)
  {
    case InterpolationStrategy::LINEAR:
      return "linear";
    case InterpolationStrategy::SMOOTHSTEP:
      return "smoothstep";
    default:
      return "unknown";
  }
}

auto nextInterpolationStrategy(const InterpolationStrategy strategy) noexcept
  -> InterpolationStrategy
{
  switch (strategy)
  {
    case InterpolationStrategy::LINEAR:
      return InterpolationStrategy::SMOOTHSTEP;
    case InterpolationStrategy::SMOOTHSTEP:
    default:
      return InterpolationStrategy::LINEAR;
  }
}

auto previousInterpolationStrategy(const InterpolationStrategy strategy) noexcept
  -> InterpolationStrategy
{
  switch (strategy)
  {
    case InterpolationStrategy::SMOOTHSTEP:
      return InterpolationStrategy::LINEAR;
    case InterpolationStrategy::LINEAR:
    default:
      return InterpolationStrategy::SMOOTHSTEP;
  }
}

} // namespace pge::terrain
