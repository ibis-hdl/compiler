//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/skipper.hpp>

#include <ibis/namespace_alias.hpp>

namespace ibis::vhdl::parser {

// using iterator_type = parser::iterator_type;
using position_annotator_type = parser::position_cache<iterator_type>::annotator;
using diagnostic_handler_type = parser::diagnostic_handler<iterator_type>;

using phrase_context_type = x3::phrase_parse_context<skipper_type>::type;

///
/// @brief Context used for external linkage
///
/// Note about linker errors:
///
/// The context shall be equal between parser and one configured by the user
/// at parser_config.hpp. Otherwise linker errors will occur if the rules
/// have external translation units (use of BOOST_SPIRIT_INSTANTIATE).
///
/// Several Q&A regards to linker errors are written on Stack Overflow, e.g.:
///
/// - [What are contexts in boost spirit X3?](
///    https://stackoverflow.com/questions/66393775/what-are-contexts-in-boost-spirit-x3)
/// - [Boost spirit x3 example calculator (calc8, calc9) linker error](
///    https://stackoverflow.com/questions/51627938/boost-spirit-x3-example-calculator-calc8-calc9-linker-error/51641878#51641878)
/// - [X3: Linker Error (unresolved external symbol “parse_rule”) on nonterminal parser](
///     https://stackoverflow.com/questions/50277979/x3-linker-error-unresolved-external-symbol-parse-rule-on-nonterminal-parser/50301865#50301865)
/// - [linking errors while separate parser using boost spirit x3](
///    https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3?answertab=active#tab-top)
/// - [x3 linker error with separate TU](
///    https://stackoverflow.com/questions/43791079/x3-linker-error-with-separate-tu?answertab=active#tab-top)
/// - [Mixing non-terminal rules from separated translation unit](
///    https://stackoverflow.com/questions/66036568/mixing-non-terminal-rules-from-separeted-translation-unit)
///
/// Using boost.type_index the concrete type can be printed there:
///
/// @code{.cpp}
/// std::cout << "\nContext is of Type:\n"
///           << boost::typeindex::type_id<Context>().pretty_name() << '\n';
/// std::cout << "\nConfigured Context is of Type:\n"
///           << boost::typeindex::type_id<context_type>().pretty_name() << '\n';
/// @endcode
///
/// @todo Report a bug: It's curious, since e.g. ```parse.cpp``` instantiate the parser as:
/// @code{.cpp}
/// x3::with<parser::annotator_tag>(std::ref(position_cache_proxy))[
///     x3::with<parser::diagnostic_handler_tag>(std::ref(diagnostic_handler))[
///         parser::grammar()
///     ]
/// ];
/// @endcode
/// naturally the ```context_type``` here should be in the same order
/// @code{.cpp}
/// x3::context<
///     parser::annotator_tag,
///     std::reference_wrapper<parser::position_annotator_type>,
///     x3::context<
///         parser::diagnostic_handler_tag,
///         std::reference_wrapper<parser::diagnostic_handler_type>,
///         phrase_context_type
///     >
/// >;
/// @endcode
/// **but** the ```context_type``` must be in another order to avoid
/// linker errors - see below!
///

// clang-format off
using context_type =
    x3::context<
        parser::diagnostic_handler_tag,
        std::reference_wrapper<parser::diagnostic_handler_type>,
        x3::context<
            parser::annotator_tag,
            std::reference_wrapper<parser::position_annotator_type>,
            phrase_context_type
        >
    >;
// clang-format on

}  // namespace ibis::vhdl::parser
