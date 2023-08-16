
#include "ValueLattice.hh"
#include <cmath>

namespace pge::lattice {

ValueLattice::ValueLattice(IHasherPtr hasher,
                           noise::INoisePtr noise,
                           interpolation::IInterpolatorPtr interpolator) noexcept
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
  , m_interpolator(std::move(interpolator))
{}

auto ValueLattice::at(const float x, const float y) -> float
{
  return generateLatticePointsAndInterpolate(x, y);
}

auto ValueLattice::generateLatticePointsAndInterpolate(const float x, const float y) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto minX = static_cast<int>(std::floor(x));
  // https://stackoverflow.com/questions/61756878/how-to-find-the-next-greater-value-generically-in-c-for-integers-and-floats
  const auto maxX = static_cast<int>(
    std::ceil(std::nextafter(x, std::numeric_limits<float>::infinity())));

  const auto minY = static_cast<int>(std::floor(y));
  const auto maxY = static_cast<int>(
    std::ceil(std::nextafter(y, std::numeric_limits<float>::infinity())));

  auto latticeValue = [this](const int x, const int y) -> float {
    m_noise->seed(m_hasher->hash(x, y));
    return m_noise->next();
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
