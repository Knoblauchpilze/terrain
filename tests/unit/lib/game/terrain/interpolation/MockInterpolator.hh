
#pragma once

#include "IInterpolator.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

class MockInterpolator : public IInterpolator<2>
{
  public:
  MockInterpolator();

  MOCK_METHOD(float, interpolate, (const InterpolationData<2> &), (const, override));

  InterpolationData<2> data{};
};

} // namespace pge::terrain
