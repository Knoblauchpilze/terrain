
#pragma once

#include "AbstractLattice.hh"

namespace pge::terrain {

template<typename ValueType>
class AbstractLattice2d : public AbstractLattice<2, ValueType>
{
  public:
  ~AbstractLattice2d() override = default;

  auto at(const Point2d &p) -> float override;

  protected:
  AbstractLattice2d(IValueGenerator2dPtr<ValueType> valueGenerator,
                    IInterpolator2dPtr interpolator,
                    std::optional<NormalizationFunc> normalization) noexcept;
};

} // namespace pge::terrain

#include "AbstractLattice2d.hxx"
