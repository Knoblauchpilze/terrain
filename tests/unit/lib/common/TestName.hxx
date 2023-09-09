
#include "PointName.hh"
#include "TestName.hh"

namespace pge::terrain {

template<typename TestCase>
inline auto testNameForSingleInputPoint(const ::testing::TestParamInfo<TestCase> &info)
  -> std::string
{
  return nameOf(info.param.in);
}

template<typename TestCase>
inline auto testNameFromTestCase(const ::testing::TestParamInfo<TestCase> &info) -> std::string
{
  return info.param.name;
}

} // namespace pge::terrain