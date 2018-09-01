/*
 * parse.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_


#include <eda/vhdl/parser/parser_config.hpp>

#include <string>
#include <iosfwd>

namespace eda {
namespace vhdl {
namespace ast {
    struct design_file;
} // namesapce ast
} // namespace vhdl
} // namespace eda

namespace eda { namespace vhdl { namespace parser {


class parse
{
   std::ostream& os;

   parser::error_handler_type /*const*/&                error_handler;

public:

    parse(std::ostream& os_, error_handler_type /*const*/& error_handler_)
    : os{ os_ }
    , error_handler{ error_handler_ }
    { }

    bool operator()(std::string const &input, ast::design_file& design_file) /* const */;

private:
    template <typename ExceptionT>
    std::string make_exception_description(std::string const &filename,
                                           ExceptionT const& exception) const;
};


} } } // namespace eda.vhdl.parser



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_ */
