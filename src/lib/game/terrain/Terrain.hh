
#pragma once

#include "Lattice.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <vector>

namespace pge::terrain {

class Terrain : public utils::CoreObject
{
  public:
  Terrain(const noise::Seed seed) noexcept;

  auto at(const float x, const float y) const -> Type;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  private:
  LatticePtr m_grid{};
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
