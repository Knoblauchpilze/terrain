
#pragma once

#include "IAreaGenerator.hh"

namespace pge::terrain {

class Area3dGenerator : public IAreaGenerator<3>
{
  public:
  ~Area3dGenerator() override = default;

  enum Corners
  {
    FRONT_TOP_LEFT     = 0,
    FRONT_TOP_RIGHT    = 1,
    FRONT_BOTTOM_RIGHT = 2,
    FRONT_BOTTOM_LEFT  = 3,
    BACK_TOP_LEFT      = 4,
    BACK_TOP_RIGHT     = 5,
    BACK_BOTTOM_RIGHT  = 6,
    BACK_BOTTOM_LEFT   = 7,
    COUNT              = 8
  };

  auto areaSurrounding(const Point3d &p) const noexcept -> Area3d override;
};

} // namespace pge::terrain
