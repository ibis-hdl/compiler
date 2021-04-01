// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BOOST_TEST_MODULE VHDL AST Test Suite

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep

// FixMe: May move the global fixture to own file to compile

#include <testsuite/ast/position_cache_fixture.hpp>

using position_cache_fixture = testsuite::position_cache_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_GLOBAL_FIXTURE(position_cache_fixture);
