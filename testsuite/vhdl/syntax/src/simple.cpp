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
#include <testsuite/data_set.hpp>



BOOST_AUTO_TEST_SUITE( syntax )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace analyze = eda::vhdl::analyze;
namespace ast    = eda::vhdl::ast;


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
    ast::design_file design_file;

    parser::parse  parse{ std::cout };
    bool const parse_ok = parse(input, design_file, test_case_name);

    boost::ignore_unused(expected);

    BOOST_TEST(parse_ok);

    auto check_label = analyze::check_label_match{std::cout};
    bool const check_ok = check_label(design_file);
    std::cout << "check = "  << std::boolalpha << check_ok << "\n";
}


BOOST_AUTO_TEST_SUITE_END()

