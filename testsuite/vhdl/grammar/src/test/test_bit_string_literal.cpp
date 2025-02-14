//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/basic_ast_walker.hpp>
#include <ibis/vhdl/ast/ast_formatter.hpp>
#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/node/constant_declaration.hpp>
#include <ibis/vhdl/ast/node/design_file.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/interface.hpp>  // BOOST_TEST()
#include <boost/test/tools/context.hpp>    // BOOST_TEST_CONTEXT()
#include <boost/test/unit_test_suite.hpp>  // BOOST_AUTO_TEST_CASE()
#include <boost/test/tree/decorator.hpp>   // utf::label

#include <testsuite/testsuite_parser.hpp>
#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <array>
#include <cassert>
#include <cstddef>
#include <format>
#include <functional>
#include <iostream>
#include <string_view>

using namespace ibis::vhdl;

namespace valid_data {

using numeric_base_specifier = ibis::vhdl::ast::bit_string_literal::numeric_base_specifier;
using namespace std::literals::string_view_literals;

// XXXX take the literals from testsuite / numeric_literals to check all valid digits and max

// Valid input to test the grammar rule, no numeric conversion here.
constexpr std::string_view const input = R"(
-- test 'bit_string_literal' grammar
PACKAGE bitstring IS
    -- bin
    CONSTANT bin_01 : bit_vector := B"0101";
    CONSTANT bin_02 : bit_vector := b"0101";
    CONSTANT bin_03 : bit_vector := b"1_0";
    CONSTANT bin_04 : bit_vector := b"1111_1111_1111";
    -- oct
    CONSTANT oct_01 : bit_vector := O"01234";
    CONSTANT oct_02 : bit_vector := o"01234";
    CONSTANT oct_03 : bit_vector := o"777";
    CONSTANT oct_04 : bit_vector := o"7";
    CONSTANT oct_05 : bit_vector := o"7_42";
    CONSTANT oct_06 : bit_vector := o"0_1_2";
    -- hex
    CONSTANT hex_01 : bit_vector := X"01234";
    CONSTANT hex_02 : bit_vector := x"01234";
    CONSTANT hex_03 : bit_vector := x"aB";
    CONSTANT hex_04 : bit_vector := x"f";
    CONSTANT hex_05 : bit_vector := x"ffff";
    CONSTANT hex_06 : bit_vector := x"a_b";
    CONSTANT hex_07 : bit_vector := x"a_b_c";
END PACKAGE;
)";

struct gold_data_type {
    numeric_base_specifier base_specifier;
    std::string_view literal;
    std::string_view formatted;
};
// clang-format off
constexpr auto gold_data = std::to_array<gold_data_type>({
    // bin
    { .base_specifier = numeric_base_specifier::base2, .literal = "0101", .formatted = "b0101" },
    { .base_specifier = numeric_base_specifier::base2, .literal = "0101", .formatted = "b0101" },
    { .base_specifier = numeric_base_specifier::base2, .literal = "1_0", .formatted = "b1_0" },
    { .base_specifier = numeric_base_specifier::base2, .literal = "1111_1111_1111", .formatted = "b1111_1111_1111" },
    // oct
    { .base_specifier = numeric_base_specifier::base8, .literal = "01234", .formatted = "o01234" },
    { .base_specifier = numeric_base_specifier::base8, .literal = "01234", .formatted = "o01234" },
    { .base_specifier = numeric_base_specifier::base8, .literal = "777", .formatted = "o777" },
    { .base_specifier = numeric_base_specifier::base8, .literal = "7", .formatted = "o7" },
    { .base_specifier = numeric_base_specifier::base8, .literal = "7_42", .formatted = "o7_42" },
    { .base_specifier = numeric_base_specifier::base8, .literal = "0_1_2", .formatted = "o0_1_2" },
    // hex
    { .base_specifier = numeric_base_specifier::base16, .literal = "01234", .formatted = "x01234" },
    { .base_specifier = numeric_base_specifier::base16, .literal = "01234", .formatted = "x01234" },
    { .base_specifier = numeric_base_specifier::base16, .literal = "aB", .formatted = "xaB" },
    { .base_specifier = numeric_base_specifier::base16, .literal = "f", .formatted = "xf" },
    { .base_specifier = numeric_base_specifier::base16, .literal = "ffff", .formatted = "xffff" },
    { .base_specifier = numeric_base_specifier::base16, .literal = "a_b", .formatted = "xa_b" },
    { .base_specifier = numeric_base_specifier::base16, .literal = "a_b_c", .formatted = "xa_b_c" },
});
// clang-format on

template <typename GoldDataT, bool verbose = false>
struct test_worker {
    test_worker(GoldDataT const& data)
        : gold_data{ data }
        , os{ std::cout }
    {
    }

    void operator()(ast::constant_declaration const& node,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
        if constexpr (verbose) {
            // ToDo [C++20] non-critical C++20 std::format, more complex work using ast walker
            static ast::printer print(os);
            os << std::format("({:2d}/{:2d}): identifier '", index + 1, std::size(gold_data));
            print(node.identifier_list);
            os << "' of subtype '";
            print(node.subtype_indication);
            os << "' with expr { ";
            if (node.expression) {
                print(*node.expression);
            }
            os << " }\n";
        }
    }

    void operator()(ast::bit_string_literal const& node,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
        BOOST_TEST_CONTEXT(">>> Test index at " << index << " <<<")
        {
            auto const& expected = gold_data.get().at(index);
            BOOST_TEST(node.base_specifier == expected.base_specifier);
            auto const node_literal = std::string_view{ node.literal };
            BOOST_TEST(node_literal == expected.literal, btt::per_element());
            BOOST_TEST(std::format("{}", node) == expected.formatted, btt::per_element());
            // Bug Failed in MSVC Debug mode, node_literal shows non-ascii chars
            if constexpr ((false)) {
                std::cout << std::format("    >>> Failure context: '{}' <-> '{}' (expected)\n",
                                         node_literal, expected.literal);
            }
        }
        ++index;
    }

    // "catch them all" operator to be able to walk through the AST organized by ast_walker
    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& /* ast_node */,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
    }

private:
    std::reference_wrapper<GoldDataT> gold_data;
    std::size_t mutable index = 0;
    std::ostream& os;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

using verifier_type = ast::basic_ast_walker<test_worker<decltype(gold_data), false /* verbose */>>;

auto const verify = [](ast::design_file const& ast) {
    verifier_type verifier(gold_data);
    verifier(ast);
};

}  // namespace valid_data

// clang-format off
BOOST_AUTO_TEST_CASE(bit_string_literal_valid_test,    // test shall pass
                     *utf::label("bit_string_literal")
                     *utf::label("formatter"))
// clang-format on
{
    using ast::design_file;
    using testsuite::testsuite_parse;
    using namespace valid_data;

    testsuite_parse parse("bit_string_literal");
    ast::design_file ast;

    BOOST_TEST(parse(input, ast) == true);

    std::cout << parse.output() << '\n';

    verify(ast);
}
