
#pragma once

#include "ILattice.hh"
#include "InterpolationStrategy.hh"
#include "LatticeType.hh"
#include "PositiveCyclicInteger.hh"
#include "Seed.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <vector>

namespace pge::terrain {

class Terrain : public utils::CoreObject
{
  public:
  Terrain() noexcept;

  auto height(const float x, const float y) const -> float;
  auto at(const float x, const float y) const -> Type;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

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
  static constexpr auto MIN_NOISE_PERIOD  = 4;
  static constexpr auto MAX_NOISE_PERIOD  = 1024;
  static constexpr auto MIN_TERRAIN_SCALE = 2;
  static constexpr auto MAX_TERRAIN_SCALE = 64;

  static constexpr auto MIN_VALUE_GENERATOR_CACHE_SIZE = 128;
  static constexpr auto MAX_VALUE_GENERATOR_CACHE_SIZE = 4096;

  static constexpr auto CYCLIC_VALUES_STEP = 2;

  Seed m_seed{1993};
  PositiveCyclicInteger m_period{MIN_NOISE_PERIOD, 16, MAX_NOISE_PERIOD, CYCLIC_VALUES_STEP};
  PositiveCyclicInteger m_scale{MIN_TERRAIN_SCALE, 8, MAX_TERRAIN_SCALE, CYCLIC_VALUES_STEP};
  PositiveCyclicInteger m_cacheSize{MIN_VALUE_GENERATOR_CACHE_SIZE,
                                    256,
                                    MAX_VALUE_GENERATOR_CACHE_SIZE,
                                    CYCLIC_VALUES_STEP};
  InterpolationStrategy m_interpolationStrategy{InterpolationStrategy::LINEAR};
  LatticeType m_latticeType{LatticeType::PERIODIC_PERLIN};

  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/simple-pattern-examples.html
  static constexpr auto MIN_LAYER_COUNT = 1;
  static constexpr auto MAX_LAYER_COUNT = 8;

  static constexpr auto MIN_LACUNARITY = 1;
  static constexpr auto MAX_LACUNARITY = 8;

  static constexpr auto MIN_LAYER_GAIN_EXPONENT = 1;
  static constexpr auto MAX_LAYER_GAIN_EXPONENT = 8;

  static constexpr auto TERRAIN_POWER_BASE = 2;

  PositiveCyclicInteger m_layerCount{MIN_LAYER_COUNT, 1, MAX_LAYER_COUNT, CYCLIC_VALUES_STEP};
  PositiveCyclicInteger m_lacunarity{MIN_LACUNARITY, 1, MAX_LACUNARITY, CYCLIC_VALUES_STEP};
  PositiveCyclicInteger m_gainExponent{MIN_LAYER_GAIN_EXPONENT,
                                       1,
                                       MAX_LAYER_GAIN_EXPONENT,
                                       CYCLIC_VALUES_STEP};

  ILattice2dPtr m_lattice2d{nullptr};

  void generate();

  auto generateValueLattice() const -> ILattice2dPtr;
  auto generateGradientLattice() const -> ILattice2dPtr;
  auto generatePeriodicGradientLattice() const -> ILattice2dPtr;
  auto generatePeriodicPerlinLattice() const -> ILattice2dPtr;
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
