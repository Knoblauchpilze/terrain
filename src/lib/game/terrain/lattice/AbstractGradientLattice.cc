
#include "AbstractGradientLattice.hh"
#include <numbers>

namespace pge::terrain {

/// https://en.cppreference.com/w/cpp/numeric/constants
constexpr auto MAGNITUDE_GRADIENT_NOISE = std::numbers::sqrt2_v<float> / 2.0f;

AbstractGradientLattice::AbstractGradientLattice(IValueGenerator2dPtr<Point3d> valueGenerator,
                                                 IInterpolator2dPtr interpolator)
  : AbstractLattice2d(std::move(valueGenerator),
                      std::move(interpolator),
                      {[](const float value) -> float {
                        return (MAGNITUDE_GRADIENT_NOISE + value)
                               / (2.0f * MAGNITUDE_GRADIENT_NOISE);
                      }})
{}

} // namespace pge::terrain
