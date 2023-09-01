
#pragma once

#include "IValueGenerator.hh"
#include <maths_utils/Vector2.hh>
#include <memory>

namespace pge::terrain {

class AbstractGradientGenerator : public IValueGenerator<utils::Vector2f>
{
  public:
  AbstractGradientGenerator()           = default;
  ~AbstractGradientGenerator() override = default;

  auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float override;
};

using AbstractGradientGeneratorPtr = std::unique_ptr<AbstractGradientGenerator>;

} // namespace pge::terrain
