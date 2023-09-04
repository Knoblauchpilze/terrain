
#include "Bilinear2d.hh"

namespace pge::terrain {

auto Bilinear2d::interpolate(const InterpolationData2d &data) const -> float
{
  const auto bottom = data.axes[BOTTOM].evaluate();
  const auto top    = data.axes[TOP].evaluate();

  InterpolationAxis out(bottom, top, data.deltas[Y]);
  return out.evaluate();
}

} // namespace pge::terrain
