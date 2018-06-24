/*
 * parse.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_



#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/parser/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <boost/filesystem/path.hpp>

#include <string>
#include <iosfwd>
#include <functional>


namespace eda { namespace vhdl { namespace parser {


class parse
{
   using error_handler_type = std::function< // FixMe: Wrong Signature
        void(x3::position_tagged, std::string const&)>;

   std::ostream& os;

//    error_handler_type                              error_handler;

public:

    //template <typename ErrorHandler>
    parse(std::ostream& os_/*, ErrorHandler const& error_handler*/)
    : os{ os_ }
//    , error_handler{
//          [&](x3::position_tagged error_position, std::string const& message)
//          { error_handler(error_position, message); }
//    }
    { }

    bool operator()(std::string const &input, ast::design_file& design_file,
                    fs::path const &filename = "") /* const */;

private:
    template <typename ExceptionT>
    std::string make_exception_description(fs::path const &filename,
                                           ExceptionT const& exception) const;
};


} } } // namespace eda.vhdl.parser



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_PARSE_HPP_ */
