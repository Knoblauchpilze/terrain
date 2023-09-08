
#pragma once

#include <stdexcept>

namespace pge::terrain::details {

inline constexpr auto pow(const int x, unsigned exp) -> int
{
  if (exp == 0u)
  {
    return x < 0 ? -1 : 1;
  }

  auto out = x;
  while (--exp)
  {
    out *= x;
  }

  return out;
}

} // namespace pge::terrain::details
