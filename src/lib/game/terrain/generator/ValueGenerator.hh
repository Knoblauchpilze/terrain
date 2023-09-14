
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
#include <deque>
#include <map>
#include <memory>

namespace pge::terrain {

template<int Dimension>
class ValueGenerator : public IValueGenerator<Dimension, float>
{
  public:
  ValueGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise);
  ~ValueGenerator() override = default;

  auto at(const ILatticePoint<Dimension> &latticePoint) const noexcept -> float override;
  auto generateFor(const ILatticePoint<Dimension> &latticePoint,
                   const IPoint<Dimension> &point) const noexcept -> float override;

  private:
  IHasherPtr<Dimension> m_hasher;
  INoisePtr m_noise;

  static constexpr auto MAX_CACHE_SIZE = 2000;
  using Key                            = std::pair<int, int>;
  mutable std::map<Key, float> m_cache{};
  mutable std::deque<Key> m_keys{};

  auto fromCacheOrGenerate(const ILatticePoint<Dimension> &lp) const -> float;
};

using ValueGenerator2d = ValueGenerator<2>;
using ValueGenerator3d = ValueGenerator<3>;

using ValueGenerator2dPtr = std::unique_ptr<ValueGenerator2d>;
using ValueGenerator3dPtr = std::unique_ptr<ValueGenerator3d>;

} // namespace pge::terrain

#include "ValueGenerator.hxx"
