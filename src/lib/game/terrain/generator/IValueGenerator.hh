
#pragma once

#include "IAreaGenerator.hh"
#include "ILatticePoint.hh"
#include "IPoint.hh"
#include <memory>

namespace pge::terrain {

// https://stackoverflow.com/questions/7968023/c-virtual-template-method
template<typename ValueType>
class IValueGenerator
{
  public:
  virtual ~IValueGenerator() = default;

  virtual auto at(const LatticePoint2d &latticePoint) const noexcept -> ValueType = 0;
  virtual auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float
    = 0;
};

template<typename ValueType>
using IValueGeneratorPtr = std::unique_ptr<IValueGenerator<ValueType>>;

} // namespace pge::terrain
