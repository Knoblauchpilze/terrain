
#pragma once

namespace pge::terrain {

class InterpolationAxis
{
  public:
  InterpolationAxis(const float low, const float high, const float perc);

  auto evaluate() const noexcept -> float;

  private:
  float m_low;
  float m_high;
  float m_perc;
};

} // namespace pge::terrain
