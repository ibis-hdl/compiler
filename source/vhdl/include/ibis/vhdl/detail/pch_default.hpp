#pragma once

// Std C++
#include <iosfwd>
#include <iostream>
#include <limits>
#include <optional>
#include <string_view>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// Boost
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <boost/range/iterator_range.hpp>
// <boost/range/iterator_range_hash.hpp> results into error: redefinition of 'hash_value'
#include <boost/functional/hash.hpp>

// The header <boost/spirit/home/x3/auxiliary.hpp>, which includes the problematic header
// <boost/spirit/home/x3/auxiliary/any_parser.hpp>, runs into compile problems due to Spirit X3's
// `move_to` traits. Even forwarding of enum class AST's `keyword_token` doesn't helped here.
#include <boost/spirit/home/x3/char.hpp>
#include <boost/spirit/home/x3/nonterminal.hpp>
#include <boost/spirit/home/x3/numeric.hpp>
#include <boost/spirit/home/x3/operator.hpp>
#include <boost/spirit/home/x3/string.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
