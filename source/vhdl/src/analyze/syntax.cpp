//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/analyze/syntax.hpp>
#include <ibis/vhdl/analyze/diagnostic_handler.hpp>
#include <ibis/vhdl/analyze/check/label_match.hpp>

#include <ibis/vhdl/ast/node/architecture_body.hpp>
#include <ibis/vhdl/ast/node/block_statement.hpp>
#include <ibis/vhdl/ast/node/case_statement.hpp>
#include <ibis/vhdl/ast/node/configuration_declaration.hpp>
#include <ibis/vhdl/ast/node/entity_declaration.hpp>
#include <ibis/vhdl/ast/node/generate_statement.hpp>
#include <ibis/vhdl/ast/node/if_statement.hpp>
#include <ibis/vhdl/ast/node/loop_statement.hpp>
#include <ibis/vhdl/ast/node/package_body.hpp>
#include <ibis/vhdl/ast/node/package_declaration.hpp>
#include <ibis/vhdl/ast/node/process_statement.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

#include <ibis/vhdl/ast/pretty_node_name.hpp>

#include <ibis/vhdl/context.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <fmt/format.h>

#include <sstream>
#include <utility>
#include <iostream>

namespace {

/// FixMe: This is hot fix for gathering non-tagged AST nodes and give an expressive
/// error message; diagnostic_handler simply assert without node name.
auto const tagged_diag = [](auto const& where_tag, [[maybe_unused]] auto const& start_label,
                            [[maybe_unused]] auto const& end_label) {
    if (!where_tag.is_tagged()) {
        std::cerr << (fmt::format("Node '{0}' not tagged\n",  // --
                      ibis::util::pretty_typename<decltype(where_tag)>().str()));
    }
};

}  // namespace

namespace ibis::vhdl::analyze {

bool syntax_worker::success() const { return context.error_free(); }

template <typename NodeT>
bool syntax_worker::label_matches(NodeT const& node, std::string_view node_name) const
{
    using boost::locale::format;
    using boost::locale::translate;

    label_match const check_label{};
    auto const match_result = check_label(node);

    // all went fine
    if (match_result == label_match::result::OK) {
        return true;
    }

    // failure diagnostic to user
    // @todo Check, if label_of alway return valid (non empty) ast::identifier, even on ill-formed
    // nodes. diagnostic_handler::syntax_error() doesn't care about!

    auto const [start_label, end_label] = labels_of(node);
    node_name = ast::pretty_node_name(node_name);

    tagged_diag(node, start_label, end_label);

    switch (match_result) {
        case label_match::result::MISMATCH: {
            auto const err_msg =  // --
                (format(translate("Label mismatch in {1}")) % node_name).str();
            diagnostic_handler.syntax_error(node, start_label, end_label, err_msg);
            return false;
        }

        case label_match::result::ILLFORMED: {
            auto const err_msg =  // --
                (format(translate("Label ill-formed in {1}")) % node_name).str();
            diagnostic_handler.syntax_error(node, start_label, end_label, err_msg);
            return false;
        }

        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }

    cxx_unreachable_bug_triggered();
}

bool syntax_worker::keyword_matches(ast::process_statement const& node,
                                    std::string_view node_name) const
{
    // Note: Re-Using label_match here results into misleading error message
    //       "Label mismatch". Further, the keywords aren't tagged so beauty
    //       error messages aren't possible this way.
    // FixMe: pretty error rendering; the error message's node lookup shows the
    // 1st optional postponed as error location with line number, the 2nd is not rendered.

    using boost::locale::format;
    using boost::locale::translate;

    if (!node.postponed && node.end_postponed) {
        node_name = ast::pretty_node_name(node_name);

        auto const err_msg =  // --
            (format(translate("ill-formed statement in {1}; "
                              "(Hint: single trailing keyword 'postponed')"))  //--
             % node_name)
                .str();
        diagnostic_handler.syntax_error(node, err_msg);

        return false;
    }

    return true;
}

void syntax_worker::operator()(ast::architecture_body const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::block_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::case_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::configuration_declaration const& node,
                               std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::entity_declaration const& node,
                               std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::generate_statement const& node,
                               std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::if_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::loop_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::package_body const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::package_declaration const& node,
                               std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(ast::process_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
    keyword_matches(node, node_name);  // check postponed
}

}  // namespace ibis::vhdl::analyze
