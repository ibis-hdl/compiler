/*
 * simple.cpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>
#include <eda/vhdl/analyze/check/label_match.hpp>

#include <iostream>
#include <iomanip>

//#include <eda/vhdl/ast/design_file.hpp>
#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/parser/parse.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/analyze/syntax.hpp>
#include <testsuite/data_set.hpp>

#include <testsuite/namespace_alias.hpp>


BOOST_AUTO_TEST_SUITE( syntax )


struct foo_dataset : public testsuite::dataset_loader
{
    foo_dataset()
    : dataset_loader{ "test_case/foo",
                      // hack for boost.test argc/argv problem
                      "../vhdl/syntax",
                      ".vhdl" }
    { }
} const foo_dataset;


BOOST_DATA_TEST_CASE( basic_syntax,
      foo_dataset.input()
    ^ foo_dataset.expect()
    ^ foo_dataset.test_case_name(),
    input, expected, test_case_name)
{
    std::ostream& os = std::cout;

    ast::design_file design_file;

    // FixMe: introduce make_error_handler(range, ...) ???

    parser::error_handler_type error_handler(input.begin(), input.end(),
                                             os, test_case_name.string());



    parser::parse  parse{ os, error_handler}; // add. arg -> file_name
    bool const parse_ok = parse(input, design_file, test_case_name);

    boost::ignore_unused(expected);

    BOOST_TEST(parse_ok);

    vhdl::context context;
    vhdl::analyze::syntax syntax_check(os, context, error_handler);

    bool const syntax_ok = syntax_check(design_file);

    os << "Syntax " << (syntax_ok ? "" : "not") << " ok\n";

    //++context.warning_count;

    os << vhdl::failure_status(context) << "\n";
}


BOOST_AUTO_TEST_SUITE_END()

