
#pragma once

#include "IValueGenerator.hh"
#include "MockHasher.hh"
#include "MockNoise.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

template<typename Generator, typename LatticeValueType>
class GeneratorPreparer
{
  protected:
  MockHasher2d *mockHasher{nullptr};
  MockNoise *mockNoise{nullptr};

  std::unique_ptr<Generator> generator{};

  void prepareGenerator()
  {
    auto hasher = std::make_unique<::testing::NiceMock<MockHasher2d>>();
    mockHasher  = hasher.get();

    auto noise = std::make_unique<::testing::NiceMock<MockNoise>>();
    mockNoise  = noise.get();

    generator = std::make_unique<Generator>(std::move(hasher), std::move(noise));
  }
};

} // namespace pge::terrain
