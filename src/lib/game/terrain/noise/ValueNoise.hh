
#pragma once

#include "Noise2d.hh"

namespace pge::noise {

class ValueNoise : public Noise2d
{
  public:
  ValueNoise(const Seed seed);
  ~ValueNoise() override = default;

  auto next() const noexcept -> float override;

  protected:
  void seed(const Seed seed) override;
};

} // namespace pge::noise
