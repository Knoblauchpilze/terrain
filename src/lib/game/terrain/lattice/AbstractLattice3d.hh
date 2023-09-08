#pragma once

#include "AbstractLattice.hh"

namespace pge::terrain {

template<typename ValueType>
class AbstractLattice3d : public AbstractLattice<3, ValueType>
{
  public:
  ~AbstractLattice3d() override = default;

  auto at(const Point3d &p) -> float override;

  protected:
  AbstractLattice3d(IValueGenerator3dPtr<ValueType> valueGenerator,
                    IInterpolator3dPtr interpolator,
                    std::optional<NormalizationFunc> normalization) noexcept;
};

} // namespace pge::terrain

#include "AbstractLattice3d.hxx"
