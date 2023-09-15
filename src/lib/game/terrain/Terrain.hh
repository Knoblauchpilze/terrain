
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

  auto seed() const noexcept -> Seed;
  auto lattice() const noexcept -> LatticeType;
  auto interpolation() const noexcept -> InterpolationStrategy;
  auto scale() const noexcept -> int;
  auto period() const noexcept -> int;
  auto cacheSize() const noexcept -> int;
  void nextLattice(bool prev);
  void nextInterpolation(bool prev);
  void nextScale(bool prev);
  void nextPeriod(bool prev);
  void nextCacheSize(bool prev);
  void nextSeed();

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

  ILattice2dPtr m_lattice2d{nullptr};
  ILattice3dPtr m_lattice3d{nullptr};

  void generate();

  auto generateValueLattice() const -> ILattice2dPtr;
  auto generateGradientLattice() const -> ILattice2dPtr;
  auto generatePeriodicGradientLattice() const -> ILattice2dPtr;
  auto generatePeriodicPerlinLattice() const -> ILattice2dPtr;
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
