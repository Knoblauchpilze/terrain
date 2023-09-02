
#include "PeriodicGradientLattice.hh"
#include "PeriodicGradientGenerator.hh"
#include <numbers>

namespace pge::terrain {

// https://en.cppreference.com/w/cpp/numeric/constants
constexpr auto MAGNITUDE_GRADIENT_NOISE = std::numbers::sqrt2_v<float> / 2.0f;

PeriodicGradientLattice::PeriodicGradientLattice(const int period,
                                                 const Seed seed,
                                                 IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<PeriodicGradientGenerator>(period, seed),
                    std::move(interpolator),
                    {[](const float value) -> float {
                      return (MAGNITUDE_GRADIENT_NOISE + value) / (2.0f * MAGNITUDE_GRADIENT_NOISE);
                    }})
{}

} // namespace pge::terrain
