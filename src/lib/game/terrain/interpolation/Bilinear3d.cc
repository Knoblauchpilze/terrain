
#include "Bilinear3d.hh"

namespace pge::terrain {

auto Bilinear3d::interpolate(const InterpolationData3d &data) const -> float
{
  const auto fBottom = data.axes[FRONT_BOTTOM].evaluate();
  const auto fTop    = data.axes[FRONT_TOP].evaluate();
  const auto bTop    = data.axes[BACK_TOP].evaluate();
  const auto bBottom = data.axes[BACK_BOTTOM].evaluate();

  InterpolationAxis front(fBottom, fTop, data.deltas[Z]);
  InterpolationAxis back(bBottom, bTop, data.deltas[Z]);

  const auto zFront = front.evaluate();
  const auto zBack  = back.evaluate();

  InterpolationAxis out(zFront, zBack, data.deltas[Y]);
  return out.evaluate();
}

} // namespace pge::terrain
