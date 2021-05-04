#pragma once

// C++
#include <algorithm>
#include <bitset>
#include <optional>
#include <iomanip>
#include <sstream>
#include <string>

// Boost
#include <boost/range/iterator_range.hpp>

#include <boost/spirit/home/x3/char.hpp>
#include <boost/spirit/home/x3/nonterminal.hpp>
#include <boost/spirit/home/x3/numeric.hpp>
#include <boost/spirit/home/x3/operator.hpp>
#include <boost/spirit/home/x3/string.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
