
#include "Terrain.hh"

#include "AbstractLattice.hh"
#include <iostream>

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

Terrain::Terrain(lattice::ILatticePtr lattice, const int scale) noexcept
  : utils::CoreObject("2d")
  , m_lattice(std::move(lattice))
  , m_scale(scale)
{
  setService("terrain");
}

auto Terrain::height(const float x, const float y) const -> float
{
  const auto begin = std::chrono::steady_clock::now();
  const auto h     = m_lattice->at(x / m_scale, y / m_scale);
  const auto end   = std::chrono::steady_clock::now();

  m_timers.heightDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                               .count();
  const auto l = dynamic_cast<lattice::AbstractLattice<utils::Vector2f> *>(m_lattice.get());
  if (l != nullptr)
  {
    m_timers.areaDuration += l->areaDuration;
    m_timers.generateForDuration += l->generateForDuration;
    m_timers.interpolateDuration += l->interpolateDuration;
    m_timers.normalizeDuration += l->normalizeDuration;

    m_timers.modulusDuration += l->modulusDuration;
    m_timers.permDuration += l->permDuration;
    m_timers.gradDuration += l->gradDuration;
  }

  return h;
}

auto Terrain::at(const float x, const float y) const -> Type
{
  const auto begin = std::chrono::steady_clock::now();
  const auto tt    = heightToTerrainType(height(x, y));
  const auto end   = std::chrono::steady_clock::now();

  m_timers.atDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  return tt;
}

void Terrain::load(const std::string &fileName)
{
  warn("Should load " + fileName);
}

void Terrain::save(const std::string &fileName) const
{
  warn("Should save " + fileName);
}

auto Terrain::timers() const noexcept -> Performance
{
  return m_timers;
}

void Terrain::increaseTimers() noexcept
{
  ++m_timers.steps;
}

} // namespace pge::terrain
