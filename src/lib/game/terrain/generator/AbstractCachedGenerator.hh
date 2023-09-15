
#pragma once

#include "IValueGenerator.hh"
#include <deque>
#include <map>
#include <memory>

namespace pge::terrain {

template<int Dimension, typename ValueType>
class AbstractCachedGenerator : public IValueGenerator<Dimension, ValueType>
{
  public:
  AbstractCachedGenerator(const int cacheSize);
  ~AbstractCachedGenerator() override = default;

  auto generateFor(const ILatticePoint<Dimension> &latticePoint,
                   const IPoint<Dimension> &point) const noexcept -> float override;

  protected:
  virtual auto combine(const ValueType &latticeValue, const IPoint<Dimension> &point) const noexcept
    -> float
    = 0;

  private:
  /// https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys
  using Key = std::pair<int, int>;
  unsigned m_cacheSize{256};
  mutable std::map<Key, ValueType> m_cache{};
  mutable std::deque<Key> m_keys{};

  auto fromCacheOrGenerate(const ILatticePoint<Dimension> &lp, const IPoint<Dimension> &p) const
    -> float;
};

} // namespace pge::terrain

#include "AbstractCachedGenerator.hxx"
