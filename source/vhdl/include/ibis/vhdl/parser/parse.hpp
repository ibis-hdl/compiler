#pragma once

#include <ibis/vhdl/parser/parser_config.hpp>

#include <iosfwd>
#include <string>
#include <string_view>
#include <exception>

namespace ibis::vhdl::ast {

struct design_file;

}

namespace ibis::vhdl::parser {

class parse {
public:
    ///
    /// Construct a new parse object.
    ///
    /// @param os_ Output stream for messages.
    /// @param error_handler_ The error handler for parser errors.
    ///
    /// @todo Signature should be:
    /// `parse(std::ostream& os_, error_handler_type const& error_handler_);`
    ///
    parse(std::ostream& os_, error_handler_type& error_handler_)
        : os{ os_ }
        , error_handler{ error_handler_ }
    {
    }

    ///
    /// Functor to call parse implementation.
    ///
    /// @param input File contents to be parsed.
    /// @param design_file AST node of input/file contents.
    /// @return true success.
    /// @return false failure.
    ///
    /// @todo Signature should be:
    /// `bool operator()(std::string const& input, ast::design_file& design_file) const;`
    ///
    /// @todo Get rid off the skipper, embed it into own rule and new start
    /// rule, see e.g. [Best practice for boost spirit context-dependent grammar rule](
    /// https://stackoverflow.com/questions/66963381/best-practice-for-boost-spirit-context-dependent-grammar-rule)
    /// X3: Function Composition.
    ///
    /// @todo Limit the use og `x3::rule<>`, following [Spirit X3, How to get attribute type to
    /// match rule type?](
    /// https://stackoverflow.com/questions/56819120/spirit-x3-how-to-get-attribute-type-to-match-rule-type/56824271#56824271)
    /// this is only required if you have recursive rules or need external linkage
    /// on rules (define them in separate translation units).
    ///
    bool operator()(std::string_view input, ast::design_file& design_file);

private:
    static std::string make_exception_description(std::exception const& exception,
                                                  std::string_view filename);

    static std::string make_exception_description(std::string_view filename);

private:
    std::ostream& os;
    parser::error_handler_type& error_handler;  // should be const reference
};

}  // namespace ibis::vhdl::parser
