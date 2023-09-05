
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

class ValueGenerator : public IValueGenerator<2, float>
{
  public:
  ValueGenerator(IHasher2dPtr hasher, INoisePtr noise);
  ~ValueGenerator() override = default;

  auto at(const LatticePoint2d &latticePoint) const noexcept -> float override;
  auto generateFor(const LatticePoint2d &latticePoint, const Point2d &point) const noexcept
    -> float override;

  private:
  IHasher2dPtr m_hasher;
  INoisePtr m_noise;
};

using ValueGeneratorPtr = std::unique_ptr<ValueGenerator>;

} // namespace pge::terrain
