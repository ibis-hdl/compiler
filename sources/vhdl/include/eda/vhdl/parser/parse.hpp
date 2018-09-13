/*
 * parse.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_

#include <eda/vhdl/parser/parser_config.hpp>

#include <iosfwd>
#include <string>
#include <exception>

namespace eda {
namespace vhdl {
namespace ast {

struct design_file;

} // namespace ast
} // namespace vhdl
} // namespace eda

namespace eda {
namespace vhdl {
namespace parser {

class parse {
public:
    parse(std::ostream& os_, error_handler_type /*const*/& error_handler_)
        : os{ os_ }
        , error_handler{ error_handler_ }
    {
    }

    bool operator()(std::string const& input, ast::design_file& design_file) /* const */;

private:
    std::string make_exception_description(
        std::exception const& exception, std::string const& filename) const;

    std::string make_exception_description(std::string const& filename) const;

private:
    // clang-format off
    std::ostream&                                   os;
    parser::error_handler_type /*const*/&           error_handler;
    // clang-format on
};

} // namespace parser
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_ */
