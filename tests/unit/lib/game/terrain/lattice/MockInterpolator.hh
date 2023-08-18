
#pragma once

#include "IInterpolator.hh"
#include <gmock/gmock.h>

namespace pge::lattice {

class MockInterpolator : public interpolation::IInterpolator
{
  public:
  MOCK_METHOD(float,
              interpolate,
              (const float, const float, const float, const float, const float, const float),
              (const, override));
};

} // namespace pge::lattice
