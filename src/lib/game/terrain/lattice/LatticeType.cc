
#include "LatticeType.hh"

namespace pge::terrain {

auto str(const LatticeType type) noexcept -> std::string
{
  switch (type)
  {
    case LatticeType::VALUE:
      return "value";
    case LatticeType::GRADIENT:
      return "gradient";
    case LatticeType::PERIODIC_GRADIENT:
      return "periodic gradient";
    case LatticeType::PERIODIC_PERLIN:
      return "periodic perlin";
    default:

      return "unknown";
  }
}

auto nextLatticeType(const LatticeType type) noexcept -> LatticeType
{
  switch (type)
  {
    case LatticeType::VALUE:
      return LatticeType::GRADIENT;
    case LatticeType::GRADIENT:
      return LatticeType::PERIODIC_GRADIENT;
    case LatticeType::PERIODIC_GRADIENT:
      return LatticeType::PERIODIC_PERLIN;
    default:
      return LatticeType::VALUE;
  }
}

} // namespace pge::terrain
