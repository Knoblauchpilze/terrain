
#include "PointName.hh"
#include "TestName.hh"

namespace pge::terrain {

template<typename TestCase>
inline auto testNameFromSingleInputPoint(const ::testing::TestParamInfo<TestCase> &info)
  -> std::string
{
  return nameOf(info.param.in);
}

template<typename TestCase>
inline auto testNameFromTestCase(const ::testing::TestParamInfo<TestCase> &info) -> std::string
{
  return info.param.name;
}

template<typename TestCase>
auto testNameFromLatticePointAndExpected(const ::testing::TestParamInfo<TestCase> &info)
  -> std::string
{
  std::string out;

  out += nameOf(info.param.latticePoint);
  out += "_";
  out += nameOf(info.param.expected);

  return sanitizeTestName(out);
}

template<typename TestCase>
inline auto testNameFromPointLatticePointAndExpected(const ::testing::TestParamInfo<TestCase> &info)
  -> std::string
{
  std::string out;

  out += nameOf(info.param.inPoint);
  out += "_";
  out += nameOf(info.param.latticePoint);
  out += "_";
  out += std::to_string(info.param.expected);

  return sanitizeTestName(out);
}

} // namespace pge::terrain