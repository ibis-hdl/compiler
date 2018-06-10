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

#include <map>


namespace boost { namespace spirit { namespace x3 {

/* FixMe: Quick & Dirty Fix; No Idea what happened here, but I get a compiler
 * error from <.../boost/optional/detail/optional_aligned_storage.hpp>
 *
 * error: invalid application of 'sizeof' to an incomplete type
 *        'boost::spirit::x3::error_handler_tag'
 * char data[ sizeof(T) ];
 *            ^~~~~~~~~
 * The problem began to rise up by using annotate_on_success() and
 * handle_on_error().
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
    std::string which{ x.which() };
    auto iter = m_ruleid_map.find(which);

    if (iter != m_ruleid_map.end())
        which = iter->second;

    std::string const message{
        "Parser Error: Expecting the VHDL-BNF rule: '" + which + "' here:"
    };

    auto& error_handler = x3::get<x3::error_handler_tag>(context).get();
    error_handler(x.where(), message);

    return x3::error_handler_result::fail;
}


}}} // namespace eda.vhdl.parser


#endif /* INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_ */
