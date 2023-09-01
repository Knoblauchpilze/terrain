
#pragma once

#include "IAreaGenerator.hh"

namespace pge::terrain {

class Area2dGenerator : public IAreaGenerator<2>
{
  public:
  ~Area2dGenerator() override = default;

  enum Corners
  {
    TOP_LEFT     = 0,
    TOP_RIGHT    = 1,
    BOTTOM_RIGHT = 2,
    BOTTOM_LEFT  = 3,
    COUNT        = 4
  };

  auto areaSurrounding(const Point2d &p) const noexcept -> Area2d override;
};

} // namespace pge::terrain
