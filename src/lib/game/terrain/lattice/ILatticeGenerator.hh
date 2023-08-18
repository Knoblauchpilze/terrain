
#pragma once

#include <maths_utils/Vector2.hh>
#include <memory>

namespace pge::lattice {

struct LatticeArea
{
  utils::Vector2f topLeft;
  utils::Vector2f topRight;
  utils::Vector2f bottomRight;
  utils::Vector2f bottomLeft;
};

class ILatticeGenerator
{
  public:
  virtual ~ILatticeGenerator() = default;

  virtual auto areaSurrounding(const float x, const float y) const noexcept -> LatticeArea = 0;
};

using ILatticeGeneratorPtr = std::unique_ptr<ILatticeGenerator>;

} // namespace pge::lattice
