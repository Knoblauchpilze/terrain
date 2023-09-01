
#pragma once

#include "AbstractGradientGenerator.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::terrain {

class GradientGenerator : public AbstractGradientGenerator
{
  public:
  GradientGenerator(IHasherPtr hasher, INoisePtr noise);
  ~GradientGenerator() override = default;

  auto at(const utils::Vector2i &latticePoint) const noexcept -> utils::Vector2f override;

  private:
  IHasherPtr m_hasher;
  INoisePtr m_noise;
};

} // namespace pge::terrain
