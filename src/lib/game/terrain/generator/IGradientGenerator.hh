
#pragma once

#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int PointDimension, int GradientDimension>
class IGradientGenerator : public IValueGenerator<PointDimension, IPoint<GradientDimension>>
{
  public:
  virtual ~IGradientGenerator() = default;

  virtual auto at(const ILatticePoint<PointDimension> &latticePoint) const noexcept
    -> IPoint<GradientDimension> = 0;
  virtual auto generateFor(const ILatticePoint<PointDimension> &latticePoint,
                           const IPoint<PointDimension> &point) const noexcept -> float
    = 0;
};

} // namespace pge::terrain
