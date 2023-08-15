
#pragma once

#include <memory>
#include <random>

namespace pge::noise {

using Seed = int;

class INoise
{
  public:
  virtual ~INoise() = default;

  virtual void seed(const Seed seed)          = 0;
  virtual auto next() const noexcept -> float = 0;
};

using INoisePtr = std::unique_ptr<INoise>;

} // namespace pge::noise
