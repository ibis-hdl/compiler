/*
 * label_check_test.cpp
 *
 *  Created on: 18.08.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <boost/core/ignore_unused.hpp>

#include <iostream>
//#include <string_view>
//#include <iomanip>

//#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/ast/node/design_file.hpp>
#include <eda/vhdl/parser/parse.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/analyze/syntax.hpp>
#include <eda/vhdl/analyze/error_handler.hpp>
#include <eda/vhdl/ast/position_cache.hpp>
//#include <eda/vhdl/ast/ast_stats.hpp>
#include <eda/vhdl/context.hpp>

#include <testsuite/common/data_set.hpp>
#include <testsuite/common/failure_diagnostic_fixture.hpp>

#include <testsuite/common/namespace_alias.hpp>	// IWYU pragma: keep


namespace analyze = eda::vhdl::analyze;


BOOST_AUTO_TEST_SUITE( syntax_check )


/*
 * SUCCESS test case
 */
BOOST_DATA_TEST_CASE_F( testsuite::failure_diagnostic_fixture,
    labels_ok,
    utf_data::make_delayed<testsuite::dataset_loader>( "test_case/labels_ok" ),
    input, expected, test_case_name)
{
    btt::output_test_stream                         os;
    ast::position_cache<parser::iterator_type>      position_cache;
    ast::design_file                                design_file;

    {
        std::size_t const id = position_cache.add_file(test_case_name, input);

        parser::error_handler_type                  error_handler{ os, position_cache.handle(id) };
        parser::parse                               parse{ os, error_handler };

        bool const parse_ok = parse(position_cache.file_contents(id), design_file);

        boost::ignore_unused(expected);

        BOOST_TEST_REQUIRE(parse_ok);
    }

    vhdl::context                                   context;

    {
        analyze::error_handler<parser::iterator_type> error_handler{ os, position_cache };
        analyze::syntax_checker                     syntax_check{ os, context, error_handler };

        syntax_check(design_file);

        bool const syntax_ok = context.error_free();
        BOOST_TEST(syntax_ok);
    }

    if (!current_test_passing()) {
        failure_closure(test_case_name, input, os.str());
        return;
    }

    BOOST_TEST(os.str() == expected, btt::per_element());
    failure_closure(test_case_name, input, os.str());
}


/*
 * FAILURE test case
 */
BOOST_DATA_TEST_CASE_F( testsuite::failure_diagnostic_fixture,
    label_missmatch,
    utf_data::make_delayed<testsuite::dataset_loader>( "test_case/label_missmatch" ),
    input, expected, test_case_name)
{
    btt::output_test_stream                         os;
    ast::position_cache<parser::iterator_type>      position_cache;
    ast::design_file                                design_file;

    {
        std::size_t const id = position_cache.add_file(test_case_name, input);

        parser::error_handler_type                  error_handler{ os, position_cache.handle(id) };
        parser::parse                               parse{ os, error_handler };

        bool const parse_ok = parse(position_cache.file_contents(id), design_file);

        boost::ignore_unused(expected);

        BOOST_TEST_REQUIRE(parse_ok);
    }

    vhdl::context                                   context;

    {
        analyze::error_handler<parser::iterator_type> error_handler{ os, position_cache };
        analyze::syntax_checker                     syntax_check{ os, context, error_handler };

        syntax_check(design_file);

        bool const syntax_ok = context.error_free();
        BOOST_TEST(!syntax_ok);
    }

    if (!current_test_passing()) {
        failure_closure(test_case_name, input, os.str());
        return;
    }

    BOOST_TEST(os.str() == expected, btt::per_element());
    failure_closure(test_case_name, input, os.str());
}


BOOST_AUTO_TEST_SUITE_END()
