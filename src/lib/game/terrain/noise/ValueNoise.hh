
#pragma once

#include "Noise2d.hh"

namespace pge::terrain {

class ValueNoise : public Noise2d
{
  public:
  ValueNoise(const int seed);
  ~ValueNoise() override = default;

  auto at(float x, float y) const noexcept -> float override;
};

} // namespace pge::terrain
