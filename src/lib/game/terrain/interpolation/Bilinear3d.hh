
#pragma once

#include "IInterpolator.hh"

namespace pge::terrain {

class Bilinear3d : public IInterpolator<4, 2>
{
  public:
  Bilinear3d() noexcept  = default;
  ~Bilinear3d() override = default;

  enum Axis
  {
    FRONT_BOTTOM = 0,
    FRONT_TOP    = 1,
    BACK_TOP     = 2,
    BACK_BOTTOM  = 3,
    Z            = 0,
    Y            = 1
  };

  auto interpolate(const InterpolationData3d &data) const -> float override;
};

} // namespace pge::terrain
