
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IValueGenerator.hh"
#include <functional>
#include <optional>

namespace pge::terrain {

template<typename ValueType>
class AbstractLattice : public ILattice2d
{
  public:
  ~AbstractLattice() override = default;

  auto at(const Point2d &p) -> float override;

  protected:
  using NormalizationFunc = std::function<float(const float)>;

  AbstractLattice(IValueGeneratorPtr<2, ValueType> valueGenerator,
                  IInterpolator2dPtr interpolator,
                  std::optional<NormalizationFunc> normalization) noexcept;

  private:
  IArea2dGeneratorPtr m_areaGenerator;
  IValueGeneratorPtr<2, ValueType> m_valueGenerator;
  IInterpolator2dPtr m_interpolator;
  std::optional<NormalizationFunc> m_normalization;
};

} // namespace pge::terrain

#include "AbstractLattice.hxx"
