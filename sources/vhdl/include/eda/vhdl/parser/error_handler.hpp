/*
 * error_handler.hpp
 *
 *  Created on: 18.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ERROR_HANDLER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ERROR_HANDLER_HPP_

#include <eda/vhdl/parser/position_cache.hpp>

#include <eda/util/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/auxiliary/guard.hpp> // error_handler_result
#include <eda/util/compiler_warnings_on.hpp>

#include <iosfwd>
#include <string>

#include <eda/namespace_alias.hpp>


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
        std::string file = "", std::size_t tabs = 4
    )
      : os(os_)
      , position_cache(position_cache_)
      , filename(file)
      , tab_sz(tabs)
    { }

public:
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type const& first, iterator_type const& last)
    {
        position_cache.annotate(node, first, last);
    }

public:
    result_type operator()(
        iterator_type err_pos, std::string const& error_message) const;

public:
    result_type operator()(
        ast::position_tagged const& where_tag, std::string const& error_message) const;

public:
    std::string file_name() const;

private:
    std::size_t line_number(iterator_type const& iter) const;
    Iterator get_line_start(iterator_type& pos_iter) const;
    void print_line(iterator_type const& start, iterator_type const& last) const;
    void print_indicator(iterator_type& first, iterator_type const& last, char symbol) const;

private:
    std::ostream&                                   os;
    position_cache<iterator_type>&                  position_cache;
    std::string                                     filename;
    std::size_t                                     tab_sz;
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ERROR_HANDLER_HPP_ */
