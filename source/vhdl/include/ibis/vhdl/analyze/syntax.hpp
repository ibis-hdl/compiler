//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/basic_ast_walker.hpp>

#include <ibis/vhdl/analyze/diagnostic_handler.hpp>

#include <string_view>
#include <iosfwd>

namespace ibis::vhdl {
class context;
}
namespace ibis::vhdl::ast {
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
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::analyze {

class syntax_worker {
public:
    syntax_worker(std::ostream& os_, vhdl::context& context_,
                  analyze::diagnostic_handler_type& diagnostic_handler_)
        : os{ os_ }
        , context{ context_ }
        , diagnostic_handler{ diagnostic_handler_ }
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
    void operator()([[maybe_unused]] NodeT const&, [[maybe_unused]] std::string_view) const
    {
    }

private:
    template <typename NodeT>
    bool label_matches(NodeT const& node, std::string_view node_name) const;

    ///
    /// Check the matching keyword.
    ///
    /// FixMe: Re-Using label_match here results into misleading error message
    /// "Label mismatch". Further, the keywords aren't tagged so beauty
    /// error messages aren't possible this way.
    ///
    /// FixMe: pretty error rendering; the error message's node lookup shows the
    /// 1st optional postponed as error location with line number, the 2nd is not rendered.
    ///
    bool keyword_matches(ast::process_statement const& node, std::string_view node_name) const;

private:
    std::ostream& os;  // unused, required later on
    vhdl::context& context;
    analyze::diagnostic_handler_type& diagnostic_handler;
};

using syntax_checker = ast::basic_ast_walker<syntax_worker>;

}  // namespace ibis::vhdl::analyze
