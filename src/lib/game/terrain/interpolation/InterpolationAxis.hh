
#pragma once

#include "InterpolationStrategy.hh"

namespace pge::terrain {

class InterpolationAxis
{
  public:
  InterpolationAxis() = default;
  InterpolationAxis(const float low, const float high, const float perc);
  InterpolationAxis(const float low,
                    const float high,
                    const float perc,
                    const InterpolationStrategy &strategy);

  auto delta() const noexcept -> float;
  auto evaluate() const noexcept -> float;

  private:
  float m_low{0.0f};
  float m_high{1.0f};
  float m_perc{0.0f};

  InterpolationStrategy m_strategy{InterpolationStrategy::LINEAR};
};

} // namespace pge::terrain
