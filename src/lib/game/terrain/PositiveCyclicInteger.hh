
#pragma once

namespace pge::terrain {

class PositiveCyclicInteger
{
  public:
  PositiveCyclicInteger(const int min, const int value, const int max, const int step);

  auto current() const noexcept -> int;
  void next() noexcept;

  private:
  int m_min;
  int m_max;
  int m_value;
  int m_step;
};

} // namespace pge::terrain
