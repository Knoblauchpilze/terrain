
#include "GradientLattice.hh"
#include "GradientGenerator.hh"
#include "Hasher.hh"
#include <numbers>

namespace pge::lattice {

// https://en.cppreference.com/w/cpp/numeric/constants
constexpr auto MAGNITUDE_PERLIN_NOISE = std::numbers::sqrt2_v<float> / 2.0f;

GradientLattice::GradientLattice(IHasherPtr hasher,
                                 noise::INoisePtr noise,
                                 interpolation::IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<GradientGenerator>(std::move(hasher), std::move(noise)),
                    std::move(interpolator),
                    {[](const float value) -> float {
                      // https://digitalfreepen.com/2017/06/20/range-perlin-noise.html
                      return (MAGNITUDE_PERLIN_NOISE + value) / (2.0f * MAGNITUDE_PERLIN_NOISE);
                    }})
{}

} // namespace pge::lattice
