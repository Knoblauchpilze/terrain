
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
  Terrain(lattice::ILatticePtr lattice) noexcept;

  auto height(const float x, const float y) const -> float;
  auto at(const float x, const float y) const -> Type;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  private:
  float m_scale{5.0f};
  lattice::ILatticePtr m_lattice{};
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
