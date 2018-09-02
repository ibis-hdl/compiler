/*
 * error_handler.hpp
 *
 *  Created on: 16.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_ERROR_HANDLER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_ERROR_HANDLER_HPP_


#include <eda/vhdl/ast/position_cache.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>

#include <iosfwd>
#include <string>

#include <eda/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace analyze {


/**
 * Syntax/Semantic error handler.
 *
 * Opposite to the pasrer::error_handler, this error handler works on AST/Tree
 * level. All informations tagged at parse time are required for diagnostics.
 * Therefore the ast::position_cache is required. Also the API is slightly
 * different.
 *
 * \todo Get "access" to information of node/rule map at parser::on_error_base
 */
template <typename Iterator>
class error_handler
{
public:
    using iterator_type = Iterator;

public:
    /**
     * Construct a Syntax/Semantic error handler.
     *
     * @param os_             Stream to write error and diagnostic messages.
     * @param position_cache_ Reference to the ast::position_cache.
     * @param tabs            Tabulator size, required for correct rendering of
     *                        source code snippet.
     */
    explicit error_handler(
        std::ostream& os_, ast::position_cache<iterator_type>& position_cache_,
        std::size_t tabs = 4
    )
      : os{ os_ }
      , position_cache{ position_cache_ }
      , tab_sz{ tabs }
    { }

    ~error_handler() = default;

    error_handler(error_handler const&) = delete;
    error_handler& operator=(error_handler const&) = delete;

    error_handler(error_handler&&) = delete;
    error_handler& operator=(error_handler&&) = delete;

public:
    /**
     * Handle a syntax/semantic error at node and render the diagnostic message
     * error_message.
     *
     * @param where_tag     The node, which triggers the error
     * @param error_message The information error message.
     */
    void operator()(ast::position_tagged const& where_tag, std::string const& error_message) const;

    /**
     *  Handle a syntax/semantic error at node and render the diagnostic message
     * error_message. This is a special overload for label pairs.
     *
     * @param where_tag     The node, which triggers the error.
     * @param start_label   The start label of the where_tag node.
     * @param end_label     The complementary end label of the where_tag node.
     * @param error_message The information error message.
     */
    void operator()(ast::position_tagged const& where_tag,
                    ast::position_tagged const& start_label, ast::position_tagged const& end_label,
                    std::string const& error_message) const;

private:
    // clang-format off
    std::ostream&                                   os;
    ast::position_cache<iterator_type>&             position_cache;
    std::size_t                                     tab_sz;
    // clang-format on
};


using error_handler_type = error_handler<parser::iterator_type>;


}}} // namespace eda.vhdl.analyze



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_ERROR_HANDLER_HPP_ */
