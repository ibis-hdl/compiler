/*
 * on_error_base.hpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_

#include <eda/utils/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/support/context.hpp>
#include <eda/utils/compiler_warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
//#include <eda/vhdl/parser/parser_config.hpp>

#include <type_traits>

#include <eda/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace parser {

/*
 * ToDo: CRTP for parser/semantic error_handler etc. See eclipse/Task
 */
struct on_error_base
{
    template<typename IteratorT, typename ExceptionT, typename ContextT>
    x3::error_handler_result
    on_error(IteratorT& /* first */, IteratorT const& /* last */,
             ExceptionT const& x, ContextT const& context) /* XXX const */
    {
#if 0 /* XXX recursive include problem; parser_config requires on_error definition,
       * but context_type is required here for statis_assert */
        // detect upcoming linker errors, see notes at parser_config.hpp about
        static_assert(
            std::is_same<ContextT, context_type>::value,
            "The Spirit.X3 Context must be equal"
        );
#endif
        std::string message = "Error! Expecting: " + x.which() + " here:";
        auto& error_handler = x3::get<parser::error_handler_tag>(context).get();
        return error_handler(x.where(), message);
    }

};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_ */
