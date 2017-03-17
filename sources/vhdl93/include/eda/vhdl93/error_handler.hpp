/*
 * error_handler.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL93_ERROR_HANDLER_HPP_
#define INCLUDE_EDA_VHDL93_ERROR_HANDLER_HPP_


#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp> // error_handler_result

#include <map>


namespace eda { namespace vhdl93 {

    namespace x3 = boost::spirit::x3;

    // Error Handler Utility
    template <typename Iterator>
    using error_handler = x3::error_handler<Iterator>;


    using error_handler_tag = x3::error_handler_tag;


    struct error_handler_base
    {
        error_handler_base();

        template <typename Iterator, typename Exception, typename Context>
        x3::error_handler_result on_error(
            Iterator& first, Iterator const& last
          , Exception const& x, Context const& context);

        std::map<std::string, std::string> const m_ruleid_map;
    };
}}


/*
 * Implementation
 */
namespace eda { namespace vhdl93 {


namespace x3 = boost::spirit::x3;


template <typename Iterator, typename Exception, typename Context>
inline x3::error_handler_result
error_handler_base::on_error(
      Iterator& first, Iterator const& last
    , Exception const& x, Context const& context)
{
    std::string which = x.which();
    auto iter = m_ruleid_map.find(which);

    if (iter != m_ruleid_map.end())
        which = iter->second;

    std::string message = "Error! Expecting: " + which + " here:";

    auto& error_handler = x3::get<error_handler_tag>(context).get();
    error_handler(x.where(), message);

    return x3::error_handler_result::fail;
}


}}




#endif /* INCLUDE_EDA_VHDL93_ERROR_HANDLER_HPP_ */
