
#pragma once

#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

class AbstractGradientGenerator : public IValueGenerator<2, 2>
{
  public:
  AbstractGradientGenerator()           = default;
  ~AbstractGradientGenerator() override = default;

  auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float override;
};

using AbstractGradientGeneratorPtr = std::unique_ptr<AbstractGradientGenerator>;

} // namespace pge::terrain
