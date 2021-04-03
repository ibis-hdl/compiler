#pragma once

#include <eda/vhdl/parser/parser_config.hpp>

#include <iosfwd>
#include <string>
#include <string_view>
#include <exception>

namespace eda::vhdl::ast {

struct design_file;

}

namespace eda::vhdl::parser {

class parse {
public:
    ///
    /// @brief Construct a new parse object.
    ///
    /// @param os_ Output stream for messagenges.
    /// @param error_handler_ The error handler for parser errors.
    ///
    /// FixMe: Signature should be
    /// ```parse(std::ostream& os_, error_handler_type const& error_handler_)```
    ///
    parse(std::ostream& os_, error_handler_type& error_handler_)
        : os{ os_ }
        , error_handler{ error_handler_ }
    {
    }

    ///
    /// @brief Functor to call parse implementation.
    ///
    /// @param input File contents to be parsed.
    /// @param design_file AST node of input/file contents.
    /// @return true success.
    /// @return false failure.
    ///
    /// FixMe: Signature should be ```bool operator()(std::string const& input, ast::design_file&
    /// design_file) const```
    bool operator()(std::string const& input, ast::design_file& design_file);

private:
    static std::string make_exception_description(std::exception const& exception,
                                                  std::string_view filename);

    static std::string make_exception_description(std::string_view filename);

private:
    std::ostream& os;
    parser::error_handler_type& error_handler;  // should be const reference
};

}  // namespace eda::vhdl::parser
