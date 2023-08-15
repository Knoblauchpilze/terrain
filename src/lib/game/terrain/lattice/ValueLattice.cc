
#include "ValueLattice.hh"
#include "Bilinear.hh"
#include "Hasher.hh"
#include "WhiteNoise.hh"

namespace pge::lattice {

ValueLattice::ValueLattice(const noise::Seed seed) noexcept
  : m_hasher(std::make_unique<Hasher>(seed))
  , m_noise(std::make_unique<noise::WhiteNoise>())
  , m_interpolator(std::make_unique<interpolation::Bilinear>())
{}

auto ValueLattice::at(const float x, const float y) -> float
{
  return generateLatticePointsAndInterpolate(x, y);
}

auto ValueLattice::generateLatticePointsAndInterpolate(const float x, const float y) -> float
{
  // https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-1D-noise.html
  const auto minX = static_cast<int>(std::floor(x));
  const auto maxX = static_cast<int>(std::ceil(x + 0.5f));

  const auto minY = static_cast<int>(std::floor(y));
  const auto maxY = static_cast<int>(std::ceil(y + 0.5f));

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
