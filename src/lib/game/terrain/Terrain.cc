
#include "Terrain.hh"

namespace pge::terrain {

namespace {
constexpr auto OCEAN_THRESHOLD    = 0.2f;
constexpr auto COAST_THRESHOLD    = 0.5f;
constexpr auto PLAIN_THRESHOLD    = 0.6f;
constexpr auto MOUNTAIN_THRESHOLD = 0.85f;
constexpr auto ICE_THRESHOLD      = 1.0f;

auto heightToTerrainType(const float height) noexcept -> Type
{
  if (height < OCEAN_THRESHOLD)
  {
    return Type::Ocean;
  }
  else if (height < COAST_THRESHOLD)
  {
    return Type::Coast;
  }
  else if (height < PLAIN_THRESHOLD)
  {
    return Type::Plain;
  }
  else if (height < MOUNTAIN_THRESHOLD)
  {
    return Type::Mountain;
  }
  else
  {
    return Type::Ice;
  }
}

} // namespace

Terrain::Terrain(int width, int height, noise::Noise2dPtr noise) noexcept
  : utils::CoreObject(std::to_string(width) + "x" + std::to_string(height))
  , m_width(width)
  , m_height(height)
  , m_noise(std::move(noise))
{
  setService("terrain");
  generate();
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
  if (x < 0 || x >= w() || y < 0 || y >= h())
  {
    error("can't get terrain at " + std::to_string(x) + "x" + std::to_string(y),
          "invalid dimensions for " + std::to_string(w()) + "x" + std::to_string(h()));
  }

  return m_land[y * w() + x];
}

void Terrain::load(const std::string &fileName)
{
  warn("Should load " + fileName);
}

void Terrain::save(const std::string &fileName) const
{
  warn("Should save " + fileName);
}

void Terrain::generate()
{
  for (int y = 0; y < h(); ++y)
  {
    for (int x = 0; x < w(); ++x)
    {
      const auto t = heightToTerrainType(m_noise->at(x, y));
      m_land.push_back(t);
    }
  }
}

} // namespace pge::terrain
