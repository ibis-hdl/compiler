/*
 * parser_aspect.cpp
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


BOOST_AUTO_TEST_SUITE( clause )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;



/*
 * generic_map_aspect
 */
struct generic_map_aspect_dataset : public ::x3_test::dataset_loader
{
    generic_map_aspect_dataset()
    : dataset_loader{ "test_case/generic_map_aspect" }
    { }
} const generic_map_aspect_dataset;


BOOST_DATA_TEST_CASE( generic_map_aspect,
      generic_map_aspect_dataset.input()
    ^ generic_map_aspect_dataset.expect()
    ^ generic_map_aspect_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::generic_map_aspect attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::generic_map_aspect);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * port_map_aspect
 */
struct port_map_aspect_dataset : public ::x3_test::dataset_loader
{
    port_map_aspect_dataset()
    : dataset_loader{ "test_case/port_map_aspect" }
    { }
} const port_map_aspect_dataset;


BOOST_DATA_TEST_CASE( port_map_aspect,
      port_map_aspect_dataset.input()
    ^ port_map_aspect_dataset.expect()
    ^ port_map_aspect_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::port_map_aspect attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::port_map_aspect);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



BOOST_AUTO_TEST_SUITE_END()
