
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IValueGenerator.hh"
#include <functional>
#include <optional>

namespace pge::terrain {

using NormalizationFunc = std::function<float(const float)>;

template<int Dimension, typename ValueType>
class AbstractLattice : public ILattice<Dimension>
{
  public:
  ~AbstractLattice() override = default;

  AbstractLattice(IAreaGeneratorPtr<Dimension> areaGenerator,
                  IValueGeneratorPtr<Dimension, ValueType> valueGenerator,
                  IInterpolatorPtr<Dimension> interpolator,
                  std::optional<NormalizationFunc> normalization) noexcept;

  protected:
  IAreaGeneratorPtr<Dimension> m_areaGenerator;
  IValueGeneratorPtr<Dimension, ValueType> m_valueGenerator;
  IInterpolatorPtr<Dimension> m_interpolator;
  std::optional<NormalizationFunc> m_normalization;
};

} // namespace pge::terrain

#include "AbstractLattice.hxx"
