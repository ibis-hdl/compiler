/*
 * label_check.cpp
 *
 *  Created on: 18.08.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <boost/core/ignore_unused.hpp>

#include <iostream>
#include <string_view>
#include <iomanip>

#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/parser/parse.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/analyze/syntax.hpp>
#include <eda/vhdl/analyze/error_handler.hpp>
#include <eda/vhdl/ast/ast_stats.hpp>

#include <testsuite/data_set.hpp>
#include <testsuite/failure_diagnostic_fixture.hpp>

#include <testsuite/namespace_alias.hpp>


namespace analyze = eda::vhdl::analyze;


BOOST_AUTO_TEST_SUITE( syntax_labels )


/*
 * SUCCESS test case
 */
BOOST_DATA_TEST_CASE_F( testsuite::failure_diagnostic_fixture, labels_ok,
    utf_data::make_delayed<testsuite::dataset_loader>( "test_case/labels_ok" ),
    input, expected, test_case_name)
{
    btt::output_test_stream                     	os;

    ast::design_file 								design_file;

    ast::position_cache<parser::iterator_type> 		position_cache(input);
    parser::error_handler_type 						error_handler(os, position_cache, test_case_name);

    parser::parse  									parse{ os, error_handler };

    bool const parse_ok = parse(input, design_file, test_case_name);

    boost::ignore_unused(expected);

    BOOST_TEST_REQUIRE(parse_ok);

    vhdl::context 									context;

	analyze::error_handler<parser::iterator_type> 	syntax_error_handler(os, position_cache, test_case_name);
	analyze::syntax_checker 						syntax_check{ os, context, syntax_error_handler };

	syntax_check(design_file);

	bool const syntax_ok = syntax_check.get_worker().success();
    BOOST_TEST(syntax_ok);

    BOOST_TEST(os.str() == expected, btt::per_element());
    failure_closure(test_case_name, input, os.str());
}


/*
 * FAILURE test case
 */
BOOST_DATA_TEST_CASE_F( testsuite::failure_diagnostic_fixture, label_missmatch,
    utf_data::make_delayed<testsuite::dataset_loader>( "test_case/label_missmatch" ),
    input, expected, test_case_name)
{
    btt::output_test_stream                     	os;

    ast::design_file 								design_file;

    ast::position_cache<parser::iterator_type> 		position_cache(input);
    parser::error_handler_type 						error_handler(os, position_cache, test_case_name);

    parser::parse  									parse{ os, error_handler };

    bool const parse_ok = parse(input, design_file, test_case_name);

    boost::ignore_unused(expected);

    BOOST_TEST_REQUIRE(parse_ok);

    vhdl::context 									context;

	analyze::error_handler<parser::iterator_type> 	syntax_error_handler(os, position_cache, test_case_name);
	analyze::syntax_checker 						syntax_check{ os, context, syntax_error_handler };

	syntax_check(design_file);

	bool const syntax_ok = syntax_check.get_worker().success();
    BOOST_TEST(!syntax_ok);

    if (!current_test_passing()) {
        failure_closure(test_case_name, input, os.str());
        return;
    }

    BOOST_TEST(os.str() == expected, btt::per_element());
    failure_closure(test_case_name, input, os.str());
}


BOOST_AUTO_TEST_SUITE_END()




