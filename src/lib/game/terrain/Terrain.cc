
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
    return Type::OCEAN;
  }
  else if (height < COAST_THRESHOLD)
  {
    return Type::COAST;
  }
  else if (height < PLAIN_THRESHOLD)
  {
    return Type::PLAIN;
  }
  else if (height < MOUNTAIN_THRESHOLD)
  {
    return Type::MOUNTAIN;
  }
  else
  {
    return Type::ICE;
  }
}

} // namespace

Terrain::Terrain(ILattice2dPtr lattice, const int scale) noexcept
  : utils::CoreObject("2d")
  , m_lattice(std::move(lattice))
  , m_scale(scale)
{
  setService("terrain");
}

auto Terrain::height(const float x, const float y) const -> float
{
  return m_lattice->at(Point2d(x / m_scale, y / m_scale));
}

auto Terrain::at(const float x, const float y) const -> Type
{
  return heightToTerrainType(height(x, y));
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
