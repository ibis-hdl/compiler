//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/basic_ast_walker.hpp>

#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <string_view>
#include <iosfwd>
#include <utility>

namespace ibis::vhdl {
class vhdl_global_context;
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
    using iterator_type = parser::iterator_type;
    using diagnostic_handler_type = vhdl::diagnostic_handler<iterator_type>;

private:
    [[maybe_unused]] std::ostream& os;  // required later on
    std::reference_wrapper<vhdl::vhdl_global_context> ref_vhdl_context;
    std::reference_wrapper<diagnostic_handler_type> ref_diagnostic_handler;

public:
    syntax_worker(std::ostream& os_, vhdl::vhdl_global_context& context,
                  diagnostic_handler_type& diagnostic_handler)
        : os{ os_ }
        , ref_vhdl_context{ std::ref(context) }
        , ref_diagnostic_handler{ std::ref(diagnostic_handler) }
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
    /// FixMe: Reuse of label_match here results into misleading error message
    /// "Label mismatch". Further, the keywords aren't tagged so beauty
    /// error messages aren't possible this way.
    ///
    /// FixMe: pretty error rendering; the error message's node lookup shows the
    /// 1st optional postponed as error location with line number, the 2nd is not rendered.
    ///
    bool keyword_matches(ast::process_statement const& node, std::string_view node_name) const;
};

using syntax_checker = ast::basic_ast_walker<syntax_worker>;

}  // namespace ibis::vhdl::analyze
