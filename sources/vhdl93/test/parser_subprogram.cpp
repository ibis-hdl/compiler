/*
 * parser_subprogram.cpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl93/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( subprogram )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;



/*
 * subprogram_specification
 */
struct subprogram_specification_dataset : public ::x3_test::dataset_loader
{
    subprogram_specification_dataset()
    : dataset_loader{ "test_case/subprogram_specification" }
    { }
} const subprogram_specification_dataset;


BOOST_DATA_TEST_CASE( subprogram_specification,
      subprogram_specification_dataset.input()
    ^ subprogram_specification_dataset.expect()
    ^ subprogram_specification_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::subprogram_specification attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::subprogram_specification);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()


