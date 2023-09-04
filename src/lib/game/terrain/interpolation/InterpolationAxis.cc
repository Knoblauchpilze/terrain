
#include "InterpolationAxis.hh"
#include <stdexcept>

namespace pge::terrain {

InterpolationAxis::InterpolationAxis(const float low, const float high, const float perc)
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

auto InterpolationAxis::evaluate() const noexcept -> float
{
  return (1.0f - m_perc) * m_low + m_perc * m_high;
}

} // namespace pge::terrain
