
#include "ValueNoise.hh"

namespace pge::terrain {

ValueNoise::ValueNoise(const int /*seed*/)
  : Noise2d()
{}

auto ValueNoise::at(float /*x*/, float /*y*/) const noexcept -> float
{
  return 0.0f;
}

} // namespace pge::terrain
