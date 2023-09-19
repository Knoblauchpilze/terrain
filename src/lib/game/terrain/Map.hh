
#pragma once

#include "Terrain.hh"
#include "TerrainMode.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <functional>
#include <memory>
#include <unordered_map>

namespace pge::terrain {

auto str(const TerrainMode &terrain) noexcept -> std::string;

class Map : public utils::CoreObject
{
  public:
  Map() noexcept;

  auto at(const float x, const float y) const -> Type;
  auto height(const float x, const float y) const -> float;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  auto terrain() const noexcept -> TerrainMode;
  void nextTerrain(bool prev) noexcept;

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
  /// https://medium.com/@henchman/adventures-in-procedural-terrain-generation-part-1-b64c29e2367a
  TerrainMode m_mode{TerrainMode::HEIGHT};

  std::unordered_map<TerrainMode, TerrainPtr> m_terrains{};

  auto defaultTerrain() const noexcept -> const Terrain &;

  using TerrainProcess = std::function<void(Terrain &)>;
  void applyToTerrain(const TerrainProcess &process);
};

using MapPtr = std::unique_ptr<Map>;

} // namespace pge::terrain
