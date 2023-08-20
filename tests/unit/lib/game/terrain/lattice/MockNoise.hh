
#pragma once

#include "INoise.hh"
#include <gmock/gmock.h>

namespace pge::lattice {

class MockNoise : public noise::INoise
{
  public:
  MOCK_METHOD(void, seed, (const noise::Seed), (override));
  MOCK_METHOD(float, next, (), (const, noexcept, override));
  MOCK_METHOD(float, nextRange, (const float, const float), (const, noexcept, override));
};

} // namespace pge::lattice
