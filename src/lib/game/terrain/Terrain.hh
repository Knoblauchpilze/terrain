
#pragma once

#include "ILattice.hh"
#include "Performance.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <vector>

namespace pge::terrain {

class Terrain : public utils::CoreObject
{
  public:
  Terrain(lattice::ILatticePtr lattice, const int scale) noexcept;

  auto height(const float x, const float y) const -> float;
  auto at(const float x, const float y) const -> Type;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  auto timers() const noexcept -> Performance;
  void increaseTimers() noexcept;

  private:
  lattice::ILatticePtr m_lattice{};
  int m_scale;

  mutable Performance m_timers{};
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
