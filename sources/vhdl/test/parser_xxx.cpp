/*
 * parser_xxx.cpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( productions )


namespace btt = boost::test_tools;
namespace but = boost::unit_test;
namespace butd = boost::unit_test::data;

namespace fs = boost::filesystem;

namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;



struct xxx_dataset : public ::x3_test::dataset_loader
{
    xxx_dataset()
    : dataset_loader{ "test_case/case_statement" }
    { }
} const xxx_dataset;


BOOST_DATA_TEST_CASE( xxx,
      butd::make(xxx_dataset.input())
    ^ butd::make(xxx_dataset.expect())
    ^ butd::make(xxx_dataset.test_file_name()),
    VHDL_input, expect_AST, file)
{
    using x3_test::testing_parser;

    typedef ast::case_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_input, parser::case_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("PARSED AST = '" << parsed_AST << "'");
    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()

