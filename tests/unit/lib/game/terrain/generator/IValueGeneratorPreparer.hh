
#pragma once

#include "IValueGenerator.hh"
#include "MockHasher.hh"
#include "MockNoise.hh"
#include <gmock/gmock.h>

namespace pge::terrain {

template<typename Generator, int Dimension, typename LatticeValueType>
class GeneratorPreparer
{
  protected:
  MockHasher<Dimension> *mockHasher{nullptr};
  MockNoise *mockNoise{nullptr};

  std::unique_ptr<Generator> generator{};

  void prepareGenerator(const int cacheSize)
  {
    auto hasher = std::make_unique<::testing::NiceMock<MockHasher<Dimension>>>();
    mockHasher  = hasher.get();

    auto noise = std::make_unique<::testing::NiceMock<MockNoise>>();
    mockNoise  = noise.get();

    generator = std::make_unique<Generator>(std::move(hasher), std::move(noise), cacheSize);
  }
};

} // namespace pge::terrain
