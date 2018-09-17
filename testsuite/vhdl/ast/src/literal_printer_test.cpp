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
#include <boost/test/output_test_stream.hpp>

#include <testsuite/namespace_alias.hpp>


BOOST_AUTO_TEST_SUITE( literal_print )

using namespace eda::vhdl::ast;

// Check on correct printing of quoted string literals
std::vector<std::string> const input_literal{
    R"("""")",
    R"(%%%%)",
    R"(""Hello"")",
    R"(Quotation: ""REPORT..."")",
    R"("%"%")",
    R"(%"%"")",
};

std::vector<std::string> expected_literal{
    R"("")",
    R"(%%)",
    R"("Hello")",
    R"(Quotation: "REPORT...")",
    R"("%"%")", // as-is
    R"(%"%")",  // as-is
};

BOOST_DATA_TEST_CASE(
    string_literal,
    utf_data::make(input_literal) ^ expected_literal,
    input,                          expected)
{
    auto const as_strlit = [](std::string const& str) {
        ast::string_literal sl;
        sl.literal = boost::make_iterator_range(str);
        return sl;
    };

    using eda::vhdl::ast::literal_printer;

    btt::output_test_stream                         os;

    literal_printer literal{ as_strlit(input) };
    os << literal;

    BOOST_TEST(os.str() == expected, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()
