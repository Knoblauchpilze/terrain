
#pragma once

#include "IValueGenerator.hh"
#include "MockHasher.hh"
#include "MockNoise.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

template<typename Generator, int LatticeSpaceDimension, int LatticeValueDimension>
class GeneratorPreparer
{
  protected:
  MockHasher<LatticeSpaceDimension> *mockHasher{nullptr};
  MockNoise *mockNoise{nullptr};

  IValueGeneratorPtr<LatticeSpaceDimension, LatticeValueDimension> generator{};

  void prepareGenerator()
  {
    auto hasher = std::make_unique<::testing::NiceMock<MockHasher<LatticeSpaceDimension>>>();
    mockHasher  = hasher.get();

    auto noise = std::make_unique<::testing::NiceMock<MockNoise>>();
    mockNoise  = noise.get();

    generator = std::make_unique<Generator>(std::move(hasher), std::move(noise));
  }
};

} // namespace pge::terrain