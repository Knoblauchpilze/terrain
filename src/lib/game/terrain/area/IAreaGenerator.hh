
#pragma once

#include <maths_utils/Vector2.hh>
#include <memory>

namespace pge::terrain {

struct Area
{
  utils::Vector2i topLeft;
  utils::Vector2i topRight;
  utils::Vector2i bottomRight;
  utils::Vector2i bottomLeft;
};

class IAreaGenerator
{
  public:
  virtual ~IAreaGenerator() = default;

  virtual auto areaSurrounding(const float x, const float y) const noexcept -> Area = 0;
};

using IAreaGeneratorPtr = std::unique_ptr<IAreaGenerator>;

} // namespace pge::terrain
