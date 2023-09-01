
#include "GradientLattice.hh"
#include "GradientGenerator.hh"
#include <numbers>

namespace pge::terrain {

// https://en.cppreference.com/w/cpp/numeric/constants
constexpr auto MAGNITUDE_PERLIN_NOISE = std::numbers::sqrt2_v<float> / 2.0f;

GradientLattice::GradientLattice(IHasher2dPtr hasher, INoisePtr noise, IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<GradientGenerator>(std::move(hasher), std::move(noise)),
                    std::move(interpolator),
                    {[](const float value) -> float {
                      return (MAGNITUDE_PERLIN_NOISE + value) / (2.0f * MAGNITUDE_PERLIN_NOISE);
                    }})
{}

} // namespace pge::terrain
