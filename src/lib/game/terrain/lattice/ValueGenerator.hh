
#pragma once

#include "INoise.hh"
#include "IValueGenerator.hh"
#include <memory>

namespace pge::lattice {

class ValueGenerator : public IValueGenerator
{
  public:
  ValueGenerator(noise::INoisePtr noise);
  ~ValueGenerator() override = default;

  auto generateFor(const utils::Vector2i &latticePoint, const utils::Vector2f &point) const noexcept
    -> float override;

  private:
  noise::INoisePtr m_noise;
};

} // namespace pge::lattice
