
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

class ValueGenerator : public IValueGenerator3d<float>
{
  public:
  ValueGenerator(IHasher3dPtr hasher, INoisePtr noise);
  ~ValueGenerator() override = default;

  auto at(const LatticePoint3d &latticePoint) const noexcept -> float override;
  auto generateFor(const LatticePoint3d &latticePoint, const Point3d &point) const noexcept
    -> float override;

  private:
  IHasher3dPtr m_hasher;
  INoisePtr m_noise;
};

using ValueGeneratorPtr = std::unique_ptr<ValueGenerator>;

} // namespace pge::terrain
