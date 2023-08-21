
#pragma once

#include "IValueGenerator.hh"
#include "MockNoise.hh"
#include <gmock/gmock.h>

namespace pge::lattice {

template<typename Generator>
class GeneratorPreparer
{
  protected:
  MockNoise *mockNoise{nullptr};

  IValueGeneratorPtr generator{};

  void prepareGenerator()
  {
    auto noise = std::make_unique<::testing::NiceMock<MockNoise>>();
    mockNoise  = noise.get();

    generator = std::make_unique<Generator>(std::move(noise));
  }
};

} // namespace pge::lattice
