
#pragma once

#include "AbstractGradientGenerator.hh"
#include "Seed.hh"
#include <functional>
#include <vector>

namespace pge::terrain {

template<int Dimension>
class AbstractPeriodicGradientGenerator : public AbstractGradientGenerator<Dimension>
{
  public:
  AbstractPeriodicGradientGenerator(const int period, const Seed seed);
  ~AbstractPeriodicGradientGenerator() override = default;

  auto at(const ILatticePoint<Dimension> &latticePoint) const noexcept -> Point3d override;
  virtual auto gradientAt(const int id) const noexcept -> Point3d = 0;

  private:
  static constexpr auto NO_CACHE_SIZE_REQUIRED = 0;
  int m_period;
  int m_modulusMask;
  std::vector<int> m_permutations{};

  void generatePermutationsTable(const Seed seed);
  auto hash(const ILatticePoint<Dimension> &latticePoint) const -> int;
};

} // namespace pge::terrain

#include "AbstractPeriodicGradientGenerator.hxx"
