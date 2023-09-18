
#pragma once

#include "Terrain.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <memory>

namespace pge::terrain {

class Map : public utils::CoreObject
{
  public:
  Map() noexcept;

  auto at(const float x, const float y) const -> Type;
  auto height(const float x, const float y) const -> float;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  auto mode() const noexcept -> TerrainMode;
  void toggleMode(bool prev);

  auto lattice() const noexcept -> LatticeType;
  auto interpolation() const noexcept -> InterpolationStrategy;
  auto scale() const noexcept -> int;
  auto period() const noexcept -> int;
  auto cacheSize() const noexcept -> int;

  auto seed() const noexcept -> Seed;

  void nextLattice(bool prev);
  void nextInterpolation(bool prev);
  void nextScale(bool prev);
  void nextPeriod(bool prev);
  void nextCacheSize(bool prev);

  void nextSeed();

  auto layersCount() const noexcept -> int;
  auto lacunarity() const noexcept -> int;
  auto gain() const noexcept -> float;

  void nextLayersCount(bool prev) noexcept;
  void nextLacunarity(bool prev) noexcept;
  void nextGain(bool prev) noexcept;

  private:
  TerrainMode m_mode{TerrainMode::NOISE};
  Terrain m_terrain{};
};

using MapPtr = std::unique_ptr<Map>;

} // namespace pge::terrain
