
#pragma once

#include "AbstractGradientGenerator.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

template<int Dimension>
class GradientGenerator : public AbstractGradientGenerator<Dimension>
{
  public:
  GradientGenerator(IHasherPtr<Dimension> hasher, INoisePtr noise);
  ~GradientGenerator() override = default;

  auto at(const ILatticePoint<Dimension> &latticePoint) const noexcept -> Point3d override;

  private:
  IHasherPtr<Dimension> m_hasher;
  INoisePtr m_noise;
};

using GradientGenerator2d = GradientGenerator<2>;

} // namespace pge::terrain

#include "GradientGenerator.hxx"
