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
#include <eda/utils/compiler_push.hpp>
#include <eda/utils/compiler_warning.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp> // error_handler_result
#include <eda/utils/compiler_pop.hpp>

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

    std::string make_error_description(std::string which);

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
    std::string const message{ make_error_description(x.which()) };

    auto& error_handler = x3::get<x3::error_handler_tag>(context).get();
    error_handler(x.where(), message);

    // detect upcoming linker errors, see notes at parser_config.hpp about
    static_assert(
        std::is_same<Context, context_type>::value,
        "The Spirit.X3 Context must be equal"
    );

    return x3::error_handler_result::fail;
}


}}} // namespace eda.vhdl.parser


#endif /* INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_ */
