
#pragma once

#include "AbstractGradientGenerator.hh"
#include "INoise.hh"
#include <vector>

namespace pge::lattice {

class PeriodicPerlinGenerator : public AbstractGradientGenerator
{
  public:
  PeriodicPerlinGenerator(const int period, const noise::Seed seed);
  ~PeriodicPerlinGenerator() override = default;

  auto at(const utils::Vector2i &latticePoint) const noexcept -> utils::Vector2f override;

  private:
  int m_period;
  int m_modulusMask;
  std::vector<utils::Vector2f> m_gradients{};
  std::vector<int> m_permutations{};

  void generate(const noise::Seed seed);
  void generatePermutationsTable(const noise::Seed seed);
};

} // namespace pge::lattice
