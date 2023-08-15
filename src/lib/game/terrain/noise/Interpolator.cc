
#include "Interpolator.hh"

namespace pge::noise::interpolation {
namespace {
auto bilinear(const float tl,
              const float tr,
              const float br,
              const float bl,
              const float px,
              const float py) -> float
{
  const auto top    = px * tl + (1.0f - px) * tr;
  const auto bottom = px * bl + (1.0f - px) * br;

  return py * bottom + (1.0f - py) * top;
}
} // namespace

Interpolator::Interpolator(const Algorithm &algorithm) noexcept
  : m_algorithm(algorithm)
{}

auto Interpolator::interpolate(const float tl,
                               const float tr,
                               const float br,
                               const float bl,
                               const float px,
                               const float py) const -> float
{
  switch (m_algorithm)
  {
    case Algorithm::BILINEAR:
    default:
      return bilinear(tl, tr, br, bl, px, py);
  }
}

} // namespace pge::noise::interpolation
