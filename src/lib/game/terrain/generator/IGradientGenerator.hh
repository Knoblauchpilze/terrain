
#pragma once

#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class IGradientGenerator : public IValueGenerator<IPoint<Dimension>>
{
  public:
  virtual ~IGradientGenerator() = default;

  virtual auto at(const LatticePoint2d &latticePoint) const noexcept -> IPoint<Dimension> = 0;
  virtual auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float
    = 0;
};

template<typename ValueType>
using IValueGeneratorPtr = std::unique_ptr<IValueGenerator<ValueType>>;

} // namespace pge::terrain
