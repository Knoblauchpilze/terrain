
#pragma once

#include "PeriodicGradientGenerator.hh"
#include <random>

#include <iostream>

namespace pge::terrain {

template<int Dimension>
inline PeriodicGradientGenerator<Dimension>::PeriodicGradientGenerator(const int period,
                                                                       const Seed seed)
  : AbstractPeriodicGradientGenerator<Dimension>(period, seed)
{
  generate(period, seed);
}

template<int Dimension>
inline auto PeriodicGradientGenerator<Dimension>::gradientAt(const int id) const noexcept -> Point3d
{
  return m_gradients[id];
}

template<int Dimension>
void PeriodicGradientGenerator<Dimension>::generate(const int period, const Seed seed)
{
  std::mt19937 generator(seed);
  std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

  m_gradients.resize(period);
  for (auto &grad : m_gradients)
  {
    std::generate(grad.begin(), grad.end(), [&distribution, &generator]() {
      return distribution(generator);
    });
    grad.normalize();
  }

  auto id = 0;
  std::cout << "seed: " << seed << ", period: " << period << std::endl;
  for (const auto &v : m_gradients)
  {
    std::cout << "gradient[" << id << "]: " << v(0) << "x" << v(1) << "x" << v(2) << std::endl;
    ++id;
  }
}

} // namespace pge::terrain
