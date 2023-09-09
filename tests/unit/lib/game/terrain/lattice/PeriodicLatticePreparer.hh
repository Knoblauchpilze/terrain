
#pragma once

#include "ILattice.hh"
#include "MockInterpolator.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

template<typename Lattice, int Dimension>
class PeriodicLatticePreparer
{
  protected:
  MockInterpolator<Dimension> *mockInterpolator{nullptr};

  std::unique_ptr<Lattice> lattice{};

  void prepareLattice(const int period, const Seed seed)
  {
    auto interpolator = std::make_unique<::testing::NiceMock<MockInterpolator<Dimension>>>();
    mockInterpolator  = interpolator.get();

    lattice = std::make_unique<Lattice>(period, seed, std::move(interpolator));
  }
};

} // namespace pge::terrain
