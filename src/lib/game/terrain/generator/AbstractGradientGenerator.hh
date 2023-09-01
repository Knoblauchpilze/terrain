
#pragma once

#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

class AbstractGradientGenerator : public IValueGenerator<utils::Vector2f>
{
  public:
  AbstractGradientGenerator()           = default;
  ~AbstractGradientGenerator() override = default;

  auto generateFor(const utils::Vector2i &latticePoint, const utils::Vector2f &point) const noexcept
    -> float override;
};

using AbstractGradientGeneratorPtr = std::unique_ptr<AbstractGradientGenerator>;

} // namespace pge::terrain
