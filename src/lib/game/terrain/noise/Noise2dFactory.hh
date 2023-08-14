
#pragma once

#include "Noise2d.hh"
#include <core_utils/CoreObject.hh>
#include <memory>
#include <optional>

namespace pge::noise {

class Noise2dFactory : public utils::CoreObject
{
  public:
  Noise2dFactory(const Type &type) noexcept;

  auto createNoise2d(const std::optional<Noise2d::Seed> &maybeSeed) -> Noise2dPtr;

  private:
  Type m_type;
};

} // namespace pge::noise
