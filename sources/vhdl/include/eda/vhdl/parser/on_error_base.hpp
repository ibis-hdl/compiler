/*
 * on_error_base.hpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_

#include <eda/vhdl/parser/error_handler.hpp>

// clang-format off
#include <eda/compiler/warnings_off.hpp> // IWYU pragma: keep
#include <boost/spirit/home/x3/support/context.hpp>
#include <eda/compiler/warnings_on.hpp>  // IWYU pragma: keep
// clang-format on

#include <string>
#include <string_view>
#include <unordered_map>

#include <eda/namespace_alias.hpp> // IWYU pragma: keep

namespace eda {
namespace vhdl {
namespace parser {

/**
 * Base class for all AST nodes where the parser error handler can be called.
 *
 * This is called directly by spirit.X3 in case of parser error.
 */
class on_error_base {
public:
    template <typename IteratorT, typename ExceptionT, typename ContextT>
    x3::error_handler_result on_error(IteratorT& /* first */, IteratorT const& /* last */,
        ExceptionT const& x, ContextT const& context) const
    {
#if 0 /* XXX recursive include problem; parser_config requires on_error definition,                \
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

    /**
     * lookup a parser rule name for a useful name used for error message
     * construction.
     *
     * @param which The spirit.x3 BNF rule name.
     * @return Beautified name of the rule.
     */
    std::string_view lookup(std::string_view which) const
    {
        auto const iter = ruleid_map.find(which);

        if (iter != ruleid_map.end()) {
            return iter->second;
        }
        return which;
    }

    /**
     * Make a error description based on spirit.x3 BNF rule name.
     *
     * @param which The spirit.x3 BNF rule name.
     * @return An parser error message.
     */
    std::string make_error_description(std::string_view which) const;

private:
    using rule_map_type = std::unordered_map<std::string_view, std::string_view>;

    // clang-format off
    static const rule_map_type                        ruleid_map;
    // clang-format on
};

} // namespace parser
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_ERROR_BASE_HPP_ */
