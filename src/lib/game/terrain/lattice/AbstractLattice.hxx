
#pragma once

#include "AbstractLattice.hh"
#include "Area2dGenerator.hh"
#include <cmath>

namespace pge::terrain {

template<typename ValueType>
AbstractLattice<ValueType>::AbstractLattice(IValueGeneratorPtr<ValueType> valueGenerator,
                                            IInterpolatorPtr interpolator,
                                            std::optional<NormalizationFunc> normalization) noexcept
  : m_areaGenerator(std::make_unique<Area2dGenerator>())
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
  , m_normalization(std::move(normalization))
{}

template<typename ValueType>
auto AbstractLattice<ValueType>::at(const float x, const float y) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto area = m_areaGenerator->areaSurrounding(Point2d(x, y));

  const auto &topLeft     = area.points[Area2dGenerator::TOP_LEFT];
  const auto &topRight    = area.points[Area2dGenerator::TOP_RIGHT];
  const auto &bottomRight = area.points[Area2dGenerator::BOTTOM_RIGHT];
  const auto &bottomLeft  = area.points[Area2dGenerator::BOTTOM_LEFT];

  const auto tl = m_valueGenerator->generateFor(utils::Vector2i(topLeft(0), topLeft(1)),
                                                utils::Vector2f(x, y));
  const auto tr = m_valueGenerator->generateFor(utils::Vector2i(topRight(0), topRight(1)),
                                                utils::Vector2f(x, y));
  const auto br = m_valueGenerator->generateFor(utils::Vector2i(bottomRight(0), bottomRight(1)),
                                                utils::Vector2f(x, y));
  const auto bl = m_valueGenerator->generateFor(utils::Vector2i(bottomLeft(0), bottomLeft(1)),
                                                utils::Vector2f(x, y));

  const auto xRange = topRight(0) - topLeft(0);
  const auto yRange = topLeft(1) - bottomLeft(1);
  const auto px     = (x - bottomLeft(0)) / xRange;
  const auto py     = (y - bottomLeft(1)) / yRange;

  const auto val = m_interpolator->interpolate(tl, tr, br, bl, px, py);
  if (!m_normalization)
  {
    return val;
  }

  return (*m_normalization)(val);
}

} // namespace pge::terrain
