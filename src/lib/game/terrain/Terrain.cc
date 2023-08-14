
#include "Terrain.hh"

namespace pge::terrain {

Terrain::Terrain(int width, int height, Noise2dPtr noise) noexcept
  : utils::CoreObject(std::to_string(width) + "x" + std::to_string(height))
  , m_width(width)
  , m_height(height)
  , m_noise(std::move(noise))
{
  setService("terrain");
}

auto Terrain::w() const noexcept -> int
{
  return m_width;
}

auto Terrain::h() const noexcept -> int
{
  return m_height;
}

auto Terrain::at(const int x, const int y) const -> Type
{
  if (x < 5)
  {
    if (y < 5)
    {
      return Type::Coast;
    }
    else
    {
      return Type::Ocean;
    }
  }
  else
  {
    if (y < 5)
    {
      return Type::Plain;
    }
    else if (y < 8)
    {
      return Type::Mountain;
    }
    else
    {
      return Type::Ice;
    }
  }
  return Type::Coast;
}

void Terrain::load(const std::string &fileName)
{
  warn("Should load " + fileName);
}

void Terrain::save(const std::string &fileName) const
{
  warn("Should save " + fileName);
}

} // namespace pge::terrain
