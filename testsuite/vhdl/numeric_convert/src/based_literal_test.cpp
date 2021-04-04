#include <testsuite/vhdl_numeric_convert/numeric_parser.hpp>
#include <testsuite/vhdl_numeric_convert/binary_string.hpp>

#include <eda/vhdl/ast/node/based_literal.hpp>
#include <eda/vhdl/ast/numeric_convert.hpp>
#include <eda/vhdl/parser/position_cache.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>
#include <eda/vhdl/type.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <boost/core/ignore_unused.hpp>

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
    using namespace testsuite::vhdl_numeric_convert::util;

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
            // no assert, write marker
            ss << "INVALID BASE SPECIFIER" << base;
            std::cerr << ">>>>> ERROR in function: " << __FUNCTION__ << "(), unexpected base "
                      << base << " <<<<<\n";
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

namespace  // anonymous
{

// The numeric_convert utility writes messages, but concrete error messages
// aren't checked. For debugging is useful to see them otherwise. Switch to
// ostream sink to hide them or let's write to cerr to see them.
// Note, using global numeric_convert object tests  implicit of state less
// conversion, otherwise test must fail due to. */
//
// Note: technically, we initialize globals that access extern objects,
// and therefore can lead to order-of-initialization problems.

bool constexpr no_messages = true;

// NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init)
auto const numeric_convert = []() {
    if constexpr (no_messages) {
        static btt::output_test_stream nil_sink;
        return ast::numeric_convert{ nil_sink };
    }
    else {
        return ast::numeric_convert(std::cerr);
    }
}();

}  // namespace

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

std::vector<eda::vhdl::intrinsic::unsigned_integer_type> const integer_dec{
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
    std::size_t const id = position_cache.add_file("<based_literal>", literal);
    auto const position_proxy{ position_cache.handle(id) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(value == N);
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
    std::size_t const id = position_cache.add_file("<based_literal>", literal);
    auto const position_proxy{ position_cache.handle(id) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy);
    BOOST_REQUIRE(parse_ok);  // must parse ...

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(!conv_ok);  // ... but must fail to convert

    boost::ignore_unused(value);
}

//******************************************************************************
// real based_literal of different bases
//******************************************************************************
std::vector<std::string> const real_lit{
    "10#0.0#", "10#1.0#", "10#42.66#e-1",
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

std::vector<eda::vhdl::intrinsic::real_type> const real_dec{
    0, 1, 4.266, 4095.0, 4095.0,
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(based_literal_real, utf_data::make(real_lit) ^ real_dec, literal, N)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    std::size_t const id = position_cache.add_file("<based_literal>", literal);
    auto const position_proxy{ position_cache.handle(id) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(value == N);
}

//******************************************************************************
// FAILURE test for binary integer/real based_literal
//******************************************************************************
std::vector<std::string> const lit_failure{
    "3#1111_0000#",  // parse ok, but unsupported base
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(based_literal_failure, utf_data::make(lit_failure), literal)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    std::size_t const id = position_cache.add_file("<based_literal>", literal);
    auto const position_proxy{ position_cache.handle(id) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.based_literal(position_proxy);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(!conv_ok);

    boost::ignore_unused(value);
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
