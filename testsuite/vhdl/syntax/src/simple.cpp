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
#include <testsuite/data_set.hpp>

#include <testsuite/namespace_alias.hpp>


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
    vhdl::analyze::syntax_checker syntax_check{ os, context, error_handler };
    syntax_check(design_file);
#endif
}


BOOST_AUTO_TEST_SUITE_END()

