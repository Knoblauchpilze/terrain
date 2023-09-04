
#include "Bilinear2d.hh"

namespace pge::terrain {

auto Bilinear2d::interpolate(const InterpolationData2d &data) const -> float
{
  const auto bottom = data.axes[0].evaluate();
  const auto top    = data.axes[1].evaluate();

  InterpolationAxis out(bottom, top, data.deltas[0]);
  return out.evaluate();
}

} // namespace pge::terrain
