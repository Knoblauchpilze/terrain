
#pragma once

#include "IHasher.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

// http://google.github.io/googletest/gmock_for_dummies.html#writing-the-mock-class
template<int Dimension>
class MockHasher : public IHasher<Dimension>
{
  public:
  MOCK_METHOD(int, hash, (const ILatticePoint<Dimension> &), (override));
};

using MockHasher2d = MockHasher<2>;

} // namespace pge::terrain
