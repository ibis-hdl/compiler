#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/analyze/syntax.hpp>
#include <ibis/vhdl/analyze/error_handler.hpp>
#include <ibis/vhdl/analyze/context.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/context.hpp>

#include <testsuite/vhdl/syntax/failure_diagnostic_fixture.hpp>
#include <testsuite/vhdl/syntax/dataset.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <boost/core/ignore_unused.hpp>

#include <iostream>

namespace analyze = ibis::vhdl::analyze;

using testsuite::vhdl::syntax::failure_diagnostic_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_FIXTURE_TEST_SUITE(syntax_check, failure_diagnostic_fixture)

//
// SUCCESS test case
//
BOOST_DATA_TEST_CASE(labels_ok,                                                              // --
                     utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("labels_ok"),  // --
                     input, expected, test_case_name)
{
    btt::output_test_stream os;
    parser::position_cache<parser::iterator_type> position_cache;
    parser::context ctx;
    ast::design_file design_file;

    auto position_cache_proxy = position_cache.add_file(test_case_name, input);

    {
        parser::parse parse{ os };

        bool const parse_ok = parse(position_cache_proxy, ctx, design_file);

        BOOST_TEST_REQUIRE(parse_ok);
    }

    {
        analyze::context ctx;
        analyze::error_handler<parser::iterator_type> error_handler{ os, ctx, position_cache_proxy };
        analyze::syntax_checker syntax_check{ os, ctx, error_handler };

        syntax_check(design_file);

        bool const syntax_ok = ctx.error_free();
        BOOST_TEST(syntax_ok);
    }

    if (!current_test_passing()) {
        failure_closure(test_case_name, input, os.str());
        return;
    }

    BOOST_TEST(os.str() == expected, btt::per_element());
    failure_closure(test_case_name, input, expected, os.str());
}

//
// FAILURE test case
//
BOOST_DATA_TEST_CASE(
    label_missmatch,                                                              // --
    utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("label_missmatch"),  // --
    input, expected, test_case_name)
{
    btt::output_test_stream os;
    parser::position_cache<parser::iterator_type> position_cache;
    parser::context ctx;
    ast::design_file design_file;

    auto position_cache_proxy = position_cache.add_file(test_case_name, input);

    {
        parser::parse parse{ os };

        bool const parse_ok = parse(position_cache_proxy, ctx, design_file);

        BOOST_TEST_REQUIRE(parse_ok);
    }

    {
        analyze::context ctx;
        analyze::error_handler<parser::iterator_type> error_handler{ os, ctx, position_cache_proxy };
        analyze::syntax_checker syntax_check{ os, ctx,error_handler };

        syntax_check(design_file);

        bool const syntax_ok = ctx.error_free();
        BOOST_TEST(!syntax_ok);
    }

    if (!current_test_passing()) {
        failure_closure(test_case_name, input, os.str());
        return;
    }

    BOOST_TEST(os.str() == expected, btt::per_element());
    failure_closure(test_case_name, input, expected, os.str());
}

BOOST_AUTO_TEST_SUITE_END()
