
#include "Bilinear.hh"

namespace pge::interpolation {

auto Bilinear::interpolate(const float tl,
                           const float tr,
                           const float br,
                           const float bl,
                           const float px,
                           const float py) const -> float
{
  const auto top    = px * tl + (1.0f - px) * tr;
  const auto bottom = px * bl + (1.0f - px) * br;

  return py * bottom + (1.0f - py) * top;
}

} // namespace pge::interpolation
