
#pragma once

#include "AbstractGradientGenerator.hh"
#include "IHasher.hh"
#include "INoise.hh"
#include <deque>
#include <map>

namespace pge::terrain {

template<int Dimension>
class GradientGenerator : public AbstractGradientGenerator<Dimension>
{
  public:
  GradientGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise, const int cacheSize);
  ~GradientGenerator() override = default;

  auto at(const ILatticePoint<Dimension> &latticePoint) const noexcept -> Point3d override;

  private:
  IHasherPtr<Dimension> m_hasher;
  INoisePtr m_noise;

  using Key = std::pair<int, int>;
  unsigned m_cacheSize{256};
  mutable std::map<Key, Point3d> m_cache{};
  mutable std::deque<Key> m_keys{};

  auto generateAndRegisterInCache(const ILatticePoint<Dimension> &lp) const -> Point3d;
};

using GradientGenerator2d = GradientGenerator<2>;
using GradientGenerator3d = GradientGenerator<3>;

} // namespace pge::terrain

#include "GradientGenerator.hxx"
