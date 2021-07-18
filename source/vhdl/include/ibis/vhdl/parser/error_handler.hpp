#pragma once

#include <ibis/vhdl/parser/diagnostic_handler.hpp>  // IWYU pragma: keep

#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <string>
#include <string_view>

namespace ibis::vhdl::parser {
///
/// Base class for all AST nodes where the parser error handler can be called.
///
/// This is called directly by Boost.Spirit X3 in case of parser error.
///
/// @todo This concept allows also to have different error handling strategies
/// depending on concrete rule ID, for more see [Custom error on rule level? #657](
///  https://github.com/boostorg/spirit/issues/657).
/// This may be used to get more detailed informations on which concrete BNF rule has
/// thrown the exception, since the X3 context contains only the tags - in these
/// days:
/// @code
/// context<
///     parser::diagnostic_handler_tag, ...,
///     context<parser::position_cache_tag, ...,
///         context<skipper_tag, ..., unused_type>
///     >
/// >
/// @endcode
/// It would be nice to get these information, e.g. on missing ';', not only the
/// error position in (single line) source context. Maybe the rule name can be gathered
/// using ``get_info<T> { std::string operator()(T const&)``,
/// see [Spirit X3, Is this error handling approach useful?](
/// https://stackoverflow.com/questions/57048008/spirit-x3-is-this-error-handling-approach-useful/57067207#57067207)
///
class error_handler {
public:
    ///
    /// @brief Handle Spirit X3's expectation errors.
    ///
    /// @tparam IteratorT Iterator type of the parser
    /// @tparam ContextT Boost.Spirit X3 context type
    /// @param first Iterator to the begin of somewhat, unused
    /// @param last  Iterator to the end of somewhat, unused
    /// @param e Boost.Spirit X3 x3::expectation_failure<IteratorT> exception
    /// @param context Boost.Spirit X3 context
    /// @return x3::diagnostic_handler_result
    ///
    /// @todo recursive include problem; `parser_config` requires on_error definition,
    /// but context_type is required here for `static_assert`. Hence there is no static
    /// assert possible here even if it would be useful.
    /// @code
    ///     // detect upcoming linker errors, see notes at parser_config.hpp about
    ///     static_assert(
    ///         std::is_same_v<ContextT, context_type>,
    ///         "The Spirit.X3 Context must be equal"
    ///     );
    /// @endcode
    ///
    /// @todo Check [Custom error on rule level?
    /// #657](https://github.com/boostorg/spirit/issues/657)
    ///
    template <typename IteratorT, typename ContextT>
    x3::error_handler_result on_error([[maybe_unused]] IteratorT& first,
                                      [[maybe_unused]] IteratorT const& last,
                                      x3::expectation_failure<IteratorT> const& e,
                                      ContextT const& context) const
    {
        auto& diagnostic_handler = x3::get<parser::diagnostic_handler_tag>(context).get();

        using error_type = typename vhdl::diagnostic_handler<IteratorT>::error_type;
        auto constexpr parser_error = error_type::parser;

        diagnostic_handler(e.where(), make_error_description(e.which()), parser_error);

        // FixMe: just here as "concept" marker, but untested by testsuite yet.
        if (e.which() == "';'") {
            // adavance iter after the error occurred, the error is registered above
            first = e.where();
            return x3::error_handler_result::accept;
        }

        return x3::error_handler_result::fail;
    }

private:
    ///
    /// lookup a parser rule name for a useful name used for error message
    /// construction.
    ///
    /// @param which The spirit.x3 BNF rule name.
    /// @return Beautified name of the rule.
    ///
    static std::string_view lookup(std::string_view which);

    ///
    /// Make a error description based on spirit.x3 BNF rule name.
    ///
    /// @param which The spirit.x3 BNF rule name.
    /// @return An parser error message.
    ///
    static std::string make_error_description(std::string_view which);
};

}  // namespace ibis::vhdl::parser
