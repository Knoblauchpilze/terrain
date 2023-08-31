
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IPoint.hh"
#include "IValueGenerator.hh"
#include <functional>
#include <optional>

namespace pge::terrain {

template<int ValueDimension>
class AbstractLattice : public ILattice<2>
{
  public:
  ~AbstractLattice() override = default;

  auto at(const Point2d &point) -> float override;

  protected:
  using NormalizationFunc = std::function<float(const float)>;

  AbstractLattice(IValueGeneratorPtr<2, ValueDimension> valueGenerator,
                  IInterpolatorPtr interpolator,
                  std::optional<NormalizationFunc> normalization) noexcept;

  private:
  IArea2dGeneratorPtr m_areaGenerator;
  IValueGeneratorPtr<2, ValueDimension> m_valueGenerator;
  IInterpolatorPtr m_interpolator;
  std::optional<NormalizationFunc> m_normalization;
};

} // namespace pge::terrain

#include "AbstractLattice.hxx"
