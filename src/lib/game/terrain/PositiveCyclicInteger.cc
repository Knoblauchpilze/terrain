
#include "PositiveCyclicInteger.hh"
#include <stdexcept>

namespace pge::terrain {

PositiveCyclicInteger::PositiveCyclicInteger(const int min,
                                             const int value,
                                             const int max,
                                             const int step)
  : m_min(min)
  , m_max(max)
  , m_value(value)
  , m_step(step)
{
  if (m_min < 0)
  {
    throw std::invalid_argument("Expected positive min, got " + std::to_string(m_min));
  }
  if (m_max < 0)
  {
    throw std::invalid_argument("Expected positive max, got " + std::to_string(m_max));
  }
  if (m_step <= 1)
  {
    throw std::invalid_argument("Expected strictly positive step, got " + std::to_string(m_step));
  }
  if (m_value < m_min || m_value > m_max)
  {
    throw std::invalid_argument("Expected value to be within range [" + std::to_string(m_min) + " - "
                                + std::to_string(m_max) + "], got " + std::to_string(m_value));
  }
}

auto PositiveCyclicInteger::current() const noexcept -> int
{
  return m_value;
}

void PositiveCyclicInteger::next() noexcept
{
  m_value *= m_step;
  if (m_value > m_max)
  {
    m_value = m_min;
  }
}

void PositiveCyclicInteger::previous() noexcept
{
  m_value /= m_step;
  if (m_value < m_min)
  {
    m_value = m_max;
  }
}

} // namespace pge::terrain
