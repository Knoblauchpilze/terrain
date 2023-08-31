
#pragma once

#include "ILattice.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <vector>

namespace pge::terrain {

class Terrain : public utils::CoreObject
{
  public:
  Terrain(ILattice2dPtr lattice, const int scale) noexcept;

  auto height(const float x, const float y) const -> float;
  auto at(const float x, const float y) const -> Type;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  private:
  ILattice2dPtr m_lattice{};
  int m_scale;
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
