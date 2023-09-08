
#pragma once

#include "IGradientGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class AbstractGradientGenerator : public IGradientGenerator<Dimension, 3>
{
  public:
  AbstractGradientGenerator()           = default;
  ~AbstractGradientGenerator() override = default;

  auto generateFor(const ILatticePoint<Dimension> &latticePoint,
                   const IPoint<Dimension> &point) const noexcept -> float override;
};

template<int Dimension>
using AbstractGradientGeneratorPtr = std::unique_ptr<AbstractGradientGenerator<Dimension>>;

} // namespace pge::terrain

#include "AbstractGradientGenerator.hxx"
