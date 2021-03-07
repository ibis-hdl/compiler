/*
 * literal_printer_test.cpp
 *
 *  Created on: 17.09.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/literal_printer.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <testsuite/common/namespace_alias.hpp>


BOOST_AUTO_TEST_SUITE( literal_print )

using namespace eda::vhdl::ast;

// Check on correct printing of quoted string literals
std::vector<std::string> const input_string_literal{
    R"("""")",
    R"(%%%%)",
    R"(""Hello"")",
    R"(Quotation: ""REPORT..."")",
    R"("%"%")",
    R"(%"%"")",
};

std::vector<std::string> const expected_string_literal{
    R"("")",
    R"(%%)",
    R"("Hello")",
    R"(Quotation: "REPORT...")",
    R"("%"%")", // as-is
    R"(%"%")",  // as-is
};

BOOST_DATA_TEST_CASE(
    string_literal,
    utf_data::make(input_string_literal) ^ expected_string_literal,
    input,                                 expected)
{
    auto const as_strlit = [](std::string const& str) {
        ast::string_literal l;
        l.literal = boost::make_iterator_range(str);
        return l;
    };

    using eda::vhdl::ast::literal_printer;

    btt::output_test_stream                         os;

    literal_printer literal{ as_strlit(input) };
    os << literal;

    BOOST_TEST(os.str() == expected, btt::per_element());
}

/// Note: Here is stated, that testing of 
/// ast::{bit_string, decimal, based}_literal
/// etc. is to simple for testing, but preparing the tests is a big 
/// effort. Implicit they are checked by parser tests.

BOOST_AUTO_TEST_SUITE_END()
