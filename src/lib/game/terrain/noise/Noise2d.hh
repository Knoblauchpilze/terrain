
#pragma once

#include "Type.hh"
#include <memory>

namespace pge::noise {

class Noise2d
{
  public:
  using Seed = int;

  virtual ~Noise2d() = default;

  auto type() const noexcept -> Type;
  virtual auto at(float x, float y) const noexcept -> float = 0;

  protected:
  Type m_type;

  Noise2d(const Type &type) noexcept;
};

using Noise2dPtr = std::unique_ptr<Noise2d>;

} // namespace pge::noise
