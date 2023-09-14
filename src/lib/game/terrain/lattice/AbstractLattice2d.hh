
#pragma once

#include "AbstractLattice.hh"
#include <unordered_map>

namespace pge::terrain {

template<typename ValueType>
class AbstractLattice2d : public AbstractLattice<2, ValueType>
{
  public:
  ~AbstractLattice2d() override = default;

  auto at(const Point2d &p) -> float override;

  protected:
  AbstractLattice2d(IValueGenerator2dPtr<ValueType> valueGenerator,
                    IInterpolator2dPtr interpolator,
                    std::optional<NormalizationFunc> normalization) noexcept;

  private:
  static constexpr auto MAX_CACHE_SIZE = 200;
  std::unordered_map<std::string, ValueType> m_cache{};

  auto fromCacheOrGenerate(const LatticePoint2d &lp, const Point2d &p) const -> float;
};

} // namespace pge::terrain

#include "AbstractLattice2d.hxx"
