
#pragma once

#include "IAreaGenerator.hh"
#include "ILatticePoint.hh"
#include "IPoint.hh"
#include <memory>

namespace pge::terrain {

/// https://stackoverflow.com/questions/7968023/c-virtual-template-method
template<int Dimension, typename ValueType>
class IValueGenerator
{
  public:
  virtual ~IValueGenerator() = default;

  virtual auto at(const ILatticePoint<Dimension> &latticePoint) const noexcept -> ValueType = 0;
  virtual auto generateFor(const ILatticePoint<Dimension> &latticePoint,
                           const IPoint<Dimension> &point) const noexcept -> float
    = 0;
};

template<typename ValueType>
using IValueGenerator2d = IValueGenerator<2, ValueType>;

template<typename ValueType>
using IValueGenerator3d = IValueGenerator<3, ValueType>;

template<typename ValueType>
using IValueGenerator2dPtr = std::unique_ptr<IValueGenerator2d<ValueType>>;

template<typename ValueType>
using IValueGenerator3dPtr = std::unique_ptr<IValueGenerator3d<ValueType>>;

} // namespace pge::terrain
