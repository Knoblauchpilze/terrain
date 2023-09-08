
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include "Seed.hh"
#include <vector>

namespace pge::terrain {

class PeriodicGradientGenerator : public AbstractPeriodicGradientGenerator<2>
{
  public:
  PeriodicGradientGenerator(const int period, const Seed seed);
  ~PeriodicGradientGenerator() override = default;

  auto gradientAt(const int id) const noexcept -> Point3d override;

  private:
  std::vector<Point3d> m_gradients{};

  void generate(const int period, const Seed seed);
};

} // namespace pge::terrain
