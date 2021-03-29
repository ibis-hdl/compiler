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
    parse(std::ostream& os_, error_handler_type /*const*/& error_handler_)
        : os{ os_ }
        , error_handler{ error_handler_ }
    {
    }

    bool operator()(std::string const& input, ast::design_file& design_file) /* const */;

private:
    static std::string make_exception_description(std::exception const& exception,
                                                  std::string_view filename);

    static std::string make_exception_description(std::string_view filename);

private:
    std::ostream& os;
    parser::error_handler_type /*const*/& error_handler;
};

}  // namespace eda::vhdl::parser
