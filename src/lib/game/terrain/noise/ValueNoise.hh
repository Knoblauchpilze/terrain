
#pragma once

#include "Noise2d.hh"

namespace pge::noise {

class ValueNoise : public Noise2d
{
  public:
  ValueNoise(const Seed seed);
  ~ValueNoise() override = default;

  auto at(float x, float y) const noexcept -> float override;
};

} // namespace pge::noise
