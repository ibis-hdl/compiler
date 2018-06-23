/*
 * simple.cpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

//#include <eda/vhdl/ast/design_file.hpp>
#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/parser/parse.hpp>

#include <testsuite/data_set.hpp>



BOOST_AUTO_TEST_SUITE( syntax )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
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


BOOST_DATA_TEST_CASE( foo,
      foo_dataset.input()
    ^ foo_dataset.expect()
    ^ foo_dataset.test_case_name(),
    input, expected, test_case_name)
{
    ast::design_file design_file;

    parser::parse  parse{ std::cout };
    bool const parse_ok = parse(input, design_file, test_case_name);

    BOOST_TEST(parse_ok);
}


BOOST_AUTO_TEST_SUITE_END()

