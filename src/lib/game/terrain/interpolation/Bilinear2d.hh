
#pragma once

#include "AbstractInterpolator.hh"

namespace pge::terrain {

class Bilinear2d : public AbstractInterpolator<2>
{
  public:
  Bilinear2d(const InterpolationStrategy &strategy) noexcept;
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
