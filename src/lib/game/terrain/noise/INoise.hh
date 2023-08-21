
#pragma once

#include <memory>

namespace pge::noise {

using Seed = int;

class INoise
{
  public:
  virtual ~INoise() = default;

  virtual void seed(const int x, const int y)                       = 0;
  virtual auto at(const int x, const int y) const noexcept -> float = 0;
};

using INoisePtr = std::unique_ptr<INoise>;

} // namespace pge::noise
