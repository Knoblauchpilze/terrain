
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
  void seed(const int x, const int y);
  virtual auto next() const noexcept -> float = 0;

  protected:
  Type m_type;
  Seed m_seed;

  Noise2d(const Type &type, const Seed seed) noexcept;
  virtual void seed(const Seed seed) = 0;
};

using Noise2dPtr = std::unique_ptr<Noise2d>;

} // namespace pge::noise
