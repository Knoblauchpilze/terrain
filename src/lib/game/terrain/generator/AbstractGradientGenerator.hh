
#pragma once

#include "IGradientGenerator.hh"
#include <memory>

namespace pge::terrain {

class AbstractGradientGenerator : public IGradientGenerator<2, 3>
{
  public:
  AbstractGradientGenerator()           = default;
  ~AbstractGradientGenerator() override = default;

  auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float override;
};

using AbstractGradientGeneratorPtr = std::unique_ptr<AbstractGradientGenerator>;

} // namespace pge::terrain
