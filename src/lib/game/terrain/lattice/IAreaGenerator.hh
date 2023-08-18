
#pragma once

#include <maths_utils/Vector2.hh>
#include <memory>

namespace pge::lattice {

struct Area
{
  utils::Vector2f topLeft;
  utils::Vector2f topRight;
  utils::Vector2f bottomRight;
  utils::Vector2f bottomLeft;
};

class IAreaGenerator
{
  public:
  virtual ~IAreaGenerator() = default;

  virtual auto areaSurrounding(const float x, const float y) const noexcept -> Area = 0;
};

using IAreaGeneratorPtr = std::unique_ptr<IAreaGenerator>;

} // namespace pge::lattice
