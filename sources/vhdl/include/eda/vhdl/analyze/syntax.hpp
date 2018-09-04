/*
 * syntax.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_

#include <eda/vhdl/ast.hpp> // XXX forward

#include <eda/vhdl/ast/basic_ast_walker.hpp>
#include <eda/vhdl/context.hpp>
#include <eda/vhdl/analyze/error_handler.hpp>

#include <iosfwd>
#include <string_view>

namespace eda {
namespace vhdl {
namespace analyze {

class syntax_worker {
public:
    syntax_worker(
        std::ostream& os_, vhdl::context& context_, analyze::error_handler_type& error_handler_)
        : os{ os_ }
        , context{ context_ }
        , error_handler{ error_handler_ }
    {
    }

public:
    bool success() const;

    bool failures() const { return !success(); }

public:
    void operator()(ast::architecture_body const& node, std::string_view const& node_name) const;
    void operator()(ast::block_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::case_statement const& node, std::string_view const& node_name) const;
    void operator()(
        ast::configuration_declaration const& node, std::string_view const& node_name) const;
    void operator()(ast::entity_declaration const& node, std::string_view const& node_name) const;
    void operator()(ast::generate_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::if_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::loop_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::package_body const& node, std::string_view const& node_name) const;
    void operator()(ast::package_declaration const& node, std::string_view const& node_name) const;
    void operator()(ast::process_statement const& node, std::string_view const& node_name) const;

    template <typename NodeT>
    void operator()(NodeT const& /*unused*/, std::string_view const& /*unused*/) const
    {
    }

private:
    template <typename NodeT>
    bool label_matches(NodeT const& node, std::string_view const& node_name) const;

private:
    // format-clang off
    std::ostream& os;
    vhdl::context& context;
    analyze::error_handler_type& error_handler;
    // format-clang on
};

using syntax_checker = ast::basic_ast_walker<syntax_worker>;

} // namespace analyze
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_ */
