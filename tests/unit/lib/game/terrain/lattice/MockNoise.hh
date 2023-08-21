
#pragma once

#include "INoise.hh"
#include <gmock/gmock.h>

namespace pge::lattice {

class MockNoise : public noise::INoise
{
  public:
  MOCK_METHOD(void, seed, (const int, const int), (override));
  MOCK_METHOD(float, at, (const int, const int), (const, noexcept, override));
};

} // namespace pge::lattice
