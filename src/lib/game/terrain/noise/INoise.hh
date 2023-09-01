
#pragma once

#include "Seed.hh"
#include <memory>

namespace pge::terrain {

class INoise
{
  public:
  virtual ~INoise() = default;

  virtual void seed(const Seed seed)          = 0;
  virtual auto next() const noexcept -> float = 0;
};

using INoisePtr = std::unique_ptr<INoise>;

} // namespace pge::terrain
