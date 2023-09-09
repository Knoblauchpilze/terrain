
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
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
};

using ValueGenerator2d = ValueGenerator<2>;
using ValueGenerator3d = ValueGenerator<3>;

using ValueGenerator2dPtr = std::unique_ptr<ValueGenerator2d>;
using ValueGenerator3dPtr = std::unique_ptr<ValueGenerator3d>;

} // namespace pge::terrain

#include "ValueGenerator.hxx"
