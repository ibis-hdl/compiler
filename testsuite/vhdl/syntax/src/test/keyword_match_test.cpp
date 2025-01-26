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

//
// SUCCESS test case
//
BOOST_DATA_TEST_CASE(keyword_ok,                                                              // --
                     utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("keyword_ok"),  // --
                     input, expected, test_case_name)
{
    using iterator_type = parser::iterator_type;

    btt::output_test_stream os;
    ast::design_file design_file;

    {
        ibis::util::file_mapper file_mapper{};
        auto const file_id = file_mapper.add_file(test_case_name, input);

        parser::position_cache<iterator_type> position_cache{};
        auto position_proxy = position_cache.get_proxy(file_id);

        parser::parse parse{ os };
        parser::context ctx;

        bool const parse_ok = parse(std::move(position_proxy), ctx, design_file);
        if (!parse_ok) {
            std::cout << os.str() << std::endl;
        }

        BOOST_TEST_REQUIRE(parse_ok);
    }

    {
        ibis::util::file_mapper file_mapper{};
        auto const file_id = file_mapper.add_file(test_case_name, input);

        parser::position_cache<iterator_type> position_cache{};
        auto position_proxy = position_cache.get_proxy(file_id);

        analyze::context ctx;
        analyze::diagnostic_handler<parser::iterator_type> diagnostic_handler{
            os, ctx, std::move(position_proxy)
        };
        analyze::syntax_checker syntax_check{ os, ctx, diagnostic_handler };

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
    keyword_mismatch,                                                              // --
    utf_data::make_delayed<testsuite::vhdl::syntax::dataset>("keyword_mismatch"),  // --
    input, expected, test_case_name)
{
    using iterator_type = parser::iterator_type;

    btt::output_test_stream os;
    ast::design_file design_file;

    {
        ibis::util::file_mapper file_mapper{};
        auto const file_id = file_mapper.add_file(test_case_name, input);

        parser::position_cache<iterator_type> position_cache{};
        auto position_proxy = position_cache.get_proxy(file_id);

        parser::parse parse{ os };
        parser::context ctx;

        bool const parse_ok = parse(std::move(position_proxy), ctx, design_file);
        if (!parse_ok) {
            std::cout << os.str() << std::endl;
        }

        BOOST_TEST_REQUIRE(parse_ok);
    }

    {
        ibis::util::file_mapper file_mapper{};
        auto const file_id = file_mapper.add_file(test_case_name, input);

        parser::position_cache<iterator_type> position_cache{};
        auto position_proxy = position_cache.get_proxy(file_id);

        analyze::context ctx;
        analyze::diagnostic_handler<parser::iterator_type> diagnostic_handler{
            os, ctx, std::move(position_proxy)
        };
        analyze::syntax_checker syntax_check{ os, ctx, diagnostic_handler };

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
