
#pragma once

#include "IInterpolator.hh"

namespace pge::terrain {

class Bilinear2d : public IInterpolator<2>
{
  public:
  Bilinear2d() noexcept  = default;
  ~Bilinear2d() override = default;

  enum Axis
  {
    BOTTOM = 0,
    TOP    = 1,
    Y      = 0
  };

  auto interpolate(const InterpolationData2d &data) const -> float override;
};

} // namespace pge::terrain
