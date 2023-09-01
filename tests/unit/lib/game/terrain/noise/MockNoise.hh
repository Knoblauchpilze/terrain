
#pragma once

#include "INoise.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

class MockNoise : public INoise
{
  public:
  MOCK_METHOD(void, seed, (const Seed), (override));
  MOCK_METHOD(float, next, (), (const, noexcept, override));
};

} // namespace pge::terrain
