
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

Terrain::Terrain(noise::Noise2dPtr noise) noexcept
  : utils::CoreObject("2d")
  , m_noise(std::move(noise))
{
  setService("terrain");
}

auto Terrain::at(const int x, const int y) const -> Type
{
  m_noise->seed(x, y);
  return heightToTerrainType(m_noise->next());
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
