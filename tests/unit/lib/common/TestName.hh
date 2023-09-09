
#pragma once

#include <gtest/gtest.h>
#include <string>

namespace pge::terrain {

template<typename TestCase>
auto testNameFromSingleInputPoint(const ::testing::TestParamInfo<TestCase> &info) -> std::string;

template<typename TestCase>
auto testNameFromTestCase(const ::testing::TestParamInfo<TestCase> &info) -> std::string;

template<typename TestCase>
auto testNameFromLatticePointAndExpected(const ::testing::TestParamInfo<TestCase> &info)
  -> std::string;

template<typename TestCase>
auto testNameFromPointLatticePointAndExpected(const ::testing::TestParamInfo<TestCase> &info)
  -> std::string;

} // namespace pge::terrain

#include "TestName.hxx"