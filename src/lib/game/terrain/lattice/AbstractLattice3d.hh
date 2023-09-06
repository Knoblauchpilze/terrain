
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IValueGenerator.hh"
#include <functional>
#include <optional>

namespace pge::terrain {

template<typename ValueType>
class AbstractLattice3d : public ILattice<3>
{
  public:
  ~AbstractLattice3d() override = default;

  auto at(const Point3d &p) -> float override;

  protected:
  using NormalizationFunc = std::function<float(const float)>;

  AbstractLattice3d(IValueGenerator3dPtr<ValueType> valueGenerator,
                    IInterpolator3dPtr interpolator,
                    std::optional<NormalizationFunc> normalization) noexcept;

  private:
  IArea3dGeneratorPtr m_areaGenerator;
  IValueGenerator3dPtr<ValueType> m_valueGenerator;
  IInterpolator3dPtr m_interpolator;
  std::optional<NormalizationFunc> m_normalization;
};

} // namespace pge::terrain

#include "AbstractLattice3d.hxx"
