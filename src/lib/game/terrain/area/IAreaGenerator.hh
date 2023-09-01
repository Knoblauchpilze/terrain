
#pragma once

#include "Area.hh"
#include "ILatticePoint.hh"
#include "IPoint.hh"
#include <memory>

namespace pge::terrain {

template<int Dimension>
class IAreaGenerator
{
  public:
  virtual ~IAreaGenerator() = default;

  virtual auto areaSurrounding(const IPoint<Dimension> &p) const noexcept -> Area<Dimension> = 0;
};

template<int Dimension>
using IAreaGeneratorPtr = std::unique_ptr<IAreaGenerator<Dimension>>;

using IArea2dGeneratorPtr = IAreaGeneratorPtr<2>;
using IArea3dGeneratorPtr = IAreaGeneratorPtr<3>;

} // namespace pge::terrain
