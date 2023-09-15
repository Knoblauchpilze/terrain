
#include "SmoothStepInterpolationAxis.hh"
#include <stdexcept>

namespace pge::terrain {

SmoothStepInterpolationAxis::SmoothStepInterpolationAxis(const float low,
                                                         const float high,
                                                         const float perc)
  : m_low(low)
  , m_high(high)
  , m_perc(perc)
{
  if (m_perc < 0.0f || m_perc > 1.0f)
  {
    throw std::invalid_argument("Expected percentage to be within [0; 1], got "
                                + std::to_string(m_perc));
  }
}

auto SmoothStepInterpolationAxis::delta() const noexcept -> float
{
  return m_perc;
}

auto SmoothStepInterpolationAxis::evaluate() const noexcept -> float
{
  /// https://en.wikipedia.org/wiki/Perlin_noise#Implementation
  return m_low
         + (m_high - m_low)
             * ((m_perc * (m_perc * 6.0f - 15.0f) + 10.0f) * m_perc * m_perc * m_perc);
}

} // namespace pge::terrain
