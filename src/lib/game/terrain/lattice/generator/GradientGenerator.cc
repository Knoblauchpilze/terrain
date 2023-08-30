
#include "GradientGenerator.hh"

#include <chrono>

namespace pge::lattice {

GradientGenerator::GradientGenerator(IHasherPtr hasher, noise::INoisePtr noise)
  : m_hasher(std::move(hasher))
  , m_noise(std::move(noise))
{}

auto GradientGenerator::at(const utils::Vector2i &latticePoint) const noexcept -> utils::Vector2f
{
  this->modulusDuration = 0;
  this->permDuration    = 0;
  this->gradDuration    = 0;
  const auto st         = std::chrono::steady_clock::now();

  utils::Vector2f grad;
  m_noise->seed(m_hasher->hash(latticePoint.x(), latticePoint.y()));

  const auto p1 = std::chrono::steady_clock::now();

  grad.x() = m_noise->next();
  grad.y() = m_noise->next();

  const auto p2 = std::chrono::steady_clock::now();

  grad.normalize();

  const auto p3         = std::chrono::steady_clock::now();
  this->modulusDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(p1 - st).count();
  this->permDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(p2 - p1).count();
  this->gradDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(p3 - p2).count();

  return grad;
}

} // namespace pge::lattice
