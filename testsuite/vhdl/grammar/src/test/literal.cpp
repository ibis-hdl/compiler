//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <testsuite/vhdl/grammar/testsuite_parse.hpp>
#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <ibis/vhdl/ast/basic_ast_walker.hpp>

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep

#include <fmt/format.h>

#include <iostream>

namespace data {

std::string_view const input = R"(
-- bit_string_literal test using package/constant_declaration
PACKAGE bitstring IS
    -- hex
    CONSTANT hex_01 : bit_vector := X"01234";
    CONSTANT hex_02 : bit_vector := x"01234";
    CONSTANT hex_03 : bit_vector := x"aB";
    CONSTANT hex_04 : bit_vector := x"f";
    CONSTANT hex_05 : bit_vector := x"ffff";
    CONSTANT hex_06 : bit_vector := x"a_b";
    CONSTANT hex_07 : bit_vector := x"a_b_c";
    -- oct
    CONSTANT oct_01 : bit_vector := O"01234";
    CONSTANT oct_02 : bit_vector := o"01234";
    CONSTANT oct_03 : bit_vector := o"777";
    CONSTANT oct_04 : bit_vector := o"7";
    CONSTANT oct_05 : bit_vector := o"7_42";
    CONSTANT oct_06 : bit_vector := o"0_1_2";
    -- bin
    CONSTANT bin_01 : bit_vector := B"0101";
    CONSTANT bin_02 : bit_vector := b"0101";
    CONSTANT bin_03 : bit_vector := b"1_0";
    CONSTANT bin_04 : bit_vector := b"1111_1111_1111";
END PACKAGE;

PACKAGE bitstring_failure IS
    -- hex
    CONSTANT hex_01 : bit_vector := x"egg";     -- 'g' is invalid
    CONSTANT hex_02 : bit_vector := x"_0F";     -- leading underscore
    CONSTANT hex_03 : bit_vector := x"ab_";     -- trailing underscore
    -- oct
    CONSTANT oct_01 : bit_vector := o"69";      -- '9' is invalid
    CONSTANT oct_02 : bit_vector := o"_666";    -- leading underscore
    CONSTANT oct_03 : bit_vector := o"666_";    -- trailing underscore
    -- bin
    CONSTANT bin_01 : bit_vector := b"012";     -- '2' is invalid
    CONSTANT bin_02 : bit_vector := b"_11";     -- leading underscore
    CONSTANT bin_03 : bit_vector := b"0_1_;     -- trailing underscore
END PACKAGE;
)";

using base_specifier = ast::bit_string_literal::base_specifier;
using namespace std::literals::string_view_literals;

struct {
    base_specifier      base_type;
    std::string_view    literal;
} const expected[] = {
    // hex
    { base_specifier::hex, "01234"sv },
    { base_specifier::hex, "01234"sv },
    { base_specifier::hex, "aB"sv },
    { base_specifier::hex, "f"sv },
    { base_specifier::hex, "ffff"sv },
    { base_specifier::hex, "a_b"sv },
    { base_specifier::hex, "a_b_c"sv },
    // oct
    { base_specifier::oct, "01234"sv },
    { base_specifier::oct, "01234"sv },
    { base_specifier::oct, "777"sv },
    { base_specifier::oct, "7"sv },
    { base_specifier::oct, "7_42"sv },
    { base_specifier::oct, "0_1_2"sv },
    // bin
    { base_specifier::bin, "0101"sv },
    { base_specifier::bin, "0101"sv },
    { base_specifier::bin, "1_0"sv },
    { base_specifier::bin, "1111_1111_1111"sv },
};

template<typename ExpectedT, bool verbose = false>
struct verify_worker
{
    verify_worker(ExpectedT const& expected_)
    : expected{ expected_ }
    , expected_size{ sizeof(expected_) / sizeof(expected_[0]) }
    , os{ std::cout }
    {  }

    void operator()(ast::constant_declaration const& node, [[maybe_unused]] std::string_view) const 
    {
        if constexpr (verbose) {
            static ast::printer print(os);
            os << fmt::format("verify {0:2d} / {1} (identifier '", test_index + 1, expected_size);
            print(node.identifier_list);
            os << "')\n";
        }
    }

    void operator()(ast::bit_string_literal const& node, [[maybe_unused]] std::string_view) const 
    {
        assert(test_index < expected_size && "test_index reached count of expected array size!");

        BOOST_TEST(node.base_type == expected[test_index].base_type);
        BOOST_TEST(node.literal == expected[test_index].literal);
        ++test_index;
    }

    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const&, [[maybe_unused]] std::string_view) const
    {
    }

    ExpectedT const& expected;
    std::size_t const expected_size;
    std::ostream& os;
    std::size_t mutable test_index = 0;
};

using verifier_type = ast::basic_ast_walker<verify_worker<decltype(expected), false>>;

std::string_view const expected_failure = 
R"(In 'bit_string_literal':28:38: parse error: expecting semicolon ';' here:
  28|     CONSTANT hex_01 : bit_vector := x"egg";     -- 'g' is invalid
    |                                      ^ <<-- here
1 error generated.
)";

} // namespace data

BOOST_AUTO_TEST_CASE(bit_string_literal)
{
    using testsuite::testsuite_parse;
    using vhdl::ast::design_file;
    using namespace data;

    testsuite_parse parse("bit_string_literal");
    ast::design_file ast;

    // FixMe: PACKAGE bitstring_failure shall fail, which does it as parser's output shows
    BOOST_TEST(parse(input, ast) == true);

    verifier_type verify(expected);
    verify(ast);

    // ToDo: add error recovery to the parser, so that all errors can be verified.
    BOOST_TEST(parse.output() == expected_failure, btt::per_element());
    //std::cout << parse.output() << '\n';
}
