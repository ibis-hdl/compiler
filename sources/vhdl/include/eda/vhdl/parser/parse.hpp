/*
 * parse.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_


#include <string>
#include <iosfwd>

#include <boost/filesystem/path.hpp>

#include <eda/vhdl/parser/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace ast {

struct design_file;

} } } // namespace eda.vhdl.ast


namespace eda { namespace vhdl { namespace parser {


class parse
{
    std::ostream& os;
public:

    parse(std::ostream& os_);

    bool operator()(std::string const &input, ast::design_file& design_file,
                    fs::path const &filename = "") /* const */;

private:
    template <typename ExceptionT>
    std::string make_exception_description(fs::path const &filename,
                                           ExceptionT const& exception) const;
};


} } } // namespace eda.vhdl.parser



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_ */
