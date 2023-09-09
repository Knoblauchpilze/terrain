
#pragma once

#include "PointName.hh"
#include "SanitizeTestName.hh"

namespace pge::terrain {

template<int Dimension>
inline auto nameOf(const ILatticePoint<Dimension> &point) -> std::string
{
  std::string out;

  for (auto i = 0; i < Dimension; ++i)
  {
    if (!out.empty())
    {
      out += "x";
    }
    out += std::to_string(point(i));
  }

  return sanitizeTestName(out);
}

template<int Dimension>
inline auto nameOf(const IPoint<Dimension> &point) -> std::string
{
  std::string out;

  for (auto i = 0; i < Dimension; ++i)
  {
    if (!out.empty())
    {
      out += "x";
    }
    out += std::to_string(point(i));
  }

  return sanitizeTestName(out);
}

} // namespace pge::terrain
