/*
 * error_handler.hpp
 *
 *  Created on: 18.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ERROR_HANDLER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ERROR_HANDLER_HPP_

#include <eda/vhdl/parser/position_cache.hpp>

#include <eda/utils/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp> // error_handler_result
#include <eda/utils/compiler_warnings_on.hpp>

#include <iosfwd>
#include <string>

#include <eda/namespace_alias.hpp>

#include <boost/type_index.hpp>


namespace eda { namespace vhdl { namespace parser {


// tag used to get our error handler from the x3::context
struct error_handler_tag;


template <typename Iterator>
class error_handler
{
public:

    typedef Iterator                                iterator_type;
    typedef boost::iterator_range<iterator_type>    range_type;

    typedef x3::error_handler_result                result_type;

public:
    error_handler(
        std::ostream& os_, position_cache<iterator_type>& position_cache_,
        std::string file = "", unsigned tabs = 4
    )
      : os(os_)
      , position_cache(position_cache_)
      , filename(file)
      , tab_sz(tabs)
    { }

public:
    template <typename NodeT>
    void tag(NodeT& node, iterator_type first, iterator_type last)
    {
//        std::cout << "error_handler::tag<"
//                  << boost::typeindex::type_id<NodeT>().pretty_name()
//                  << ">\n";
        position_cache.annotate(node, first, last);
    }

#if 0
public:
    // AST error handler (original signature)
    result_type operator()(
        ast::position_tagged const& where_tag, std::string const& message) const;

    // AST error handler
    result_type operator()(
        ast::position_tagged const& where_tag, std::string const& which_rule,
        std::string const& message) const;

public:
    result_type operator()(
        range_type  const& where, std::string const& which_rule,
        std::string const& error_message) const;

    result_type operator()(
        range_type const& where, std::string const& error_message) const;

    // non-AST error handler
    result_type operator()(
        iterator_type const& err_pos, std::string const& error_message) const;
#else
public:
    // AST/parse related error handler (original signature)
    result_type operator()(
        iterator_type err_pos, std::string const& error_message) const;

public:
    // working on tagged AST
    result_type operator()(
        ast::position_tagged const& where_tag, std::string const& error_message) const;


#endif

public:
    std::string const& file_name() const { return filename; }

private:
    // helper functions
    void print_file_line(iterator_type const& iter) const;
    void print_line(iterator_type start, iterator_type const& last) const;
    void print_indicator(iterator_type& first, iterator_type const& last, char indicator) const;
    void skip_whitespace(iterator_type& err_pos, iterator_type const& last) const;
    Iterator get_line_start(iterator_type first, iterator_type const& pos) const;

private:
    std::ostream&                                   os;
    position_cache<iterator_type>&                  position_cache;
    std::string                                     filename;
    unsigned                                        tab_sz;
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ERROR_HANDLER_HPP_ */
