
#pragma once

#include "AbstractGradientGenerator.hh"
#include "Seed.hh"
#include <functional>
#include <vector>

namespace pge::terrain {

class AbstractPeriodicGradientGenerator : public AbstractGradientGenerator
{
  public:
  AbstractPeriodicGradientGenerator(const int period, const Seed seed);
  ~AbstractPeriodicGradientGenerator() override = default;

  auto at(const LatticePoint2d &latticePoint) const noexcept -> Point2d override;
  virtual auto gradientAt(const int id) const noexcept -> Point2d = 0;

  private:
  int m_period;
  int m_modulusMask;
  std::vector<int> m_permutations{};

  void generatePermutationsTable(const Seed seed);
};

} // namespace pge::terrain
