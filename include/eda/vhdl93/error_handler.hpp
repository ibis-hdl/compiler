/*
 * error_handler.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL93_ERROR_HANDLER_HPP_
#define INCLUDE_EDA_VHDL93_ERROR_HANDLER_HPP_


//#include <boost/locale/encoding_utf.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
//#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
//#include <ostream>
//#include <sstream>


namespace eda { namespace vhdl93 {

    namespace x3 = boost::spirit::x3;

    // Error Handler Utility
    template <typename Iterator>
    using error_handler = x3::error_handler<Iterator>;


    // tag used to get our error handler from the context
    using error_handler_tag = x3::error_handler_tag;


    struct error_handler_base
    {
        template <typename Iterator, typename Exception, typename Context>
        x3::error_handler_result on_error(
            Iterator& first, Iterator const& last
          , Exception const& x, Context const& context)
        {
            std::string message = "Error! Expecting: " + x.which() + " here:";
            auto& error_handler = x3::get<error_handler_tag>(context).get();
            error_handler(x.where(), message);
            return x3::error_handler_result::fail;
        }
    };
}}


#endif /* INCLUDE_EDA_VHDL93_ERROR_HANDLER_HPP_ */
