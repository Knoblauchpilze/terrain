
#pragma once

#include "AbstractGradientGenerator.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class GradientGenerator : public AbstractGradientGenerator<2>
{
  public:
  GradientGenerator(IHasher2dPtr hasher, INoisePtr noise);
  ~GradientGenerator() override = default;

  auto at(const LatticePoint2d &latticePoint) const noexcept -> Point3d override;

  private:
  IHasher2dPtr m_hasher;
  INoisePtr m_noise;
};

} // namespace pge::terrain
