
#pragma once

#include "IPoint.hh"
#include <string>

namespace pge::terrain {

template<int Dimension>
auto nameOf(const IPoint<Dimension> &point) -> std::string;

}

#include "PointName.hxx"
