
#pragma once

#include "AbstractPeriodicGradientGenerator.hh"
#include "INoise.hh"
#include <vector>

namespace pge::lattice {

class PeriodicPerlinGenerator : public AbstractPeriodicGradientGenerator
{
  public:
  PeriodicPerlinGenerator(const int period, const noise::Seed seed);
  ~PeriodicPerlinGenerator() override = default;

  auto gradientAt(const int id) const noexcept -> utils::Vector2f override;

  private:
  std::vector<utils::Vector2f> m_gradients{};

  void generate(const int period, const noise::Seed seed);
};

} // namespace pge::lattice
