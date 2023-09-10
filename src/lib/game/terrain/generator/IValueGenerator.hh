
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

  static constexpr auto DIMENSION = Dimension;
};

template<int Dimension, typename ValueType>
using IValueGeneratorPtr = std::unique_ptr<IValueGenerator<Dimension, ValueType>>;

template<typename ValueType>
using IValueGenerator2dPtr = IValueGeneratorPtr<2, ValueType>;

template<typename ValueType>
using IValueGenerator3dPtr = IValueGeneratorPtr<3, ValueType>;

} // namespace pge::terrain
