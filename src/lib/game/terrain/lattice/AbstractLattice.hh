
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IValueGenerator.hh"
#include <functional>
#include <optional>

namespace pge::lattice {

class AbstractLattice : public ILattice
{
  public:
  ~AbstractLattice() override = default;

  auto at(const float x, const float y) -> float override;

  protected:
  using NormalizationFunc = std::function<float(const float)>;

  AbstractLattice(IValueGeneratorPtr valueGenerator,
                  interpolation::IInterpolatorPtr interpolator,
                  std::optional<NormalizationFunc> normalization) noexcept;

  private:
  IAreaGeneratorPtr m_areaGenerator;
  IValueGeneratorPtr m_valueGenerator;
  interpolation::IInterpolatorPtr m_interpolator;
  std::optional<NormalizationFunc> m_normalization;
};

} // namespace pge::lattice
