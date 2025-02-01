//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/analyze/syntax.hpp>
#include <ibis/vhdl/analyze/diagnostic_handler.hpp>
#include <ibis/vhdl/analyze/context.hpp>
#include <ibis/vhdl/analyze/context.hpp>
#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/context.hpp>

#include <testsuite/vhdl/syntax/failure_diagnostic_fixture.hpp>
#include <testsuite/vhdl/syntax/dataset.hpp>

// #include <testsuite/namespace_alias.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <boost/core/ignore_unused.hpp>

#include <iostream>
#include <string_view>
#include <iomanip>

namespace analyze = ibis::vhdl::analyze;

using namespace ibis::vhdl;

using testsuite::vhdl::syntax::failure_diagnostic_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_FIXTURE_TEST_SUITE(syntax_check, failure_diagnostic_fixture)

// ToDo Source same as label_match_test.cpp - unify test

//
// SUCCESS test case
//
BOOST_DATA_TEST_CASE(keyword_ok,                                                              // --
                     utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("keyword_ok"),  // --
                     input, expected, test_case_name)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    parser::position_cache<iterator_type> position_cache{};

    auto current_file = file_mapper.add_file(test_case_name, input);

    btt::output_test_stream output;
    ast::design_file design_file;
    parser::context vhdl_ctx;

    {
        parser::parse parse{ output };

        bool const parse_ok = parse(std::move(current_file), position_cache, vhdl_ctx, design_file);

        // syntactically correct
        BOOST_TEST_REQUIRE(parse_ok == true);
        BOOST_TEST_REQUIRE(vhdl_ctx.error_free() == true);
    }

    {
        analyze::diagnostic_handler<parser::iterator_type> diagnostic_handler{
            output, std::move(current_file), std::ref(position_cache), std::ref(vhdl_ctx)
        };
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
    keyword_mismatch,                                                              // --
    utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("keyword_mismatch"),  // --
    input, expected, test_case_name)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    parser::position_cache<iterator_type> position_cache{};

    auto current_file = file_mapper.add_file(test_case_name, input);

    btt::output_test_stream output;
    ast::design_file design_file;
    parser::context vhdl_ctx;

    {
        parser::parse parse{ output };

        bool const parse_ok = parse(std::move(current_file), position_cache, vhdl_ctx, design_file);

        // syntactically correct
        BOOST_TEST_REQUIRE(parse_ok == true);
        BOOST_TEST_REQUIRE(vhdl_ctx.error_free() == true);
    }

    {
        analyze::diagnostic_handler<parser::iterator_type> diagnostic_handler{
            output, std::move(current_file), std::ref(position_cache), std::ref(vhdl_ctx)
        };
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
