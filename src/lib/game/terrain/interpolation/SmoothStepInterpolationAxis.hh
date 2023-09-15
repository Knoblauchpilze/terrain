
#pragma once

namespace pge::terrain {

class SmoothStepInterpolationAxis
{
  public:
  SmoothStepInterpolationAxis() = default;
  SmoothStepInterpolationAxis(const float low, const float high, const float perc);

  auto delta() const noexcept -> float;
  auto evaluate() const noexcept -> float;

  private:
  float m_low{0.0f};
  float m_high{1.0f};
  float m_perc{0.0f};
};

} // namespace pge::terrain
