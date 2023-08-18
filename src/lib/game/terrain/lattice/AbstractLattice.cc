
#include "AbstractLattice.hh"
#include "AreaGenerator.hh"
#include <cmath>

namespace pge::lattice {

AbstractLattice::AbstractLattice(IValueGeneratorPtr valueGenerator,
                                 interpolation::IInterpolatorPtr interpolator) noexcept
  : m_areaGenerator(std::make_unique<AreaGenerator>())
  , m_valueGenerator(std::move(valueGenerator))
  , m_interpolator(std::move(interpolator))
{}

auto AbstractLattice::at(const float x, const float y) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto area = m_areaGenerator->areaSurrounding(x, y);

  const auto tl = m_valueGenerator->generateFor(area.topLeft, utils::Vector2f(x, y));
  const auto tr = m_valueGenerator->generateFor(area.topRight, utils::Vector2f(x, y));
  const auto br = m_valueGenerator->generateFor(area.bottomRight, utils::Vector2f(x, y));
  const auto bl = m_valueGenerator->generateFor(area.bottomLeft, utils::Vector2f(x, y));

  const auto xRange = area.topRight.x() - area.topLeft.x();
  const auto yRange = area.topLeft.y() - area.bottomLeft.y();
  const auto px     = (x - area.bottomLeft.x()) / xRange;
  const auto py     = (y - area.bottomLeft.y()) / yRange;

  return m_interpolator->interpolate(tl, tr, br, bl, px, py);
}

} // namespace pge::lattice
