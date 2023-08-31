
#include "PeriodicPerlinGenerator.hh"
#include <random>

#include <iostream>

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

namespace {
/// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
const std::vector<Eigen::Vector3f> DEFAULT_GRADIENTS = {Eigen::Vector3f(1.0f, 1.0f, 0.0f),
                                                        Eigen::Vector3f(-1.0f, 1.0f, 0.0f),
                                                        Eigen::Vector3f(1.0f, -1.0f, 0.0f),
                                                        Eigen::Vector3f(-1.0f, -1.0f, 0.0f),
                                                        Eigen::Vector3f(1.0f, 0.0f, 1.0f),
                                                        Eigen::Vector3f(-1.0f, 0.0f, 1.0f),
                                                        Eigen::Vector3f(1.0f, 0.0f, -1.0f),
                                                        Eigen::Vector3f(-1.0f, 0.0f, -1.0f),
                                                        Eigen::Vector3f(0.0f, 1.0f, 1.0f),
                                                        Eigen::Vector3f(0.0f, -1.0f, 1.0f),
                                                        Eigen::Vector3f(0.0f, 1.0f, -1.0f),
                                                        Eigen::Vector3f(0.0f, -1.0f, -1.0f)};
} // namespace

void PeriodicPerlinGenerator::generate(const int period, const Seed seed)
{
  std::mt19937 generator(seed);
  /// TODO: The gradient should not be completely random, see here:
  /// https://mrl.cs.nyu.edu/~perlin/paper445.pdf
  std::uniform_int_distribution<int> distribution(0, 11);

  std::vector<int> rnd;

  m_gradients.resize(period);
  /// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2/perlin-noise.html
  for (auto &grad : m_gradients)
  {
    rnd.push_back(distribution(generator));
    grad = DEFAULT_GRADIENTS[rnd.back()].head(m_spaceDimension);
  }

  auto id = 0;
  for (const auto &v : m_gradients)
  {
    std::cout << "perlin[" << id << "]: " << v << " (" << rnd[id] << ")" << std::endl;
    ++id;
  }
}

} // namespace pge::terrain
