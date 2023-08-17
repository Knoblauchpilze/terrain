
#include "GradientLattice.hh"
#include <cmath>

namespace pge::lattice {

GradientLattice::GradientLattice(IHasherPtr hasher,
                                 noise::INoisePtr noise,
                                 interpolation::IInterpolatorPtr interpolator) noexcept
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
  , m_interpolator(std::move(interpolator))
{}

auto GradientLattice::at(const float x, const float y) -> float
{
  return generateLatticePointsAndInterpolate(x, y);
}

auto GradientLattice::generateLatticePointsAndInterpolate(const float x, const float y) -> float
{
  // https://adrianb.io/2014/08/09/perlinnoise.html
  const auto minX = static_cast<int>(std::floor(x));
  const auto maxX = static_cast<int>(
    std::ceil(std::nextafter(x, std::numeric_limits<float>::infinity())));

  const auto minY = static_cast<int>(std::floor(y));
  const auto maxY = static_cast<int>(
    std::ceil(std::nextafter(y, std::numeric_limits<float>::infinity())));

  auto latticeValue = [this, x, y](const int ix, const int iy) -> float {
    m_noise->seed(m_hasher->hash(ix, iy));
    const auto gradX = 2.0f * m_noise->next() - 1.0f;
    const auto gradY = 2.0f * m_noise->next() - 1.0f;

    // https://en.wikipedia.org/wiki/Perlin_noise#Implementation
    const auto distX = x - ix;
    const auto distY = y - iy;

    const auto dot = gradX * distX + gradY * distY;

    return 0.5f * (dot + 1.0f);
  };

  const auto tl = latticeValue(minX, maxY);
  const auto tr = latticeValue(maxX, maxY);
  const auto br = latticeValue(maxX, minY);
  const auto bl = latticeValue(minX, minY);

  const auto px = (x - minX) / (maxX - minX);
  const auto py = (y - minY) / (maxY - minY);

  return m_interpolator->interpolate(tl, tr, br, bl, px, py);
}

} // namespace pge::lattice
