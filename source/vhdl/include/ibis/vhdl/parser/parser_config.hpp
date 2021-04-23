#pragma once

#include <ibis/vhdl/parser/error_handler.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/skipper.hpp>

#include <ibis/namespace_alias.hpp>

namespace ibis::vhdl::parser {

using error_handler_type = parser::error_handler<iterator_type>;

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
/// Namely equal of the x3::context  must be
/// - phrase_context_type
/// - iterator_type and
/// - and reference_wrapper<error_handler_type>
///
/// The last is 'const' following the X3 examples (and it compiles/links
/// successfully!), but not here (no idea why).
///
/// Several Q&A regards to linker errors are written on Stack Overflow, e.g.:
///
/// - [linking errors while separate parser using boost spirit x3](
///    https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3?answertab=active#tab-top)
/// - [x3 linker error with separate TU](
///    https://stackoverflow.com/questions/43791079/x3-linker-error-with-separate-tu?answertab=active#tab-top)
/// - [Mixing non-terminal rules from separeted translation unit](
///    https://stackoverflow.com/questions/66036568/mixing-non-terminal-rules-from-separeted-translation-unit)
///
/// but none pointed out the reference_wrapper<error_handler_type> problem
/// faced here.
///
/// So, finally the performed check at handle_on_error class isn't a right place
/// to check the equality, but here we can get both contexts. Further,
/// using boost.type_index the concrete type can be printed there:
///
/// @code{.cpp}
/// std::cout << "\nContext is of Type:\n"
///           << boost::typeindex::type_id<Context>().pretty_name() << '\n';
/// std::cout << "\nConfigured Context is of Type:\n"
///           << boost::typeindex::type_id<context_type>().pretty_name() << '\n';
/// @endcode
///
/// At this time, the context is of type:
///
/// @code{.cpp}
/// x3::context<
///     x3::error_handler_tag,
///     std::reference_wrapper<
///         x3::error_handler<std::string::const_iterator>
///     >, // ... and (even it should) *not*: > const,
///     x3::context<
///         x3::skipper_tag,
///         x3::rule<ibis::vhdl::parser::skipper_class, x3::unused_type, false> const,
///         x3::unused_type
///     >
/// >
/// @endcode
///
/// @todo The using type alias should be:
/// `x3::context<error_handler_tag,
///             std::reference_wrapper<error_handler_type> const, phrase_context_type>`
using context_type = x3::context<parser::error_handler_tag,
                                 std::reference_wrapper<error_handler_type>, phrase_context_type>;

}  // namespace ibis::vhdl::parser
