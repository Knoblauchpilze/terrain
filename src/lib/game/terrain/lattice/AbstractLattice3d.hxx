
#pragma once

#include "AbstractLattice3d.hh"
#include "Area3dGenerator.hh"
#include "Bilinear3d.hh"
#include <cmath>

namespace pge::terrain {

template<typename ValueType>
AbstractLattice3d<ValueType>::AbstractLattice3d(
  IValueGenerator3dPtr<ValueType> valueGenerator,
  IInterpolator3dPtr interpolator,
  std::optional<NormalizationFunc> normalization) noexcept
  : m_areaGenerator(std::make_unique<Area3dGenerator>())
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
  , m_normalization(std::move(normalization))
{}

template<typename ValueType>
auto AbstractLattice3d<ValueType>::at(const Point3d &p) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto area = m_areaGenerator->areaSurrounding(p);

  const auto &frontTopLeft     = area.points[Area3dGenerator::FRONT_TOP_LEFT];
  const auto &frontTopRight    = area.points[Area3dGenerator::FRONT_TOP_RIGHT];
  const auto &frontBottomRight = area.points[Area3dGenerator::FRONT_BOTTOM_RIGHT];
  const auto &frontBottomLeft  = area.points[Area3dGenerator::FRONT_BOTTOM_LEFT];

  const auto &backTopLeft     = area.points[Area3dGenerator::BACK_TOP_LEFT];
  const auto &backTopRight    = area.points[Area3dGenerator::BACK_TOP_RIGHT];
  const auto &backBottomRight = area.points[Area3dGenerator::BACK_BOTTOM_RIGHT];
  const auto &backBottomLeft  = area.points[Area3dGenerator::BACK_BOTTOM_LEFT];

  const auto ftl = m_valueGenerator->generateFor(frontTopLeft, p);
  const auto ftr = m_valueGenerator->generateFor(frontTopRight, p);
  const auto fbr = m_valueGenerator->generateFor(frontBottomRight, p);
  const auto fbl = m_valueGenerator->generateFor(frontBottomLeft, p);

  const auto btl = m_valueGenerator->generateFor(backTopLeft, p);
  const auto btr = m_valueGenerator->generateFor(backTopRight, p);
  const auto bbr = m_valueGenerator->generateFor(backBottomRight, p);
  const auto bbl = m_valueGenerator->generateFor(backBottomLeft, p);

  const auto xRange = frontBottomRight(0) - frontBottomLeft(0);
  const auto yRange = backBottomLeft(1) - frontBottomLeft(1);
  const auto zRange = frontTopLeft(1) - frontBottomLeft(1);
  const auto px     = (p(0) - frontBottomLeft(0)) / xRange;
  const auto py     = (p(1) - frontBottomLeft(1)) / yRange;
  const auto pz     = (p(2) - frontBottomLeft(2)) / zRange;

  InterpolationData3d data{};
  data.axes[Bilinear3d::FRONT_BOTTOM] = InterpolationAxis(fbl, fbr, px);
  data.axes[Bilinear3d::FRONT_TOP]    = InterpolationAxis(ftl, ftr, px);
  data.axes[Bilinear3d::BACK_TOP]     = InterpolationAxis(btl, btr, px);
  data.axes[Bilinear3d::BACK_BOTTOM]  = InterpolationAxis(bbl, bbr, px);
  data.deltas[Bilinear3d::Z]          = pz;
  data.deltas[Bilinear3d::Y]          = py;

  const auto val = m_interpolator->interpolate(data);
  if (!m_normalization)
  {
    return val;
  }

  return (*m_normalization)(val);
}

} // namespace pge::terrain
