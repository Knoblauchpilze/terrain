
#include "PeriodicGradientGenerator.hh"
#include <random>

namespace pge::terrain {

PeriodicGradientGenerator::PeriodicGradientGenerator(const int period, const Seed seed)
  : AbstractPeriodicGradientGenerator(period, seed)
{
  generate(period, seed);
}

auto PeriodicGradientGenerator::gradientAt(const int id) const noexcept -> utils::Vector2f
{
  return m_gradients[id];
}

void PeriodicGradientGenerator::generate(const int period, const Seed seed)
{
  std::mt19937 generator(seed);
  /// TODO: The gradient should not be completely random, see here:
  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

  m_gradients.resize(period);
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  std::for_each(m_gradients.begin(),
                m_gradients.end(),
                [&distribution, &generator](utils::Vector2f &grad) {
                  grad.x() = distribution(generator);
                  grad.y() = distribution(generator);

                  grad.normalize();
                });

  auto id = 0;
  for (const auto &v : m_gradients)
  {
    std::cout << "gradient[" << id << "]: " << v.toString() << std::endl;
    ++id;
  }
}

} // namespace pge::terrain
