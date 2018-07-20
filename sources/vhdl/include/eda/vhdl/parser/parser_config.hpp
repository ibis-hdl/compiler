/*
 * parser_config.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL_PARSER_CONFIG_HPP_
#define INCLUDE_EDA_VHDL_PARSER_CONFIG_HPP_

#include <eda/vhdl/parser/common_types.hpp>     // iterator_type
#include <eda/vhdl/parser/skipper.hpp>
#include <eda/vhdl/parser/error_handler.hpp>

#include <eda/namespace_alias.hpp>


/* Note about linker errors:
 *
 * The context shall be equal between parser and one configured by the user
 * at parser_config.hpp. Otherwise linker errors will occur if the rules
 * have external translation units (use of BOOST_SPIRIT_INSTANTIATE).
 *
 * Namely equal of the x3::context  must be
 * - phrase_context_type
 * - iterator_type and
 * - and reference_wrapper<error_handler_type>
 *
 * The last is 'const' following the X3 examples (and it compiles/links
 * successfully!), but not here (no idea why).
 *
 * Several Q&A are written on Stack Overflow:
 *
 * - [linking errors while separate parser using boost spirit x3](
 *    https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3?answertab=active#tab-top)
 * - [x3 linker error with separate TU](
 *    https://stackoverflow.com/questions/43791079/x3-linker-error-with-separate-tu?answertab=active#tab-top)
 *
 * but none pointed out the reference_wrapper<error_handler_type> problem
 * faced here.
 *
 * So, finally the performed check at handle_on_error class isn't a right place
 * to check the equality, but here we can get both contexts. Further,
 * using boost.type_index the concrete type can be printed there:
 *
 * \code{.cpp}
 * std::cout << "\nContext is of Type:\n"
 *           << boost::typeindex::type_id<Context>().pretty_name() << "\n";
 * std::cout << "\nConfgured Context is of Type:\n"
 *           << boost::typeindex::type_id<context_type>().pretty_name() << "\n";
 * \endcode
 *
 * At this time, the context is of type:
 *
 * \code{.cpp}
 * x3::context<
 *     x3::error_handler_tag,
 *     std::reference_wrapper<
 *         x3::error_handler<std::string::const_iterator>
 *     >, // ... and not: > const,
 *     x3::context<
 *         x3::skipper_tag,
 *         x3::rule<eda::vhdl::parser::skipper_class, x3::unused_type, false> const,
 *         x3::unused_type
 *     >
 * >
 * \endcode
 */

namespace eda { namespace vhdl { namespace parser {


typedef parser::error_handler<iterator_type>            error_handler_type;

typedef x3::phrase_parse_context<skipper_type>::type    phrase_context_type;

// used for external linkage
typedef x3::context<
      parser::error_handler_tag
    , std::reference_wrapper<error_handler_type> /* const */
    , phrase_context_type
>                                                       context_type;


}}}  // namespace eda.vhdl.parser



#endif /* INCLUDE_EDA_VHDL_PARSER_CONFIG_HPP_ */
