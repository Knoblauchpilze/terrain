
#pragma once

#include "MockInterpolator.hh"

namespace pge::terrain {
using namespace ::testing;

template<int Dimension>
inline MockInterpolator<Dimension>::MockInterpolator()
{
  // https://stackoverflow.com/questions/24390218/capture-gmock-string-parameter
  ON_CALL(*this, interpolate(_)).WillByDefault(DoAll(SaveArg<0>(&this->data), Return(0.0f)));
}

} // namespace pge::terrain
