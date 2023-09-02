
#include "PeriodicPerlinLattice.hh"
#include "PeriodicPerlinGenerator.hh"
#include <numbers>

namespace pge::terrain {

// https://digitalfreepen.com/2017/06/20/range-perlin-noise.html
// But vectors are not normalized here, so a similar argument is
// giving the range `[-1; 1]`.
constexpr auto MAGNITUDE_PERLIN_NOISE = 1.0f;

PeriodicPerlinLattice::PeriodicPerlinLattice(const int period,
                                             const Seed seed,
                                             IInterpolatorPtr interpolator)
  : AbstractLattice(std::make_unique<PeriodicPerlinGenerator>(period, seed),
                    std::move(interpolator),
                    {[](const float value) -> float {
                      return (MAGNITUDE_PERLIN_NOISE + value) / (2.0f * MAGNITUDE_PERLIN_NOISE);
                    }})
{}

} // namespace pge::terrain
