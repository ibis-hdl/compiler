/*
 * simple.cpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
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

#include <testsuite/namespace_alias.hpp>


namespace analyze = eda::vhdl::analyze;

BOOST_AUTO_TEST_SUITE( syntax )


BOOST_DATA_TEST_CASE( basic_syntax,
    utf_data::make_delayed<testsuite::dataset_loader>( "test_case/foo" ),
    input, expected, test_case_name)
{
    std::ostream& os = std::cerr;

    ast::design_file design_file;

    parser::position_cache<parser::iterator_type> position_cache(input);
    parser::error_handler_type error_handler(os, position_cache, test_case_name);

    parser::parse  parse{ os, error_handler }; // add. arg -> file_name
    bool const parse_ok = parse(input, design_file, test_case_name);

    boost::ignore_unused(expected);

    BOOST_TEST(parse_ok);

#if 0
    vhdl::context context;
    vhdl::analyze::syntax syntax_check(os, context, error_handler);

    bool const syntax_ok = syntax_check(design_file);

    os << "Syntax " << (syntax_ok ? "" : "not") << " ok\n"
       << vhdl::failure_status(context) << "\n";
#else
    vhdl::context context;
    context.error_count.limit() = 20;

    try {
    	analyze::error_handler<parser::iterator_type> syntax_error_handler(os, position_cache, test_case_name);
    	vhdl::analyze::syntax_checker syntax_check{ os, context, syntax_error_handler };
    	syntax_check(design_file);

    	bool const syntax_errors = syntax_check.has_errors();

        os << "Syntax" << (syntax_errors ? " not" : "") << " ok\n"
           << vhdl::failure_status(context) << "\n";
    }
    catch(vhdl::context::error_counter::overflow const&) {
    	os << "fatal: to many errors emitted, stopping now\n";
    	os << context.error_count << "errors generated\n";
    }
#endif

//	ast::ast_stats stats(design_file);
//	std::cout << stats << "\n";
}


BOOST_AUTO_TEST_SUITE_END()

