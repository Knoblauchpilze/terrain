
#pragma once

#include "AbstractLattice.hh"
#include "AreaGenerator.hh"
#include <cmath>

#include "GradientGenerator.hh"
#include "PeriodicPerlinGenerator.hh"
#include <chrono>

namespace pge::lattice {

template<typename ValueType>
AbstractLattice<ValueType>::AbstractLattice(IValueGeneratorPtr<ValueType> valueGenerator,
                                            interpolation::IInterpolatorPtr interpolator,
                                            std::optional<NormalizationFunc> normalization) noexcept
  : m_areaGenerator(std::make_unique<AreaGenerator>())
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
  , m_normalization(std::move(normalization))
{}

template<typename ValueType>
auto AbstractLattice<ValueType>::at(const float x, const float y) -> float
{
  this->areaDuration        = 0;
  this->generateForDuration = 0;
  this->interpolateDuration = 0;
  this->normalizeDuration   = 0;

  this->modulusDuration = 0;
  this->permDuration    = 0;
  this->gradDuration    = 0;
  const auto st         = std::chrono::steady_clock::now();

  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto area = m_areaGenerator->areaSurrounding(x, y);

  const auto p1 = std::chrono::steady_clock::now();

  const auto tl = m_valueGenerator->generateFor(area.topLeft, utils::Vector2f(x, y));
  const auto tr = m_valueGenerator->generateFor(area.topRight, utils::Vector2f(x, y));
  const auto br = m_valueGenerator->generateFor(area.bottomRight, utils::Vector2f(x, y));
  const auto bl = m_valueGenerator->generateFor(area.bottomLeft, utils::Vector2f(x, y));

  const auto p2 = std::chrono::steady_clock::now();

  const auto xRange = area.topRight.x() - area.topLeft.x();
  const auto yRange = area.topLeft.y() - area.bottomLeft.y();
  const auto px     = (x - area.bottomLeft.x()) / xRange;
  const auto py     = (y - area.bottomLeft.y()) / yRange;

  const auto p3 = std::chrono::steady_clock::now();

  const auto val = m_interpolator->interpolate(tl, tr, br, bl, px, py);

  const auto p4 = std::chrono::steady_clock::now();

  if (!m_normalization)
  {
    return val;
  }

  const auto p5 = std::chrono::steady_clock::now();

  const auto v = (*m_normalization)(val);

  const auto p6 = std::chrono::steady_clock::now();

  this->areaDuration        = std::chrono::duration_cast<std::chrono::nanoseconds>(p1 - st).count();
  this->generateForDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count();
  this->interpolateDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(p4 - p3).count();
  this->normalizeDuration   = std::chrono::duration_cast<std::chrono::nanoseconds>(p6 - p5).count();

  // const auto g          = dynamic_cast<PeriodicPerlinGenerator *>(m_valueGenerator.get());
  const auto g          = dynamic_cast<GradientGenerator *>(m_valueGenerator.get());
  this->modulusDuration = g->modulusDuration;
  this->permDuration    = g->permDuration;
  this->gradDuration    = g->gradDuration;

  return v;
}

} // namespace pge::lattice
