
#include "Noise2d.hh"

namespace pge::noise {

Noise2d::Noise2d(const Type &type) noexcept
  : m_type(type)
{}

auto Noise2d::type() const noexcept -> Type
{
  return m_type;
}

} // namespace pge::noise
