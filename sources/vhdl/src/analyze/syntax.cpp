/*
 * syntax.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/analyze/syntax.hpp>

#include <eda/vhdl/analyze/check/label_match.hpp>
#include <eda/vhdl/ast/pretty_node_name.hpp>

#include <eda/support/boost/locale.hpp>

#include <eda/util/cxx_bug_fatal.hpp>

#include <iostream>

namespace eda {
namespace vhdl {
namespace analyze {

bool syntax_worker::success() const { return context.error_count == 0; }

template <typename NodeT>
bool syntax_worker::label_matches(NodeT const& node, std::string_view node_name) const
{
    label_match check_label{};

    using boost::locale::format;
    using boost::locale::translate;
    using ast::pretty_node_name;

    switch (check_label(node)) {
        case label_match::result::OK:
            return true;

        case label_match::result::MISMATCH: {
            auto[start_label, end_label] = labels_of(node);
            error_handler(node, start_label, end_label,
                // clang-format off
                (format(translate(
                    "Label mismatch in {1}"
                    ))
                    % pretty_node_name(node_name)
                ).str()
                // clang-format on
            );
            ++context.error_count;
            return false;
        }

        case label_match::result::ILLFORMED: {
            auto[start_label, end_label] = labels_of(node);
            error_handler(node, start_label, end_label,
                // clang-format off
                (format(translate(
                    "Label ill-formed in {1}"
                    ))
                    % pretty_node_name(node_name)
                ).str()
                // clang-format on
            );
            ++context.error_count;
            return false;
        }

        default:
            cxx_unreachable_bug_triggered();
    }
    cxx_unreachable_bug_triggered();
}

bool syntax_worker::keyword_matches(ast::process_statement const& node, std::string_view node_name) const {

    // Note: Re-Using label_match here results into misleading error message
    //       "Label mismatch". Further, the keywords aren't tagged so beauty
    //       error messages arn't possible this way.

    // FixMe: pretty error rendering

    using boost::locale::format;
    using boost::locale::translate;
    using ast::pretty_node_name;

    if (!node.postponed && node.end_postponed) {
        error_handler(node,
            // clang-format off
            (format(translate(
                "ill-formed statement in {1}; (Hint: single trailing keyword 'postponed')"
                ))
                % pretty_node_name(node_name)
            ).str()
            // clang-format on
        );
        ++context.error_count;
        return false;
    }

    return true;
}

void syntax_worker::operator()(
    ast::architecture_body const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::block_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::case_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::configuration_declaration const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::entity_declaration const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::generate_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::if_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::loop_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::package_body const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::package_declaration const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
}

void syntax_worker::operator()(
    ast::process_statement const& node, std::string_view node_name) const
{
    label_matches(node, node_name);
    keyword_matches(node, node_name);   // check postponed
}

} // namespace analyze
} // namespace vhdl
} // namespace eda
