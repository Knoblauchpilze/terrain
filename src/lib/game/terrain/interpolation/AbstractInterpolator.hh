
#pragma once

#include "IInterpolator.hh"
#include "InterpolationStrategy.hh"

namespace pge::terrain {

template<int Dimension>
class AbstractInterpolator : IInterpolator<Dimension>
{
  public:
  AbstractInterpolator(const InterpolationStrategy &strategy);
  ~AbstractInterpolator() override = default;

  auto strategy() const noexcept -> InterpolationStrategy;

  private:
  InterpolationStrategy m_strategy{InterpolationStrategy::LINEAR};
};

} // namespace pge::terrain

#include "AbstractInterpolator.hxx"
