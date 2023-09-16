
#include "Terrain.hh"
#include "Bilinear2d.hh"
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
  if (m_lattice2d)
  {
    return m_lattice2d->at(Point2d(x / m_scale.current(), y / m_scale.current()));
  }
  else if (m_lattice3d)
  {
    return m_lattice3d->at(Point3d(x / m_scale.current(), y / m_scale.current(), 0.0f));
  }
  else
  {
    return 0.0f;
  }
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

auto Terrain::lattice() const noexcept -> LatticeType
{
  return m_latticeType;
}

auto Terrain::interpolation() const noexcept -> InterpolationStrategy
{
  return m_interpolationStrategy;
}

auto Terrain::scale() const noexcept -> int
{
  return m_scale.current();
}

auto Terrain::period() const noexcept -> int
{
  return m_period.current();
}

auto Terrain::cacheSize() const noexcept -> int
{
  return m_cacheSize.current();
}

auto Terrain::seed() const noexcept -> Seed
{
  return m_seed;
}

void Terrain::nextLattice(bool prev)
{
  if (prev)
  {
    m_latticeType = previousLatticeType(m_latticeType);
  }
  else
  {
    m_latticeType = nextLatticeType(m_latticeType);
  }
  generate();
}

void Terrain::nextInterpolation(bool prev)
{
  if (prev)
  {
    m_interpolationStrategy = previousInterpolationStrategy(m_interpolationStrategy);
  }
  else
  {
    m_interpolationStrategy = nextInterpolationStrategy(m_interpolationStrategy);
  }
  generate();
}

void Terrain::nextScale(bool prev)
{
  if (prev)
  {
    m_scale.previous();
  }
  else
  {
    m_scale.next();
  }
  generate();
}

void Terrain::nextPeriod(bool prev)
{
  if (prev)
  {
    m_period.previous();
  }
  else
  {
    m_period.next();
  }
  generate();
}

void Terrain::nextCacheSize(bool prev)
{
  if (prev)
  {
    m_cacheSize.previous();
  }
  else
  {
    m_cacheSize.next();
  }
  generate();
}

void Terrain::nextSeed()
{
  ++m_seed;
  generate();
}

auto Terrain::layersCount() const noexcept -> int
{
  return m_layerCount.current();
}

auto Terrain::lacunarity() const noexcept -> int
{
  return m_lacunarity.current();
}

auto Terrain::gain() const noexcept -> float
{
  const auto den = std::pow(TERRAIN_POWER_BASE, m_gainExponent.current());
  return 1.0f / den;
}

void Terrain::nextLayersCount(bool prev) noexcept
{
  if (prev)
  {
    m_layerCount.previous();
  }
  else
  {
    m_layerCount.next();
  }
}

void Terrain::nextLacunarity(bool prev) noexcept
{
  if (prev)
  {
    m_lacunarity.previous();
  }
  else
  {
    m_lacunarity.next();
  }
}

void Terrain::nextGain(bool prev) noexcept
{
  if (prev)
  {
    m_gainExponent.previous();
  }
  else
  {
    m_gainExponent.next();
  }
}

void Terrain::generate()
{
  info("Generating terrain with properties: seed = " + std::to_string(m_seed)
       + " lattice = " + str(m_latticeType) + " interpolation = " + str(m_interpolationStrategy)
       + " period = " + std::to_string(m_period.current()) + " scale = "
       + std::to_string(m_period.current()) + " cache = " + std::to_string(m_cacheSize.current()));

  switch (m_latticeType)
  {
    case LatticeType::GRADIENT:
      m_lattice2d = generateGradientLattice();
      break;
    case LatticeType::PERIODIC_GRADIENT:
      m_lattice2d = generatePeriodicGradientLattice();
      break;
    case LatticeType::PERIODIC_PERLIN:
      m_lattice2d = generatePeriodicPerlinLattice();
      break;
    case LatticeType::VALUE:
    default:
      m_lattice2d = generateValueLattice();
      break;
  }
}

auto Terrain::generateValueLattice() const -> ILattice2dPtr
{
  auto hasher       = std::make_unique<Hasher2d>(m_seed);
  auto noise        = std::make_unique<WhiteNoise>();
  auto interpolator = std::make_unique<Bilinear2d>(m_interpolationStrategy);

  return std::make_unique<ValueLattice>(std::move(hasher),
                                        std::move(noise),
                                        std::move(interpolator),
                                        m_cacheSize.current());
}

auto Terrain::generateGradientLattice() const -> ILattice2dPtr
{
  auto hasher       = std::make_unique<Hasher2d>(m_seed);
  auto noise        = std::make_unique<WhiteNoise>(-1.0f, 1.0f);
  auto interpolator = std::make_unique<Bilinear2d>(m_interpolationStrategy);

  return std::make_unique<GradientLattice>(std::move(hasher),
                                           std::move(noise),
                                           std::move(interpolator),
                                           m_cacheSize.current());
}

auto Terrain::generatePeriodicGradientLattice() const -> ILattice2dPtr
{
  auto interpolator = std::make_unique<Bilinear2d>(m_interpolationStrategy);

  return std::make_unique<PeriodicGradientLattice>(m_period.current(),
                                                   m_seed,
                                                   std::move(interpolator));
}

auto Terrain::generatePeriodicPerlinLattice() const -> ILattice2dPtr
{
  auto interpolator = std::make_unique<Bilinear2d>(m_interpolationStrategy);

  return std::make_unique<PeriodicPerlinLattice>(m_period.current(),
                                                 m_seed,
                                                 std::move(interpolator));
}

} // namespace pge::terrain
