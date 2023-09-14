
#pragma once

#include "IGradientGenerator.hh"
#include <deque>
#include <map>
#include <memory>

namespace pge::terrain {

template<int Dimension>
class AbstractGradientGenerator : public IGradientGenerator<Dimension, 3>
{
  public:
  AbstractGradientGenerator()           = default;
  ~AbstractGradientGenerator() override = default;

  auto generateFor(const ILatticePoint<Dimension> &latticePoint,
                   const IPoint<Dimension> &point) const noexcept -> float override;

  private:
  static constexpr auto MAX_CACHE_SIZE = 2000;
  /// https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys
  using Key = std::pair<int, int>;
  mutable std::map<Key, Point3d> m_cache{};
  mutable std::deque<Key> m_keys{};

  auto fromCacheOrGenerate(const ILatticePoint<Dimension> &lp) const -> Point3d;
};

template<int Dimension>
using AbstractGradientGeneratorPtr = std::unique_ptr<AbstractGradientGenerator<Dimension>>;

} // namespace pge::terrain

#include "AbstractGradientGenerator.hxx"
