
#pragma once

#include "IInterpolator.hh"

namespace pge::terrain {

class Bilinear : public IInterpolator
{
  public:
  Bilinear() noexcept  = default;
  ~Bilinear() override = default;

  auto interpolate(const float tl,
                   const float tr,
                   const float br,
                   const float bl,
                   const float px,
                   const float py) const -> float override;
};

} // namespace pge::terrain
