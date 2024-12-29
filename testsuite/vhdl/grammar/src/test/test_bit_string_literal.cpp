//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/grammar/testsuite_parse.hpp>
#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <ibis/vhdl/ast/basic_ast_walker.hpp>
#include <ibis/vhdl/ast/ast_formatter.hpp>
#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/node/design_file.hpp>

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep

#include <format>
#include <string_view>
#include <iostream>
#include <cassert>
#include <cstddef>

namespace valid_data {

using base_specifier = ast::bit_string_literal::base_specifier;
using namespace std::literals::string_view_literals;

// Valid input to test the grammar rule, no numeric conversion here.
std::string_view const input = R"(
-- test 'bit_string_literal' grammar
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
)";

// clang-format off
struct {
    base_specifier base_type;
    std::string_view literal;
    std::string_view formatted;
} const gold_data[] = {
    // hex
    { .base_type = base_specifier::hex, .literal = "01234", .formatted = "x01234" },
    { .base_type = base_specifier::hex, .literal = "01234", .formatted = "x01234" },
    { .base_type = base_specifier::hex, .literal = "aB", .formatted = "xaB" },
    { .base_type = base_specifier::hex, .literal = "f", .formatted = "xf" },
    { .base_type = base_specifier::hex, .literal = "ffff", .formatted = "xffff" },
    { .base_type = base_specifier::hex, .literal = "a_b", .formatted = "xa_b" },
    { .base_type = base_specifier::hex, .literal = "a_b_c", .formatted = "xa_b_c" },
    // oct
    { .base_type = base_specifier::oct, .literal = "01234", .formatted = "o01234" },
    { .base_type = base_specifier::oct, .literal = "01234", .formatted = "o01234" },
    { .base_type = base_specifier::oct, .literal = "777", .formatted = "o777" },
    { .base_type = base_specifier::oct, .literal = "7", .formatted = "o7" },
    { .base_type = base_specifier::oct, .literal = "7_42", .formatted = "o7_42" },
    { .base_type = base_specifier::oct, .literal = "0_1_2", .formatted = "o0_1_2" },
    // bin
    { .base_type = base_specifier::bin, .literal = "0101", .formatted = "b0101" },
    { .base_type = base_specifier::bin, .literal = "0101", .formatted = "b0101" },
    { .base_type = base_specifier::bin, .literal = "1_0", .formatted = "b1_0" },
    { .base_type = base_specifier::bin, .literal = "1111_1111_1111", .formatted = "b1111_1111_1111" },
};
// clang-format on

template <typename GoldDataT, bool verbose = false>
struct test_worker {
    test_worker(GoldDataT const& gold_data)
        : gold{ gold_data }
        , test_case_count{ sizeof(gold_data) / sizeof(gold_data[0]) }
        , os{ std::cout }
    {
    }

    void operator()(ast::constant_declaration const& node,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
        if constexpr (verbose) {
            // FixMe [C++20] non-critical C++20 std::format, more complex work using ast walker
            static ast::printer print(os);
            os << std::format("({:2d}/{:2d}): identifier '", index + 1, test_case_count);
            print(node.identifier_list);
            os << "' of subtype '";
            print(node.subtype_indication);
            os << "' with expr <";
            if (node.expression) {
                print(*node.expression);
            }
            os << ">\n";
        }
    }

    void operator()(ast::bit_string_literal const& node,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
        assert(index < test_case_count && "index reached count of gold data array size!");

        auto const expected = gold[index];
        // FixMe BOOST_TEST_xxxx("Test index at " << index);
        BOOST_TEST(node.base_type == expected.base_type);
        BOOST_TEST(node.literal == expected.literal);
        BOOST_TEST(std::format("{}", node) == expected.formatted);

        ++index;
    }

    // "catch them all" operator to be able to walk trough the AST organized by ast_walker
    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& /* ast_node */,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
    }

    GoldDataT const& gold;
    std::size_t const test_case_count;
    std::size_t mutable index = 0;
    std::ostream& os;
};

using verifier_type = ast::basic_ast_walker<test_worker<decltype(gold_data), false /* verbose */>>;

auto const verify = [&](ast::design_file const& ast) {
    verifier_type verify(gold_data);
    verify(ast);
};

}  // namespace valid_data

BOOST_AUTO_TEST_CASE(bit_string_literal__valid_test,    // test shall pass
                     *utf::label("bit_string_literal")  //
                         * utf::label("format"))
{
    using testsuite::testsuite_parse;
    using vhdl::ast::design_file;
    using namespace valid_data;

    testsuite_parse parse("bit_string_literal");
    ast::design_file ast;

    BOOST_TEST(parse(input, ast) == true);

    verify(ast);
}
