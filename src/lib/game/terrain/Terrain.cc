
#include "Terrain.hh"
#include "Bilinear.hh"
#include "GradientLattice.hh"
#include "Hasher.hh"
#include "PeriodicGradientLattice.hh"
#include "PeriodicPerlinLattice.hh"
#include "ValueLattice.hh"
#include "WhiteNoise.hh"

namespace pge::terrain {

namespace {
constexpr auto OCEAN_THRESHOLD    = 0.2f;
constexpr auto COAST_THRESHOLD    = 0.5f;
constexpr auto PLAIN_THRESHOLD    = 0.6f;
constexpr auto MOUNTAIN_THRESHOLD = 0.85f;
constexpr auto ICE_THRESHOLD      = 1.0f;

auto heightToTerrainType(const float height) noexcept -> Type
{
  if (height < OCEAN_THRESHOLD)
  {
    return Type::OCEAN;
  }
  else if (height < COAST_THRESHOLD)
  {
    return Type::COAST;
  }
  else if (height < PLAIN_THRESHOLD)
  {
    return Type::PLAIN;
  }
  else if (height < MOUNTAIN_THRESHOLD)
  {
    return Type::MOUNTAIN;
  }
  else
  {
    return Type::ICE;
  }
}

} // namespace

Terrain::Terrain() noexcept
  : utils::CoreObject("2d")
{
  setService("terrain");
  generate();
}

auto Terrain::height(const float x, const float y) const -> float
{
  return m_lattice->at(Point2d(x / m_scale.current(), y / m_scale.current()));
}

auto Terrain::at(const float x, const float y) const -> Type
{
  return heightToTerrainType(height(x, y));
}

void Terrain::load(const std::string &fileName)
{
  warn("Should load " + fileName);
}

void Terrain::save(const std::string &fileName) const
{
  warn("Should save " + fileName);
}

auto Terrain::seed() const noexcept -> Seed
{
  return m_seed;
}

auto Terrain::lattice() const noexcept -> LatticeType
{
  return m_latticeType;
}

auto Terrain::scale() const noexcept -> int
{
  return m_scale.current();
}

auto Terrain::period() const noexcept -> int
{
  return m_period.current();
}

void Terrain::nextLattice()
{
  m_latticeType = nextLatticeType(m_latticeType);
  generate();
}

void Terrain::nextScale()
{
  m_scale.next();
  generate();
}

void Terrain::nextPeriod()
{
  m_period.next();
  generate();
}

void Terrain::nextSeed()
{
  ++m_seed;
  generate();
}

void Terrain::generate()
{
  info("Generating terrain with properties: seed = " + std::to_string(m_seed)
       + " lattice = " + str(m_latticeType) + " period = " + std::to_string(m_period.current())
       + " scale = " + std::to_string(m_period.current()));

  switch (m_latticeType)
  {
    case LatticeType::GRADIENT:
      m_lattice = generateGradientLattice();
      break;
    case LatticeType::PERIODIC_GRADIENT:
      m_lattice = generatePeriodicGradientLattice();
      break;
    case LatticeType::PERIODIC_PERLIN:
      m_lattice = generatePeriodicPerlinLattice();
      break;
    case LatticeType::VALUE:
    default:
      m_lattice = generateValueLattice();
      break;
  }
}

auto Terrain::generateValueLattice() const -> ILatticePtr
{
  auto hasher       = std::make_unique<Hasher2d>(m_seed);
  auto noise        = std::make_unique<WhiteNoise>();
  auto interpolator = std::make_unique<Bilinear>();

  return std::make_unique<ValueLattice>(std::move(hasher),
                                        std::move(noise),
                                        std::move(interpolator));
}

auto Terrain::generateGradientLattice() const -> ILatticePtr
{
  auto hasher       = std::make_unique<Hasher2d>(m_seed);
  auto noise        = std::make_unique<WhiteNoise>(-1.0f, 1.0f);
  auto interpolator = std::make_unique<Bilinear>();

  return std::make_unique<GradientLattice>(std::move(hasher),
                                           std::move(noise),
                                           std::move(interpolator));
}

auto Terrain::generatePeriodicGradientLattice() const -> ILatticePtr
{
  auto interpolator = std::make_unique<Bilinear>();

  return std::make_unique<PeriodicGradientLattice>(m_period.current(),
                                                   m_seed,
                                                   std::move(interpolator));
}

auto Terrain::generatePeriodicPerlinLattice() const -> ILatticePtr
{
  auto interpolator = std::make_unique<Bilinear>();

  return std::make_unique<PeriodicPerlinLattice>(m_period.current(),
                                                 m_seed,
                                                 std::move(interpolator));
}

} // namespace pge::terrain
