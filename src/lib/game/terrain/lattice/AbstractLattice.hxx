
#pragma once

#include "AbstractLattice.hh"
#include "Area2dGenerator.hh"
#include <cmath>

namespace pge::terrain {

template<int ValueDimension>
inline AbstractLattice<ValueDimension>::AbstractLattice(
  IValueGeneratorPtr<2, ValueDimension> valueGenerator,
  IInterpolatorPtr interpolator,
  std::optional<NormalizationFunc> normalization) noexcept
  : m_areaGenerator(std::make_unique<Area2dGenerator>())
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
  , m_normalization(std::move(normalization))
{}

template<int ValueDimension>
inline auto AbstractLattice<ValueDimension>::at(const Point2d &point) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  /// TODO: Should be dynamic.
  const auto area = m_areaGenerator->areaSurrounding(point);

  const auto topLeft    = area.points[Area2dGenerator::TOP_LEFT];
  const auto topRight   = area.points[Area2dGenerator::TOP_RIGHT];
  const auto bottomLeft = area.points[Area2dGenerator::BOTTOM_LEFT];

  const auto tl = m_valueGenerator->generateFor(topLeft, point);
  const auto tr = m_valueGenerator->generateFor(topRight, point);
  const auto br = m_valueGenerator->generateFor(area.points[Area2dGenerator::BOTTOM_RIGHT], point);
  const auto bl = m_valueGenerator->generateFor(bottomLeft, point);

  const auto xRange = topRight(0) - topLeft(0);
  const auto yRange = topLeft(1) - bottomLeft(1);
  const auto px     = (point(0) - bottomLeft(0)) / xRange;
  const auto py     = (point(1) - bottomLeft(1)) / yRange;

  const auto val = m_interpolator->interpolate(tl, tr, br, bl, px, py);
  if (!m_normalization)
  {
    return val;
  }

  return (*m_normalization)(val);
}

} // namespace pge::terrain
