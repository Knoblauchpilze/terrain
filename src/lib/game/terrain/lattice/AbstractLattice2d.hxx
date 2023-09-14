
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
  : AbstractLattice<2, ValueType>(std::make_unique<Area2dGenerator>(),
                                  std::move(valueGenerator),
                                  std::move(interpolator),
                                  std::move(normalization))
{}

template<typename ValueType>
inline auto AbstractLattice2d<ValueType>::at(const Point2d &p) -> float
{
  // https://stackoverflow.com/questions/1120833/derived-template-class-access-to-base-class-member-data
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto area = this->m_areaGenerator->areaSurrounding(p);

  const auto &topLeft     = area.points[Area2dGenerator::TOP_LEFT];
  const auto &topRight    = area.points[Area2dGenerator::TOP_RIGHT];
  const auto &bottomRight = area.points[Area2dGenerator::BOTTOM_RIGHT];
  const auto &bottomLeft  = area.points[Area2dGenerator::BOTTOM_LEFT];

  const auto tl = this->fromCacheOrGenerate(topLeft, p);
  const auto tr = this->fromCacheOrGenerate(topRight, p);
  const auto br = this->fromCacheOrGenerate(bottomRight, p);
  const auto bl = this->fromCacheOrGenerate(bottomLeft, p);

  const auto xRange = topRight(0) - topLeft(0);
  const auto yRange = topLeft(1) - bottomLeft(1);
  const auto px     = (p(0) - bottomLeft(0)) / xRange;
  const auto py     = (p(1) - bottomLeft(1)) / yRange;

  InterpolationData2d data{};
  data.axes[Bilinear2d::BOTTOM] = InterpolationAxis(bl, br, px);
  data.axes[Bilinear2d::TOP]    = InterpolationAxis(tl, tr, px);
  data.deltas[Bilinear2d::Y]    = py;

  const auto val = this->m_interpolator->interpolate(data);
  if (!this->m_normalization)
  {
    return val;
  }

  return (*this->m_normalization)(val);
}

template<typename ValueType>
inline auto AbstractLattice2d<ValueType>::fromCacheOrGenerate(const LatticePoint2d &lp,
                                                              const Point2d &p) const -> float
{
  return this->m_valueGenerator->generateFor(lp, p);
}

} // namespace pge::terrain
