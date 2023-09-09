
#pragma once

#include "IInterpolator.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

template<int Dimension>
class MockInterpolator : public IInterpolator<Dimension>
{
  public:
  MockInterpolator();

  MOCK_METHOD(float, interpolate, (const InterpolationData<Dimension> &), (const, override));

  InterpolationData<Dimension> data{};
};

} // namespace pge::terrain

#include "MockInterpolator.hxx"
