
#pragma once

#include "AbstractCachedGenerator.hh"
#include <memory>

namespace pge::terrain {

template<int PointDimension, int GradientDimension>
class AbstractGradientGenerator
  : public AbstractCachedGenerator<PointDimension, IPoint<GradientDimension>>
{
  public:
  AbstractGradientGenerator(const int cacheSize);
  virtual ~AbstractGradientGenerator() = default;

  protected:
  auto combine(const ILatticePoint<PointDimension> &latticePoint,
               const IPoint<GradientDimension> &latticeValue,
               const IPoint<PointDimension> &point) const noexcept -> float override;
};

template<int PointDimension>
using AbstractGradient3dGeneratorPtr = std::unique_ptr<AbstractGradientGenerator<PointDimension, 3>>;

} // namespace pge::terrain

#include "AbstractGradientGenerator.hxx"
