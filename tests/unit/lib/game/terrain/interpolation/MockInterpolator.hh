
#pragma once

#include "IInterpolator.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

class MockInterpolator : public IInterpolator2d
{
  public:
  MockInterpolator();

  MOCK_METHOD(float, interpolate, (const InterpolationData2d &), (const, override));

  InterpolationData2d data{};
};

} // namespace pge::terrain
