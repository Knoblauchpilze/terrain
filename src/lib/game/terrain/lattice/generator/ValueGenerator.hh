
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
#include <memory>

namespace pge::lattice {

class ValueGenerator : public IValueGenerator<float>
{
  public:
  ValueGenerator(IHasherPtr hasher, noise::INoisePtr noise);
  ~ValueGenerator() override = default;

  auto at(const utils::Vector2i &latticePoint) const noexcept -> float override;
  auto generateFor(const utils::Vector2i &latticePoint, const utils::Vector2f &point) const noexcept
    -> float override;

  private:
  IHasherPtr m_hasher;
  noise::INoisePtr m_noise;
};

using ValueGeneratorPtr = std::unique_ptr<ValueGenerator>;

} // namespace pge::lattice