
#include "PeriodicGradientLattice.hh"
#include "PeriodicGradientGenerator.hh"
#include <numbers>

namespace pge::lattice {

// https://en.cppreference.com/w/cpp/numeric/constants
constexpr auto MAGNITUDE_PERLIN_NOISE = std::numbers::sqrt2_v<float> / 2.0f;

PeriodicGradientLattice::PeriodicGradientLattice(const int period,
                                                 const noise::Seed seed,
                                                 interpolation::IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<PeriodicGradientGenerator>(period, seed),
                    std::move(interpolator),
                    {[](const float value) -> float {
                      return (MAGNITUDE_PERLIN_NOISE + value) / (2.0f * MAGNITUDE_PERLIN_NOISE);
                    }})
{}

} // namespace pge::lattice
