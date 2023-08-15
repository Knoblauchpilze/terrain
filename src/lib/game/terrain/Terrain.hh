
#pragma once

#include "Noise2d.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <vector>

namespace pge::terrain {

class Terrain : public utils::CoreObject
{
  public:
  Terrain(noise::Noise2dPtr noise) noexcept;

  auto at(const int x, const int y) const -> Type;

  void load(const std::string &fileName);
  void save(const std::string &fileName) const;

  private:
  noise::Noise2dPtr m_noise{};
};

using TerrainPtr = std::unique_ptr<Terrain>;

} // namespace pge::terrain
