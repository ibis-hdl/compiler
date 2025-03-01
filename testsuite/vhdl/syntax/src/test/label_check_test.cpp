//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/analyze/syntax.hpp>
#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/context.hpp>
#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/ast/ast_context.hpp>

#include <testsuite/vhdl/syntax/failure_diagnostic_fixture.hpp>
#include <testsuite/vhdl/syntax/dataset.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/tools/interface.hpp>  // BOOST_TEST_REQUIRE, BOOST_TEST
#include <boost/test/unit_test_suite.hpp>  // BOOST_FIXTURE_TEST_SUITE

#include <functional>

namespace analyze = ibis::vhdl::analyze;

using namespace ibis::vhdl;

using testsuite::vhdl::syntax::failure_diagnostic_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_FIXTURE_TEST_SUITE(syntax_check, failure_diagnostic_fixture)

// ToDo Source same as keyboard_match_test.cpp - unify test

//
// SUCCESS test case
//
BOOST_DATA_TEST_CASE(labels_ok,                                                              // --
                     utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("labels_ok"),  // --
                     input, expected, test_case_name)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto current_file = file_mapper.add_file(test_case_name, input);
    parser::position_cache<iterator_type> position_cache{};
    ibis::vhdl::ast::ast_context<iterator_type> ast_context{ current_file, position_cache };

    btt::output_test_stream output;
    ast::design_file design_file;
    ibis::vhdl::vhdl_global_context vhdl_ctx;

    {
        parser::parse<iterator_type> const parse{ output };

        bool const parse_ok = parse(current_file, position_cache, vhdl_ctx, design_file);

        // syntactically correct
        BOOST_TEST_REQUIRE(parse_ok == true);
        BOOST_TEST_REQUIRE(vhdl_ctx.error_free() == true);
    }

    {
        ibis::vhdl::diagnostic_handler<parser::iterator_type> diagnostic_handler{ output,
                                                                                  ast_context,
                                                                                  vhdl_ctx };
        analyze::syntax_checker syntax_check{ output, vhdl_ctx, diagnostic_handler };

        syntax_check(design_file);

        BOOST_TEST(vhdl_ctx.error_free() == true);
    }

    if (!current_test_passing()) {
        // failure_closure(test_case_name, input, output.str());
        return;
    }

    // std::cout << "### output:\n" << os.str() << " -- -- -- -- -- -- -- -- -- -- -- -- -- --\n ";

    BOOST_TEST(output.str() == expected, btt::per_element());
    // failure_closure(test_case_name, input, expected, output.str());
}

//
// FAILURE test case
//
BOOST_DATA_TEST_CASE(
    label_mismatch,                                                              // --
    utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("label_mismatch"),  // --
    input, expected, test_case_name)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto current_file = file_mapper.add_file(test_case_name, input);
    parser::position_cache<iterator_type> position_cache{};
    ast::ast_context<iterator_type> ast_context{ current_file, position_cache };

    btt::output_test_stream output;
    ast::design_file design_file;
    ibis::vhdl::vhdl_global_context vhdl_ctx;

    {
        parser::parse<iterator_type> const parse{ output };

        bool const parse_ok = parse(current_file, position_cache, vhdl_ctx, design_file);

        // syntactically correct
        BOOST_TEST_REQUIRE(parse_ok == true);
        BOOST_TEST_REQUIRE(vhdl_ctx.error_free() == true);
    }

    {
        ibis::vhdl::diagnostic_handler<parser::iterator_type> diagnostic_handler{ output,
                                                                                  ast_context,
                                                                                  vhdl_ctx };
        analyze::syntax_checker syntax_check{ output, vhdl_ctx, diagnostic_handler };

        syntax_check(design_file);

        BOOST_TEST(vhdl_ctx.error_free() == false);
    }

    if (!current_test_passing()) {
        // failure_closure(test_case_name, input, output.str());
        return;
    }

    // std::cout << "### output:\n" << output.str() << " -- -- -- -- -- -- -- -- -- -- -- -- -- --\n
    // ";

    BOOST_TEST(output.str() == expected, btt::per_element());
    // failure_closure(test_case_name, input, expected, output.str());
}

BOOST_AUTO_TEST_SUITE_END()
