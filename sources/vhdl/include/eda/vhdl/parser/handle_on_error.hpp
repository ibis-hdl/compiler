/*
 * error_handler.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_
#define INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_


#include <eda/util/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp> // error_handler_result
#include <eda/util/compiler_warnings_on.hpp>

#include <eda/vhdl/parser/parser_config.hpp> // context_type

#include <map>


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
        std::is_same_v<Context, context_type>,
        "The Spirit.X3 Context must be equal"
    );

    return x3::error_handler_result::fail;
}


}}} // namespace eda.vhdl.parser


#endif /* INCLUDE_EDA_VHDL_HANDLE_ON_ERROR_HPP_ */
