
#pragma once

#include "IAreaGenerator.hh"
#include <memory>

namespace pge::lattice {

class IValueGenerator
{
  public:
  virtual ~IValueGenerator() = default;

  virtual auto generateFor(const utils::Vector2i &latticePoint,
                           const utils::Vector2f &point) const noexcept -> float
    = 0;
};

using IValueGeneratorPtr = std::unique_ptr<IValueGenerator>;

} // namespace pge::lattice
