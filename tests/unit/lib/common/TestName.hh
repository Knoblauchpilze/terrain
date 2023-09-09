
#pragma once

#include <gtest/gtest.h>
#include <string>

namespace pge::terrain {

template<typename TestCase>
auto testNameForSingleInputPoint(const ::testing::TestParamInfo<TestCase> &info) -> std::string;

template<typename TestCase>
auto testNameFromTestCase(const ::testing::TestParamInfo<TestCase> &info) -> std::string;

} // namespace pge::terrain

#include "TestName.hxx"