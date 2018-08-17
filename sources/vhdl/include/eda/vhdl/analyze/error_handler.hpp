/*
 * error_handler.hpp
 *
 *  Created on: 16.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_ERROR_HANDLER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_ERROR_HANDLER_HPP_


#include <eda/vhdl/ast/position_cache.hpp>

#include <iosfwd>
#include <string>

#include <eda/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace analyze {


template <typename Iterator>
class error_handler
{
public:
    typedef Iterator                                iterator_type;

public:
    explicit error_handler(
        std::ostream& os_, ast::position_cache<iterator_type>& position_cache_,
        std::string file = "", std::size_t tabs = 4
    )
      : os(os_)
      , position_cache(position_cache_)
      , filename(file)
      , tab_sz(tabs)
    { }

    error_handler(error_handler const&) = delete;
    error_handler& operator=(error_handler const&) = delete;

public:
    void operator()(ast::position_tagged const& where_tag, std::string const& error_message) const;

public:
    std::string file_name() const;

private:
    std::size_t line_number(iterator_type const& iter) const {
    	return position_cache.line_number(iter);
    }

    iterator_type get_line_start(iterator_type& iter) const {
        return position_cache.get_line_start(iter);
    }

    std::string current_line(iterator_type const& start) const {
    	return position_cache.current_line(start);
    }

private:
    std::ostream&                                   os;
    ast::position_cache<iterator_type>&          	position_cache;
    std::string                                     filename;
    std::size_t                                     tab_sz;
};


}}} // namespace eda.vhdl.analyze



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_ERROR_HANDLER_HPP_ */
