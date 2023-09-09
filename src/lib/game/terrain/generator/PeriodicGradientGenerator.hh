
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include "Seed.hh"
#include <vector>

namespace pge::terrain {

template<int Dimension>
class PeriodicGradientGenerator : public AbstractPeriodicGradientGenerator<Dimension>
{
  public:
  PeriodicGradientGenerator(const int period, const Seed seed);
  ~PeriodicGradientGenerator() override = default;

  auto gradientAt(const int id) const noexcept -> Point3d override;

  private:
  std::vector<Point3d> m_gradients{};

  void generate(const int period, const Seed seed);
};

using PeriodicGradientGenerator2d = PeriodicGradientGenerator<2>;
using PeriodicGradientGenerator3d = PeriodicGradientGenerator<3>;

} // namespace pge::terrain

#include "PeriodicGradientGenerator.hxx"
