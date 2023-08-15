
#include "Noise2d.hh"

namespace pge::noise {

Noise2d::Noise2d(const Type &type, const Seed seed) noexcept
  : m_type(type)
  , m_seed(seed)
{}

auto Noise2d::type() const noexcept -> Type
{
  return m_type;
}

void Noise2d::seed(const int x, const int y)
{
  // https://stackoverflow.com/questions/682438/hash-function-providing-unique-uint-from-an-integer-coordinate-pair
  auto seed1d = ((y << 16) | x) + m_seed;
  seed(seed1d);
}

} // namespace pge::noise
