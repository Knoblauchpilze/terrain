
#include "Lattice.hh"
#include "Bilinear.hh"
#include "Noise.hh"

namespace pge::lattice {

auto hashCoordinates(const int x, const int y) -> noise::Seed
{
  const auto px = (x < 0 ? -2 * x + 1 : 2 * x);
  const auto py = (y < 0 ? -2 * y + 1 : 2 * y);

  auto hash = px;
  hash ^= py << 16;
  hash ^= py >> 16;

  return hash;
}

Lattice::Lattice(const noise::Seed seed) noexcept
  : m_seed(seed)
  , m_noise(std::make_unique<noise::Noise>())
  , m_interpolator(std::make_unique<interpolation::Bilinear>())
{}

auto Lattice::at(const float x, const float y) -> float
{
  return generateLatticePointsAndInterpolate(x, y);
}

auto Lattice::generateLatticePointsAndInterpolate(const float x, const float y) -> float
{
  const auto minX = static_cast<int>(std::floor(x));
  const auto maxX = static_cast<int>(std::ceil(x + 0.5f));

  const auto minY = static_cast<int>(std::floor(y));
  const auto maxY = static_cast<int>(std::ceil(y + 0.5f));

  // https://gamedev.stackexchange.com/questions/183142/how-can-i-create-a-persistent-seed-for-each-chunk-of-an-infinite-procedural-worl
  auto latticeValue = [this](const int x, const int y) -> float {
    auto seed1d = hashCoordinates(x, y) ^ m_seed;
    m_noise->seed(seed1d);

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
