
#pragma once

#include "AbstractGradientGenerator.hh"
#include "IHasher.hh"
#include "INoise.hh"

namespace pge::lattice {

class GradientGenerator : public AbstractGradientGenerator
{
  public:
  GradientGenerator(IHasherPtr hasher, noise::INoisePtr noise);
  ~GradientGenerator() override = default;

  auto at(const utils::Vector2i &latticePoint) const noexcept -> utils::Vector2f override;

  private:
  IHasherPtr m_hasher;
  noise::INoisePtr m_noise;

  public:
  mutable int64_t modulusDuration{0};
  mutable int64_t permDuration{0};
  mutable int64_t gradDuration{0};
};

} // namespace pge::lattice
