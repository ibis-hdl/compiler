#pragma once

#include <eda/vhdl/parser/error_handler.hpp>  // IWYU pragma: keep

#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp>

#include <eda/namespace_alias.hpp>  // IWYU pragma: keep

#include <string>
#include <string_view>

namespace eda::vhdl::parser {
struct error_handler_tag;
}

namespace eda::vhdl::parser {

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
        // FixMe: recursive include problem; parser_config requires on_error definition,
        // but context_type is required here for statis_assert */
        //
        // if constexpr (false /* disabled */) {
        //     // detect upcoming linker errors, see notes at parser_config.hpp about
        //     static_assert(
        //         std::is_same_v<ContextT, context_type>,
        //         "The Spirit.X3 Context must be equal"
        //     );
        // }

        auto& error_handler = x3::get<parser::error_handler_tag>(context).get();
        return error_handler(x.where(), make_error_description(x.which()));
    }

private:
    /**
     * lookup a parser rule name for a useful name used for error message
     * construction.
     *
     * @param which The spirit.x3 BNF rule name.
     * @return Beautified name of the rule.
     */
    static std::string_view lookup(std::string_view which);

    /**
     * Make a error description based on spirit.x3 BNF rule name.
     *
     * @param which The spirit.x3 BNF rule name.
     * @return An parser error message.
     */
    static std::string make_error_description(std::string_view which);
};

}  // namespace eda::vhdl::parser
