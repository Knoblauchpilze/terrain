
#pragma once

#include "ILatticePoint.hh"
#include "IPoint.hh"
#include <string>

namespace pge::terrain {

template<int Dimension>
auto nameOf(const ILatticePoint<Dimension> &point) -> std::string;

template<int Dimension>
auto nameOf(const IPoint<Dimension> &point) -> std::string;

} // namespace pge::terrain

#include "PointName.hxx"
