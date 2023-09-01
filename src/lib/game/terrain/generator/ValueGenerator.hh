
#pragma once

#include "IHasher.hh"
#include "INoise.hh"
#include "IValueGenerator.hh"
#include <memory>

namespace pge::terrain {

class ValueGenerator : public IValueGenerator<float>
{
  public:
  ValueGenerator(IHasherPtr hasher, INoisePtr noise);
  ~ValueGenerator() override = default;

  auto at(const utils::Vector2i &latticePoint) const noexcept -> float override;
  auto generateFor(const utils::Vector2i &latticePoint, const utils::Vector2f &point) const noexcept
    -> float override;

  private:
  IHasherPtr m_hasher;
  INoisePtr m_noise;
};

using ValueGeneratorPtr = std::unique_ptr<ValueGenerator>;

} // namespace pge::terrain
