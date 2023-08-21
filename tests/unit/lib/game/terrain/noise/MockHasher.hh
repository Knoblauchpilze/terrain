
#pragma once

#include "IHasher.hh"
#include <gmock/gmock.h>

namespace pge::noise {

// // http://google.github.io/googletest/gmock_for_dummies.html#writing-the-mock-class
class MockHasher : public IHasher
{
  public:
  MOCK_METHOD(float, hash, (const int, const int), (override));
};

} // namespace pge::noise
