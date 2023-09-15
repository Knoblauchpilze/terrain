
#include "Bilinear3d.hh"

namespace pge::terrain {

Bilinear3d::Bilinear3d(const InterpolationStrategy &strategy) noexcept
  : AbstractInterpolator<3>(strategy)
{}

auto Bilinear3d::interpolate(const InterpolationData3d &data) const -> float
{
  const auto fBottom = data.axes[FRONT_BOTTOM].evaluate();
  const auto fTop    = data.axes[FRONT_TOP].evaluate();
  const auto bTop    = data.axes[BACK_TOP].evaluate();
  const auto bBottom = data.axes[BACK_BOTTOM].evaluate();

  const auto zFront = InterpolationAxis(fBottom, fTop, data.deltas[Z], strategy());
  const auto zBack  = InterpolationAxis(bBottom, bTop, data.deltas[Z], strategy());

  InterpolationAxis out(zFront.evaluate(), zBack.evaluate(), data.deltas[Y], strategy());
  return out.evaluate();
}

} // namespace pge::terrain
