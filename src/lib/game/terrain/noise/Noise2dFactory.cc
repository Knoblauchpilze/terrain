
#include "Noise2dFactory.hh"
#include "WhiteNoise.hh"
#include <chrono>

namespace pge::noise {
namespace {
auto prepareSeed(const std::optional<Noise2d::Seed> &seed) -> Noise2d::Seed
{
  // // https://cplusplus.com/reference/random/mersenne_twister_engine/mersenne_twister_engine/
  auto out = std::chrono::system_clock::now().time_since_epoch().count();
  if (seed)
  {
    out = *seed;
  }

  return out;
}
} // namespace

Noise2dFactory::Noise2dFactory(const Type &type) noexcept
  : utils::CoreObject("2d")
  , m_type(type)
{
  setService("noise");
}

auto Noise2dFactory::createNoise2d(const std::optional<Noise2d::Seed> &maybeSeed) -> Noise2dPtr
{
  auto seed = prepareSeed(maybeSeed);

  switch (m_type)
  {
    case Type::White:
      return std::make_unique<WhiteNoise>(seed);
    default:
      error("failed to generate noise", "unknown noise " + str(m_type));
      // Useless but needed as the error does not have a throw qualifier.
      return nullptr;
  }
}

} // namespace pge::noise
