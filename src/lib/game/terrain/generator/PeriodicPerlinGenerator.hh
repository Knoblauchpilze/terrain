
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include "Seed.hh"
#include <vector>

namespace pge::terrain {

class PeriodicPerlinGenerator : public AbstractPeriodicGradientGenerator<2>
{
  public:
  PeriodicPerlinGenerator(const int period, const Seed seed);
  ~PeriodicPerlinGenerator() override = default;

  auto gradientAt(const int id) const noexcept -> Point3d override;
};

} // namespace pge::terrain
