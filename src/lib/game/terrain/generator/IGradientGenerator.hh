
#pragma once

#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class IGradientGenerator : public IValueGenerator2d<IPoint<Dimension>>
{
  public:
  virtual ~IGradientGenerator() = default;

  virtual auto at(const LatticePoint2d &latticePoint) const noexcept -> IPoint<Dimension> = 0;
  virtual auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float
    = 0;
};

} // namespace pge::terrain
