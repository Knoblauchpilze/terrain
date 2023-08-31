
#pragma once

#include "ILatticePoint.hh"
#include "IPoint.hh"
#include <eigen3/Eigen/Eigen>
#include <memory>

namespace pge::terrain {

// https://stackoverflow.com/questions/7968023/c-virtual-template-method
template<int SpaceDimension, int ValueDimension>
class IValueGenerator
{
  public:
  virtual ~IValueGenerator() = default;

  using LatticePoint = ILatticePoint<SpaceDimension>;
  using Point        = IPoint<SpaceDimension>;
  using Value        = IPoint<ValueDimension>;

  virtual auto at(const LatticePoint &latticePoint) const noexcept -> Value = 0;
  virtual auto generateFor(const LatticePoint &latticePoint, const Point &point) const noexcept
    -> float
    = 0;

  protected:
  int m_spaceDimension{SpaceDimension};
  int m_valueDimension{ValueDimension};
};

template<int SpaceDimension, int ValueDimension>
using IValueGeneratorPtr = std::unique_ptr<IValueGenerator<SpaceDimension, ValueDimension>>;

} // namespace pge::terrain
