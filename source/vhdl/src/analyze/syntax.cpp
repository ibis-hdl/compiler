#include <eda/vhdl/analyze/syntax.hpp>
#include <eda/vhdl/analyze/error_handler.hpp>
#include <eda/vhdl/analyze/check/label_match.hpp>

#include <eda/vhdl/ast/node/architecture_body.hpp>
#include <eda/vhdl/ast/node/block_statement.hpp>
#include <eda/vhdl/ast/node/case_statement.hpp>
#include <eda/vhdl/ast/node/configuration_declaration.hpp>
#include <eda/vhdl/ast/node/entity_declaration.hpp>
#include <eda/vhdl/ast/node/generate_statement.hpp>
#include <eda/vhdl/ast/node/if_statement.hpp>
#include <eda/vhdl/ast/node/loop_statement.hpp>
#include <eda/vhdl/ast/node/package_body.hpp>
#include <eda/vhdl/ast/node/package_declaration.hpp>
#include <eda/vhdl/ast/node/process_statement.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

#include <eda/vhdl/ast/pretty_node_name.hpp>

#include <eda/vhdl/context.hpp>

#include <eda/util/cxx_bug_fatal.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <sstream>
#include <utility>

namespace eda::vhdl::analyze {

bool syntax_worker::success() const { return context.error_count == 0; }

template <typename NodeT>
bool syntax_worker::label_matches(NodeT const& node, std::string_view node_name) const
{
    // FixMe: Generally here, if pretty_node_name lookup failed, give a warning to developer

    label_match check_label{};

    using ast::pretty_node_name;
    using boost::locale::format;
    using boost::locale::translate;

    switch (check_label(node)) {
        case label_match::result::OK:
            return true;

        case label_match::result::MISMATCH: {
            auto const [start_label, end_label] = labels_of(node);
            auto const [found, node_name_sv] = pretty_node_name(node_name);

            error_handler(node, start_label, end_label,
                          (format(translate("Label mismatch in {1}"))  // --
                           % node_name_sv)                             // {1}
                              .str());

            ++context.error_count;

            return false;
        }

        case label_match::result::ILLFORMED: {
            auto const [start_label, end_label] = labels_of(node);
            auto const [found, node_name_sv] = pretty_node_name(node_name);

            error_handler(node, start_label, end_label,
                          (format(translate("Label ill-formed in {1}"))  // --
                           % node_name_sv)                               // {1}
                              .str());

            ++context.error_count;

            return false;
        }

        default:
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
    // FixMe: pretty error rendering

    // FixMe: If pretty_node_name lookup failed, give a warning to user/developer

    using ast::pretty_node_name;
    using boost::locale::format;
    using boost::locale::translate;

    if (!node.postponed && node.end_postponed) {
        auto const [found, node_name_sv] = pretty_node_name(node_name);

        error_handler(node, (format(translate("ill-formed statement in {1}; "
                                              "(Hint: single trailing keyword 'postponed')"))  //--
                             % node_name_sv)  // {1}
                                .str());

        ++context.error_count;

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

}  // namespace eda::vhdl::analyze
