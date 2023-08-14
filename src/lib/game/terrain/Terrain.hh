
#pragma once

#include "Noise2d.hh"
#include "Type.hh"
#include <core_utils/CoreObject.hh>
#include <vector>

namespace pge::terrain {

class Terrain : public utils::CoreObject
{
  public:
  Terrain(int width, int height, Noise2dPtr noise) noexcept;

  auto w() const noexcept -> int;
  auto h() const noexcept -> int;

  auto at(const int x, const int y) const -> Type;

  void load(const std::string &fileName);

  void save(const std::string &fileName) const;

  private:
  int m_width;
  int m_height;

  Noise2dPtr m_noise{};

  std::vector<Type> m_land{};
};

} // namespace pge::terrain
