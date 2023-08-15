
#include "ValueNoise.hh"

namespace pge::noise {

ValueNoise::ValueNoise(const Seed seed)
  : Noise2d(Type::Value, seed)
{}

auto ValueNoise::next() const noexcept -> float
{
  return 2.0f;
}

void ValueNoise::seed(const Seed /*seed*/) {}

} // namespace pge::noise
