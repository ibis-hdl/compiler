//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>
#include <testsuite/vhdl/numeric_convert/binary_string.hpp>

#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/vhdl/ast/numeric_convert.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <vector>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(numeric_convert)

namespace detail {

//******************************************************************************
// generator helper functions
//******************************************************************************

template <class T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type to_based_literal(
    unsigned base, T value, std::string const& postfix = "")
{
    using namespace testsuite::vhdl::numeric_convert::util;

    std::stringstream ss;

    switch (base) {
        case 2: {
            ss << base << '#' << binary_string(value) << postfix << '#';
            break;
        }
        case 8: {
            ss << base << '#' << octal_string(value) << postfix << '#';
            break;
        }
        case 10: {
            ss << base << '#' << value << postfix << '#';
            break;
        }
        case 16: {
            ss << base << '#' << hexadecimal_string(value) << postfix << '#';
            break;
        }
        default:
            // as is:
            ss << base << '#' << value << postfix << '#';
    }

    return ss.str();
}

#if 0
template<class T>
typename std::enable_if<
    std::is_floating_point<T>::value, std::string
>::type
to_based_literal(unsigned base, T value)
{
    std::stringstream ss;

    switch(base) {
    case 2: {
        ss << base << '#' << std::bin << value << '#';
        break;
    }
    case 8: {
        ss << base << '#' << std::oct  << value << '#';
        break;
    }
    case 10: {
        ss  << base << '#'             << value << '#';
        break;
    }
    case 16: {
        ss << base << '#' << std::hex  << value << '#';
        break;
    }
    default:
        std::cerr << "ERROR in function " << __FUNCTION__
                  << ", unexpected base " << base << '\n';
    }

    return ss.str();
}
#endif

}  // namespace detail

namespace btt = boost::test_tools;

using ast::numeric_convert;

//******************************************************************************
// integer based_literal of different bases
//******************************************************************************
std::vector<std::string> const integer_lit{
    // binary
    "2#0#",
    "2#0#E0",
    "2#1#",
    "2#1#E0",
    "2#1#E1",
    "2#1#E2",
    // octal
    "8#0#",
    "8#1#",
    "8#1#E1",
    "8#42#",
    // hexadecimal
    "16#1#",
    "16#F#E1",
    // Examples from
    // - IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    //
    //   2#1111_1111#            = 255 (integer literal)
    //   16#FF#                  = 255 (integer literal)
    //   016#0FF#                = 255 (integer literal)
    //   16#E#E1                 = 224 (integer literal)
    //   2#1110_0000#            = 224 (integer literal)
    "2#1111_1111#",
    "16#FF#",
    "016#0FF#",
    "16#E#E1",
    "2#1110_0000#",
    // border cases
    detail::to_based_literal(2, std::numeric_limits<uint32_t>::max()),
    detail::to_based_literal(8, std::numeric_limits<uint32_t>::max()),
    detail::to_based_literal(10, std::numeric_limits<uint32_t>::max()),
    detail::to_based_literal(16, std::numeric_limits<uint32_t>::max()),
    detail::to_based_literal(2, std::numeric_limits<uint64_t>::max()),
    detail::to_based_literal(8, std::numeric_limits<uint64_t>::max()),
    detail::to_based_literal(10, std::numeric_limits<uint64_t>::max()),
    detail::to_based_literal(16, std::numeric_limits<uint64_t>::max()),
};

std::vector<ibis::vhdl::intrinsic::unsigned_integer_type> const integer_dec{
    // binary
    0,
    0,
    1,
    1,
    2,
    4,
    // octal
    0,
    1,
    8,
    34,
    1,
    240,
    // hexadecimal LRM examples
    255,
    255,
    255,
    224,
    224,
    // border cases
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    std::numeric_limits<uint64_t>::max(),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(based_literal_integer, utf_data::make(integer_lit) ^ integer_dec, literal, N)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    auto position_proxy = position_cache.add_file("<based_literal/integer>", literal);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx, position_proxy };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);

    using numeric_type_specifier = ibis::vhdl::ast::based_literal::numeric_type_specifier;
    BOOST_REQUIRE(ast_node.numeric_type() == numeric_type_specifier::integer);

    numeric_convert numeric{ diagnostic_handler };
    auto const [conv_ok, value] = numeric(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(std::get<numeric_convert::integer_type>(value) == N);

    os << vhdl::failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << os.str() << "\n\n";
    }
}

//******************************************************************************
// integer based_literal overflow checks
//******************************************************************************
std::vector<std::string> const integer_lit_uint64_ovflw{
    detail::to_based_literal(2, std::numeric_limits<uint64_t>::max(), "_0"),
    detail::to_based_literal(8, std::numeric_limits<uint64_t>::max(), "_0"),
    detail::to_based_literal(10, std::numeric_limits<uint64_t>::max(), "_0"),
    detail::to_based_literal(16, std::numeric_limits<uint64_t>::max(), "_0"),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(based_literal_uint64_ovflw, utf_data::make(integer_lit_uint64_ovflw), literal)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    auto position_proxy = position_cache.add_file("<based_literal/uint64_ovflw>", literal);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx, position_proxy };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);  // must parse ...

    using numeric_type_specifier = ibis::vhdl::ast::based_literal::numeric_type_specifier;
    BOOST_REQUIRE(ast_node.numeric_type() == numeric_type_specifier::integer);

    numeric_convert numeric{ diagnostic_handler };

    bool conv_ok = true;
    std::tie(conv_ok, std::ignore) = numeric(ast_node);
    BOOST_REQUIRE(!conv_ok);  // ... but must fail to convert

    os << vhdl::failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << os.str() << "\n\n";
    }
}

//******************************************************************************
// real based_literal of different bases
//******************************************************************************
std::vector<std::string> const real_lit{
    "10#0.0#", "10#1.0#",
    "10#42.66#e-1",  // based real with allowed negative exponent
    // Examples from
    // - IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    //
    //   16#F.FF#E+2             = 4095.0 (real literal)
    //   2#1.1111_1111_111#E11   = 4095.0 (real literal)
    //
    // Algorithm (in Octave/Matlab):
    // base = 16
    // result = ( ...
    //    hex2dec('F')*base^0  ...
    // + ( ...
    //      hex2dec('F')/base^1 ...
    //    + hex2dec('F')/base^2 ...
    //    ) ...
    // ) * base^2
    "16#F.FF#E+2",            // 4095.0
    "2#1.1111_1111_111#E11",  // 4095.0
};

std::vector<ibis::vhdl::intrinsic::real_type> const real_dec{
    0, 1, 4.266, 4095.0, 4095.0,
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(based_literal_real, utf_data::make(real_lit) ^ real_dec, literal, N)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    auto position_proxy = position_cache.add_file("<based_literal/real>", literal);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx, position_proxy };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);

    using numeric_type_specifier = ibis::vhdl::ast::based_literal::numeric_type_specifier;
    BOOST_REQUIRE(ast_node.numeric_type() == numeric_type_specifier::real);

    numeric_convert numeric{ diagnostic_handler };

    auto const [conv_ok, value] = numeric(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(std::get<numeric_convert::real_type>(value) == N);

    os << vhdl::failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << os.str() << "\n\n";
    }
}

//******************************************************************************
// FAILURE test for binary integer/real based_literal
//******************************************************************************
std::vector<std::string> const lit_failure{
    "3#1111_0000#",              // parse ok, but unsupported base
    "18446744073709551616#42#",  // base numeric overflow
    //"8#42#2147483648"            // exponent numeric overflow
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(based_literal_failure, utf_data::make(lit_failure), literal)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    auto position_proxy = position_cache.add_file("<based_literal/failure>", literal);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx, position_proxy };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);

    numeric_convert numeric{ diagnostic_handler };

    bool conv_ok = true;
    std::tie(conv_ok, std::ignore) = numeric(ast_node);
    BOOST_REQUIRE(!conv_ok);

    os << vhdl::failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << '\n' << os.str() << '\n';
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
