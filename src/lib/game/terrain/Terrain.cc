
#include "Terrain.hh"
#include "Bilinear2d.hh"
#include "GradientLattice.hh"
#include "Hasher.hh"
#include "PeriodicGradientLattice.hh"
#include "PeriodicPerlinLattice.hh"
#include "ValueLattice.hh"
#include "WhiteNoise.hh"

namespace pge::terrain {

Terrain::Terrain() noexcept
  : utils::CoreObject("2d")
{
  setService("terrain");
  generate();
}

auto Terrain::height(const float x, const float y) const -> float
{
  if (!m_lattice2d)
  {
    return 0.0f;
  }

  float out{0.0f};

  float frequency{1.0f};
  float amplitude{1.0f};
  float magnitude{0.0f};
  for (auto i = 0; i < layersCount(); ++i)
  {
    const auto nx = x * frequency / scale();
    const auto ny = y * frequency / scale();
    magnitude += 1.0f * amplitude;

    Point2d p(nx, ny);

    out += amplitude * m_lattice2d->at(p);

    frequency *= lacunarity();
    amplitude *= gain();
  }

  return out / magnitude;
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
    m_latticeType = previousLatticeType(lattice());
  }
  else
  {
    m_latticeType = nextLatticeType(lattice());
  }
  generate();
}

void Terrain::nextInterpolation(bool prev)
{
  if (prev)
  {
    m_interpolationStrategy = previousInterpolationStrategy(interpolation());
  }
  else
  {
    m_interpolationStrategy = nextInterpolationStrategy(interpolation());
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
  std::string msg("Generating terrain with properties: ");

  msg += "seed = " + std::to_string(seed());
  msg += ", ";
  msg += "lattice = " + str(lattice());
  msg += ", ";
  msg += "interpolation = " + str(interpolation());
  msg += ", ";
  msg += "scale = " + std::to_string(scale());
  msg += ", ";
  msg += "period = " + std::to_string(period());
  msg += ", ";
  msg += "cache = " + std::to_string(cacheSize());
  msg += ", ";

  msg += "layers = " + std::to_string(layersCount());
  msg += ", ";
  msg += "lacunarity = " + std::to_string(lacunarity());
  msg += ", ";
  msg += "gain = " + std::to_string(gain());

  info(msg);

  switch (lattice())
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
  auto hasher       = std::make_unique<Hasher2d>(seed());
  auto noise        = std::make_unique<WhiteNoise>();
  auto interpolator = std::make_unique<Bilinear2d>(interpolation());

  return std::make_unique<ValueLattice>(std::move(hasher),
                                        std::move(noise),
                                        std::move(interpolator),
                                        cacheSize());
}

auto Terrain::generateGradientLattice() const -> ILattice2dPtr
{
  auto hasher       = std::make_unique<Hasher2d>(seed());
  auto noise        = std::make_unique<WhiteNoise>(-1.0f, 1.0f);
  auto interpolator = std::make_unique<Bilinear2d>(interpolation());

  return std::make_unique<GradientLattice>(std::move(hasher),
                                           std::move(noise),
                                           std::move(interpolator),
                                           cacheSize());
}

auto Terrain::generatePeriodicGradientLattice() const -> ILattice2dPtr
{
  auto interpolator = std::make_unique<Bilinear2d>(m_interpolationStrategy);

  return std::make_unique<PeriodicGradientLattice>(period(), seed(), std::move(interpolator));
}

auto Terrain::generatePeriodicPerlinLattice() const -> ILattice2dPtr
{
  auto interpolator = std::make_unique<Bilinear2d>(m_interpolationStrategy);

  return std::make_unique<PeriodicPerlinLattice>(period(), seed(), std::move(interpolator));
}

} // namespace pge::terrain
