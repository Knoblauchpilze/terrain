
#pragma once

#include "IAreaGenerator.hh"
#include <memory>

namespace pge::terrain {

// https://stackoverflow.com/questions/7968023/c-virtual-template-method
template<typename ValueType>
class IValueGenerator
{
  public:
  virtual ~IValueGenerator() = default;

  virtual auto at(const utils::Vector2i &latticePoint) const noexcept -> ValueType = 0;
  virtual auto generateFor(const utils::Vector2i &latticePoint,
                           const utils::Vector2f &point) const noexcept -> float
    = 0;
};

template<typename ValueType>
using IValueGeneratorPtr = std::unique_ptr<IValueGenerator<ValueType>>;

} // namespace pge::terrain
