
#pragma once

#include "IInterpolator.hh"

namespace pge::terrain {

template<int Dimension>
class AbstractInterpolator : public IInterpolator<Dimension>
{
  public:
  AbstractInterpolator() = default;
  AbstractInterpolator(const InterpolationStrategy &strategy);
  ~AbstractInterpolator() override = default;

  auto strategy() const noexcept -> InterpolationStrategy override;

  private:
  InterpolationStrategy m_strategy{InterpolationStrategy::LINEAR};
};

} // namespace pge::terrain

#include "AbstractInterpolator.hxx"
