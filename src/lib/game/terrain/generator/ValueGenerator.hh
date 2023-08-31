
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class ValueGenerator : public IValueGenerator<Dimension, 1>
{
  public:
  ValueGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise);
  ~ValueGenerator() override = default;

  using LatticePoint = ILatticePoint<Dimension>;
  using Point        = IPoint<Dimension>;

  auto at(const LatticePoint &latticePoint) const noexcept -> Point1d override;
  auto generateFor(const LatticePoint &latticePoint, const Point &point) const noexcept
    -> float override;

  private:
  IHasherPtr<Dimension> m_hasher;
  INoisePtr m_noise;
};

template<int Dimension>
using ValueGeneratorPtr = std::unique_ptr<ValueGenerator<Dimension>>;

using ValueGenerator2dPtr = ValueGeneratorPtr<2>;

} // namespace pge::terrain

#include "ValueGenerator.hxx"
