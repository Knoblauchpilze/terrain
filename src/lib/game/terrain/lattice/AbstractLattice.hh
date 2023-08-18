
#pragma once

#include "IAreaGenerator.hh"
#include "IInterpolator.hh"
#include "ILattice.hh"
#include "IValueGenerator.hh"

namespace pge::lattice {

class AbstractLattice : public ILattice
{
  public:
  ~AbstractLattice() override = default;

  auto at(const float x, const float y) -> float override;

  protected:
  AbstractLattice(IValueGeneratorPtr valueGenerator,
                  interpolation::IInterpolatorPtr interpolator) noexcept;

  private:
  IAreaGeneratorPtr m_areaGenerator;
  IValueGeneratorPtr m_valueGenerator;
  interpolation::IInterpolatorPtr m_interpolator;
};

} // namespace pge::lattice
