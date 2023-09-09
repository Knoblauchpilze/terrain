
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include "Seed.hh"
#include <vector>

namespace pge::terrain {

template<int Dimension>
class PeriodicPerlinGenerator : public AbstractPeriodicGradientGenerator<Dimension>
{
  public:
  PeriodicPerlinGenerator(const int period, const Seed seed);
  ~PeriodicPerlinGenerator() override = default;

  auto gradientAt(const int id) const noexcept -> Point3d override;

  private:
  static const std::vector<Point3d> DEFAULT_GRADIENTS;
};

using PeriodicPerlinGenerator2d = PeriodicPerlinGenerator<2>;

} // namespace pge::terrain

#include "PeriodicPerlinGenerator.hxx"
