
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include "Seed.hh"
#include <vector>

namespace pge::terrain {

class PeriodicPerlinGenerator : public AbstractPeriodicGradientGenerator
{
  public:
  PeriodicPerlinGenerator(const int period, const Seed seed);
  ~PeriodicPerlinGenerator() override = default;

  auto gradientAt(const int id) const noexcept -> Point2d override;

  private:
  std::vector<Point2d> m_gradients{};

  void generate(const int period, const Seed seed);
};

} // namespace pge::terrain
