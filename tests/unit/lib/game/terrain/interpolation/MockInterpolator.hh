
#pragma once

#include "IInterpolator.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

class MockInterpolator : public IInterpolator
{
  public:
  MOCK_METHOD(float,
              interpolate,
              (const float, const float, const float, const float, const float, const float),
              (const, override));
};

} // namespace pge::terrain
