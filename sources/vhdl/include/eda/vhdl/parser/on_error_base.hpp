/*
 * on_error_base.hpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_

#include <eda/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3/support/context.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
//#include <eda/vhdl/parser/parser_config.hpp>
//#include <type_traits>

#include <string>
#include <string_view>
#include <unordered_map>

#include <eda/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace parser {


class on_error_base
{
public:
    template<typename IteratorT, typename ExceptionT, typename ContextT>
    x3::error_handler_result
    on_error(IteratorT& /* first */, IteratorT const& /* last */,
             ExceptionT const& x, ContextT const& context) /* XXX const */
    {
#if 0 /* XXX recursive include problem; parser_config requires on_error definition,
       * but context_type is required here for statis_assert */
        // detect upcoming linker errors, see notes at parser_config.hpp about
        static_assert(
            std::is_same_v<ContextT, context_type>,
            "The Spirit.X3 Context must be equal"
        );
#endif
        auto& error_handler = x3::get<parser::error_handler_tag>(context).get();
        return error_handler(x.where(), make_error_description(x.which()));
    }

    std::string_view lookup(std::string_view which) const
    {
        auto const iter = ruleid_map.find(which);

        if (iter != ruleid_map.end()) {
           	return iter->second;
        }
        return which;
    }

    std::string make_error_description(std::string_view which) const;

private:
    typedef std::unordered_map<
    	std::string_view, std::string_view> 		rule_map_type;

    static const rule_map_type						ruleid_map;
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_ */
