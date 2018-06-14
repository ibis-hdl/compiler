/*
 * error_handler.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_
#define INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_

/* special boost.spirit.x3 header to get rid off the annoying unused parameter
 * warnings from x3 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp> // error_handler_result
#pragma GCC diagnostic pop

#include <eda/vhdl/parser/namespace_alias.hpp>
#include <eda/vhdl/parser/parser_config.hpp> // context_type

#include <map>


namespace boost { namespace spirit { namespace x3 {

/* FixMe: Quick & Dirty Fix; No Idea what happened here, but I get a compiler
 * error from <.../boost/optional/detail/optional_aligned_storage.hpp>
 *
 * error: invalid application of 'sizeof' to an incomplete type
 *        'boost::spirit::x3::error_handler_tag'
 * char data[ sizeof(T) ];
 *            ^~~~~~~~~
 *
 * The problem began to rise up by using annotate_on_success() and
 * handle_on_error(). Maybe a dismiss as ADL inflicted.
 */
struct error_handler_tag {};

} } }


namespace eda { namespace vhdl { namespace parser {


struct handle_on_error
{
    handle_on_error();

    template <typename Iterator, typename Exception, typename Context>
    x3::error_handler_result on_error(
        Iterator& first, Iterator const& last
      , Exception const& x, Context const& context);

    std::string assemble_message(std::string which);

    std::map<std::string, std::string> const m_ruleid_map;
};


}}} // namespace eda.vhdl.parser


/*
 * Implementation
 */
namespace eda { namespace vhdl { namespace parser {


template <typename Iterator, typename Exception, typename Context>
inline x3::error_handler_result
handle_on_error::on_error(
      Iterator& /* first */, Iterator const& /* last */
    , Exception const& x, Context const& context)
{
    std::string const message{ assemble_message(x.which()) };

    auto& error_handler = x3::get<x3::error_handler_tag>(context).get();
    error_handler(x.where(), message);

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
     * successfully), but not here (no idea why).
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
     * So, finally these isn't a good place to check the equality, but here we
     * can get both contexts. Further, using boost.type_index the concrete type
     * can be printed:
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
     *     >, // ... and not > const,
     *     x3::context<
     *         x3::skipper_tag,
     *         x3::rule<eda::vhdl::parser::skipper_class, x3::unused_type, false> const,
     *         x3::unused_type
     *     >
     * >
     * \endcode
     */
    static_assert(
        std::is_same<Context, context_type>::value,
        "The Spirit.X3 Context must be equal"
    );

    return x3::error_handler_result::fail;
}


}}} // namespace eda.vhdl.parser


#endif /* INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_ */
