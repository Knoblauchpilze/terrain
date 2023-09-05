
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IValueGenerator.hh"
#include <functional>
#include <optional>

namespace pge::terrain {

template<typename ValueType>
class AbstractLattice2d : public ILattice2d
{
  public:
  ~AbstractLattice2d() override = default;

  auto at(const Point2d &p) -> float override;

  protected:
  using NormalizationFunc = std::function<float(const float)>;

  AbstractLattice2d(IValueGenerator2dPtr<ValueType> valueGenerator,
                    IInterpolator2dPtr interpolator,
                    std::optional<NormalizationFunc> normalization) noexcept;

  private:
  IArea2dGeneratorPtr m_areaGenerator;
  IValueGenerator2dPtr<ValueType> m_valueGenerator;
  IInterpolator2dPtr m_interpolator;
  std::optional<NormalizationFunc> m_normalization;
};

} // namespace pge::terrain

#include "AbstractLattice2d.hxx"
