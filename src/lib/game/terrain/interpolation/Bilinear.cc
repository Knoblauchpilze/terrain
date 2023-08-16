
#include "Bilinear.hh"

namespace pge::interpolation {

auto Bilinear::interpolate(const float tl,
                           const float tr,
                           const float br,
                           const float bl,
                           const float px,
                           const float py) const -> float
{
  const auto top    = (1.0f - px) * tl + px * tr;
  const auto bottom = (1.0f - px) * bl + px * br;

  return (1.0f - py) * bottom + py * top;
}

} // namespace pge::interpolation
