
#pragma once

#include "AbstractLattice.hh"

namespace pge::terrain {

template<int Dimension, typename ValueType>
inline AbstractLattice<Dimension, ValueType>::AbstractLattice(
  IAreaGeneratorPtr<Dimension> areaGenerator,
  IValueGeneratorPtr<Dimension, ValueType> valueGenerator,
  IInterpolatorPtr<Dimension> interpolator,
  std::optional<NormalizationFunc> normalization) noexcept
  : m_areaGenerator(std::move(areaGenerator))
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
  , m_normalization(std::move(normalization))
{}

} // namespace pge::terrain
