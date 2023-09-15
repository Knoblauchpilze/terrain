
#include "AbstractInterpolator.hh"

namespace pge::terrain {

template<int Dimension>
inline AbstractInterpolator<Dimension>::AbstractInterpolator(const InterpolationStrategy &strategy)
  : m_strategy(strategy)
{}

template<int Dimension>
auto inline AbstractInterpolator<Dimension>::strategy() const noexcept -> InterpolationStrategy
{
  return m_strategy;
}

} // namespace pge::terrain
