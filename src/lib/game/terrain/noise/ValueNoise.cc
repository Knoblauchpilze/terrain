
#include "ValueNoise.hh"

namespace pge::noise {

ValueNoise::ValueNoise(const Seed /*seed*/)
  : Noise2d(Type::Value)
{}

auto ValueNoise::at(float x, float y) const noexcept -> float
{
  return (x + y) / 20.0f;
}

} // namespace pge::noise
