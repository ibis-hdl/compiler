#pragma once

#include <eda/vhdl/ast/basic_ast_walker.hpp>

#include <eda/vhdl/analyze/error_handler.hpp>

#include <string_view>
#include <iosfwd>

namespace eda::vhdl {
class context;
}
namespace eda::vhdl::ast {
struct architecture_body;
struct block_statement;
struct case_statement;
struct configuration_declaration;
struct entity_declaration;
struct generate_statement;
struct if_statement;
struct loop_statement;
struct package_body;
struct package_declaration;
struct process_statement;
}  // namespace eda::vhdl::ast

namespace eda::vhdl::analyze {

class syntax_worker {
public:
    syntax_worker(std::ostream& os_, vhdl::context& context_,
                  analyze::error_handler_type& error_handler_)
        : os{ os_ }
        , context{ context_ }
        , error_handler{ error_handler_ }
    {
    }

public:
    bool success() const;

    bool failures() const { return !success(); }

public:
    void operator()(ast::architecture_body const& node, std::string_view node_name) const;
    void operator()(ast::block_statement const& node, std::string_view node_name) const;
    void operator()(ast::case_statement const& node, std::string_view node_name) const;
    void operator()(ast::configuration_declaration const& node, std::string_view node_name) const;
    void operator()(ast::entity_declaration const& node, std::string_view node_name) const;
    void operator()(ast::generate_statement const& node, std::string_view node_name) const;
    void operator()(ast::if_statement const& node, std::string_view node_name) const;
    void operator()(ast::loop_statement const& node, std::string_view node_name) const;
    void operator()(ast::package_body const& node, std::string_view node_name) const;
    void operator()(ast::package_declaration const& node, std::string_view node_name) const;
    void operator()(ast::process_statement const& node, std::string_view node_name) const;

    template <typename NodeT>
    void operator()(NodeT const& /*unused*/, std::string_view /*unused*/) const
    {
    }

private:
    template <typename NodeT>
    bool label_matches(NodeT const& node, std::string_view node_name) const;

    bool keyword_matches(ast::process_statement const& node, std::string_view node_name) const;

private:
    std::ostream& os;  // unused, required later on
    vhdl::context& context;
    analyze::error_handler_type& error_handler;
};

using syntax_checker = ast::basic_ast_walker<syntax_worker>;

}  // namespace eda::vhdl::analyze
