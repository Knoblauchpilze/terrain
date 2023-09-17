
#pragma once

#include "AbstractCachedGenerator.hh"
#include "IHasher.hh"
#include "INoise.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class ValueGenerator : public AbstractCachedGenerator<Dimension, float>
{
  public:
  ValueGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise, const int cacheSize);
  ~ValueGenerator() override = default;

  auto at(const ILatticePoint<Dimension> &latticePoint) const noexcept -> float override;

  protected:
  auto combine(const ILatticePoint<Dimension> &latticePoint,
               const float &latticeValue,
               const IPoint<Dimension> &point) const noexcept -> float override;

  private:
  IHasherPtr<Dimension> m_hasher;
  INoisePtr m_noise;
};

using ValueGenerator2d = ValueGenerator<2>;
using ValueGenerator3d = ValueGenerator<3>;

using ValueGenerator2dPtr = std::unique_ptr<ValueGenerator2d>;
using ValueGenerator3dPtr = std::unique_ptr<ValueGenerator3d>;

} // namespace pge::terrain

#include "ValueGenerator.hxx"
