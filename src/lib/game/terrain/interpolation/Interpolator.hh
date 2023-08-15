
#pragma once

#include "Algorithm.hh"
#include <vector>

namespace pge::interpolation {

class Interpolator
{
  public:
  Interpolator(const Algorithm &algorithm) noexcept;
  ~Interpolator() = default;

  auto interpolate(const float tl,
                   const float tr,
                   const float br,
                   const float bl,
                   const float px,
                   const float py) const -> float;

  private:
  Algorithm m_algorithm;
};

} // namespace pge::interpolation
