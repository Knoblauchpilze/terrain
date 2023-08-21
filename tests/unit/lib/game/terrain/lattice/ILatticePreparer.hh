
#pragma once

#include "ILattice.hh"
#include "MockInterpolator.hh"
#include "MockNoise.hh"
#include <gmock/gmock.h>

namespace pge::lattice {

template<typename Lattice>
class LatticePreparer
{
  protected:
  MockNoise *mockNoise{nullptr};
  MockInterpolator *mockInterpolator{nullptr};

  ILatticePtr lattice{};

  void prepareLattice()
  {
    auto noise        = std::make_unique<::testing::NiceMock<MockNoise>>();
    mockNoise         = noise.get();
    auto interpolator = std::make_unique<::testing::NiceMock<MockInterpolator>>();
    mockInterpolator  = interpolator.get();

    lattice = std::make_unique<Lattice>(std::move(noise), std::move(interpolator));
  }
};

} // namespace pge::lattice
