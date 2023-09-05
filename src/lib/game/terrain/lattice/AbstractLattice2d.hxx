
#pragma once

#include "AbstractLattice2d.hh"
#include "Area2dGenerator.hh"
#include "Bilinear2d.hh"
#include <cmath>

namespace pge::terrain {

template<typename ValueType>
AbstractLattice2d<ValueType>::AbstractLattice2d(
  IValueGenerator2dPtr<ValueType> valueGenerator,
  IInterpolator2dPtr interpolator,
  std::optional<NormalizationFunc> normalization) noexcept
  : m_areaGenerator(std::make_unique<Area2dGenerator>())
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
  , m_normalization(std::move(normalization))
{}

template<typename ValueType>
auto AbstractLattice2d<ValueType>::at(const Point2d &p) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto area = m_areaGenerator->areaSurrounding(p);

  const auto &topLeft     = area.points[Area2dGenerator::TOP_LEFT];
  const auto &topRight    = area.points[Area2dGenerator::TOP_RIGHT];
  const auto &bottomRight = area.points[Area2dGenerator::BOTTOM_RIGHT];
  const auto &bottomLeft  = area.points[Area2dGenerator::BOTTOM_LEFT];

  const auto tl = m_valueGenerator->generateFor(topLeft, p);
  const auto tr = m_valueGenerator->generateFor(topRight, p);
  const auto br = m_valueGenerator->generateFor(bottomRight, p);
  const auto bl = m_valueGenerator->generateFor(bottomLeft, p);

  const auto xRange = topRight(0) - topLeft(0);
  const auto yRange = topLeft(1) - bottomLeft(1);
  const auto px     = (p(0) - bottomLeft(0)) / xRange;
  const auto py     = (p(1) - bottomLeft(1)) / yRange;

  InterpolationData2d data{};
  data.axes[Bilinear2d::BOTTOM] = InterpolationAxis(bl, br, px);
  data.axes[Bilinear2d::TOP]    = InterpolationAxis(tl, tr, px);
  data.deltas[Bilinear2d::Y]    = py;

  const auto val = m_interpolator->interpolate(data);
  if (!m_normalization)
  {
    return val;
  }

  return (*m_normalization)(val);
}

} // namespace pge::terrain
