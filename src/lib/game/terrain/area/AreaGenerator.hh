
#pragma once

#include "IAreaGenerator.hh"

namespace pge::lattice {

class AreaGenerator : public IAreaGenerator
{
  public:
  ~AreaGenerator() override = default;

  auto areaSurrounding(const float x, const float y) const noexcept -> Area override;
};

} // namespace pge::lattice
