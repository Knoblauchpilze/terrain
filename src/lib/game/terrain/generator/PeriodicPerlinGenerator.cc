
#include "PeriodicPerlinGenerator.hh"
#include <iostream>
#include <random>

namespace pge::terrain {

PeriodicPerlinGenerator::PeriodicPerlinGenerator(const int period, const Seed seed)
  : AbstractPeriodicGradientGenerator(period, seed)
{
  generate(period, seed);
}

auto PeriodicPerlinGenerator::gradientAt(const int id) const noexcept -> Point2d
{
  return m_gradients[id];
}

void PeriodicPerlinGenerator::generate(const int period, const Seed seed)
{
  std::mt19937 generator(seed);
  /// TODO: The gradient should not be completely random, see here:
  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  std::uniform_int_distribution<int> distribution(0, 3);

  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  const auto intToGrad = [](const int id) {
    switch (id)
    {
      case 0:
        return Point2d(1.0f, 1.0f);
      case 1:
        return Point2d(-1.0f, 1.0f);
      case 2:
        return Point2d(1.0f, -1.0f);
      case 3:
      default:
        return Point2d(-1.0f, -1.0f);
    }
  };

  std::vector<int> rnd;

  m_gradients.resize(period);
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  std::for_each(m_gradients.begin(),
                m_gradients.end(),
                [&distribution, &generator, &intToGrad, &rnd](Point2d &grad) {
                  rnd.push_back(distribution(generator));
                  grad = intToGrad(rnd.back());
                });

  auto id = 0;
  for (const auto &v : m_gradients)
  {
    std::cout << "perlin[" << id << "]: " << v(0) << "x" << v(1) << " (" << rnd[id] << ")"
              << std::endl;
    ++id;
  }
}

} // namespace pge::terrain
