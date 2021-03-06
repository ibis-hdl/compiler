//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/vhdl/ast.hpp>

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <ibis/util/overloaded.hpp>  // IWYU pragma: keep

#include <ibis/util/cxx_bug_fatal.hpp>

namespace ibis::vhdl::ast {

printer::printer(std::ostream& os_, uint16_t start_indent)
    : os{ os_, start_indent }
{
}

class printer::scope_printer {
public:
    scope_printer(util::indent_ostream& os_, std::string_view name_, bool verbose_,
                  std::string_view name_pfx = std::string_view{})
        : os{ os_ }
        , name{ name_ }
        , verbose{ verbose_ }
    {
        if (verbose) {
            os << util::increase_indent << "(";
            os << name;
            if (!name_pfx.empty()) {
                os << "<" << name_pfx << ">";
            }
            os << '\n';
        }
    }

    ~scope_printer()
    {
        if (verbose) {
            os << util::decrease_indent << "\n)";
        }
    }

    scope_printer(const scope_printer&) = delete;
    scope_printer& operator=(scope_printer const&) = delete;
    scope_printer(scope_printer&&) = delete;
    scope_printer& operator=(scope_printer&&) = delete;

private:
    util::indent_ostream& os;
    std::string_view const name;
    bool const verbose;
};

template <typename T, typename Enable>
struct printer::symbol_scope : public scope_printer {
    symbol_scope(printer& root, std::string_view name)
        : scope_printer(root.os, name, root.verbose_symbol)
    {
    }
};

template <typename T>
struct printer::symbol_scope<T, typename std::enable_if_t<x3::traits::is_variant<T>::value>>
    : public printer::scope_printer {
    symbol_scope(printer& root, std::string_view name)
        : scope_printer(root.os, name, root.verbose_variant, "v")
    {
    }
};

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::ast {

void printer::operator()(abstract_literal const& node)
{
    static const std::string_view symbol{ "abstract_literal" };
    symbol_scope<abstract_literal> _(*this, symbol);
    visit(node);
}

void printer::operator()(access_type_definition const& node)
{
    static const std::string_view symbol{ "access_type_definition" };
    symbol_scope<access_type_definition> _(*this, symbol);
    (*this)(node.subtype_indication);
}

void printer::operator()(actual_designator const& node)
{
    static const std::string_view symbol{ "actual_designator" };
    symbol_scope<actual_designator> _(*this, symbol);
    visit(node);
}

void printer::operator()(actual_part const& node)
{
    static const std::string_view symbol{ "actual_part" };
    symbol_scope<actual_part> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::actual_part_chunk const& chunk) {
            (*this)(chunk.context_tied_name);
            os << '\n';
            (*this)(chunk.actual_designator);
        },
        [this](ast::actual_designator const& node_) {
            (*this)(node_);
        }
    }, node);
    // clang-format on
}

void printer::operator()(aggregate const& node)
{
    static const std::string_view symbol{ "aggregate" };
    symbol_scope<aggregate> _(*this, symbol);

    // FixMe: CheckMe - this visitation looks strange!
    // Unmodified source (tag R2018) runs in 2021 fine
    // but some case fail, e.g. aggregate/aggregate_00{1,2,3,6}
    // It looks for an infinity recursive call here!
    // [BNF](https://www.vhdl-online.de/vhdl_reference_93/aggregates)
    // states: ( element_association { , element_association } )
    visit(node);
}

void printer::operator()(alias_declaration const& node)
{
    static const std::string_view symbol{ "alias_declaration" };
    symbol_scope<alias_declaration> _(*this, symbol);

    (*this)(node.alias_designator);
    os << '\n';

    if (node.subtype_indication) {
        (*this)(*node.subtype_indication);
        os << '\n';
    }

    (*this)(node.name);

    if (node.signature) {
        os << '\n';
        (*this)(*node.signature);
    }
}

void printer::operator()(alias_designator const& node)
{
    static const std::string_view symbol{ "alias_designator" };
    symbol_scope<alias_designator> _(*this, symbol);
    visit(node);
}

void printer::operator()(allocator const& node)
{
    static const std::string_view symbol{ "allocator" };
    symbol_scope<allocator> _(*this, symbol);
    visit(node);
}

void printer::operator()(architecture_body const& node)
{
    static const std::string_view symbol{ "architecture_body" };
    symbol_scope<architecture_body> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';

    (*this)(node.entity_name);
    os << '\n';

    if (!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << '\n';
    }

    if (!node.statement_part.empty()) {
        (*this)(node.statement_part);
        os << '\n';
    }

    if (node.end_identifier) {
        (*this)(*node.end_identifier);
    }
}

void printer::operator()(architecture_statement_part const& node)
{
    static const std::string_view symbol{ "architecture_statement_part" };
    symbol_scope<architecture_statement_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(array_type_definition const& node)
{
    static const std::string_view symbol{ "array_type_definition" };
    symbol_scope<array_type_definition> _(*this, symbol);
    visit(node);
}

void printer::operator()(assertion const& node)
{
    static const std::string_view symbol{ "assertion" };
    symbol_scope<assertion> _(*this, symbol);

    (*this)(node.condition);

    if (node.report) {
        static const std::string_view symbol{ "assertion.report" };
        os << '\n';
        symbol_scope<assertion> _(*this, symbol);
        (*this)(*node.report);
    }
    if (node.severity) {
        static const std::string_view symbol{ "assertion.severity" };
        os << '\n';
        symbol_scope<assertion> _(*this, symbol);
        (*this)(*node.severity);
    }
}

void printer::operator()(assertion_statement const& node)
{
    static const std::string_view symbol{ "assertion_statement" };
    symbol_scope<assertion_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }
    (*this)(node.assertion);
}

void printer::operator()(association_element const& node)
{
    static const std::string_view symbol{ "association_element" };
    symbol_scope<association_element> _(*this, symbol);

    if (node.formal_part) {
        (*this)(*node.formal_part);
        os << '\n';
    }
    (*this)(node.actual_part);
}

void printer::operator()(association_list const& node)
{
    static const std::string_view symbol{ "association_list" };
    symbol_scope<association_list> _(*this, symbol);

    visit(node);
}

void printer::operator()(attribute_declaration const& node)
{
    static const std::string_view symbol{ "attribute_declaration" };
    symbol_scope<attribute_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';
    (*this)(node.type_mark);
}

void printer::operator()(attribute_name const& node)
{
    static const std::string_view symbol{ "attribute_name" };
    symbol_scope<attribute_name> _(*this, symbol);

    (*this)(node.prefix);

    if (node.signature) {
        os << '\n';
        (*this)(*node.signature);
    }

    os << '\n';
    {  // no own type, printing here
        static const std::string_view symbol{ "attribute_designator" };
        symbol_scope<attribute_name> _(*this, symbol);

        (*this)(node.attribute_designator);
    }

    if (node.expression) {
        os << '\n';
        (*this)(*node.expression);
    }
}

void printer::operator()(attribute_specification const& node)
{
    static const std::string_view symbol{ "attribute_specification" };
    symbol_scope<attribute_specification> _(*this, symbol);

    {
        static const std::string_view symbol{ "attribute_designator" };
        symbol_scope<based_literal> _(*this, symbol);
        (*this)(node.attribute_designator);
    }

    os << '\n';
    (*this)(node.entity_specification);

    os << '\n';
    (*this)(node.expression);
}

void printer::operator()(based_literal const& node)
{
    static const std::string_view symbol{ "based_literal" };
    symbol_scope<based_literal> _(*this, symbol);

    os << "base: " << node.base << ", "
       << "integer: " << node.number.integer_part;

    if (!node.number.fractional_part.empty()) {
        os << ", fraction: " << node.number.fractional_part;
    }

    if (!node.number.exponent.empty()) {
        os << ", exp: " << node.number.exponent;
    }

    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

    os << ", type: ";
    switch (node.numeric_type()) {
        case numeric_type_specifier::integer: {
            os << "integer";
            break;
        }
        case numeric_type_specifier::real: {
            os << "real";
            break;
        }
        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
}

void printer::operator()(binding_indication const& node)
{
    static const std::string_view symbol{ "binding_indication" };
    symbol_scope<binding_indication> _(*this, symbol);

    if (node.entity_aspect) {
        (*this)(*node.entity_aspect);
        os << '\n';
    }

    (*this)(node.generic_map_aspect);
    os << '\n';
    (*this)(node.port_map_aspect);
}

void printer::operator()(bit_string_literal const& node)
{
    static const std::string_view symbol{ "bit_string_literal" };
    symbol_scope<bit_string_literal> _(*this, symbol);

    using base_specifier = bit_string_literal::base_specifier;

    os << "base: ";

    switch (node.base_type) {
        case base_specifier::bin:
            os << "bin";
            break;
        case base_specifier::oct:
            os << "oct";
            break;
        case base_specifier::hex:
            os << "hex";
            break;
        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }

    os << ", literal: " << node.literal;
}

void printer::operator()(block_configuration const& node)
{
    static const std::string_view symbol{ "block_configuration" };
    symbol_scope<block_configuration> _(*this, symbol);

    (*this)(node.block_specification);
    os << '\n';

    {
        static const std::string_view symbol{ "use_clause*" };
        symbol_scope<block_configuration> _(*this, symbol);
        visit(node.use_clause_list);
    }

    os << '\n';

    {
        static const std::string_view symbol{ "configuration_item*" };
        symbol_scope<block_configuration> _(*this, symbol);
        visit(node.configuration_item_list);
    }
}

void printer::operator()(block_declarative_item const& node)
{
    static const std::string_view symbol{ "block_declarative_item" };
    symbol_scope<block_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(block_declarative_part const& node)
{
    static const std::string_view symbol{ "block_declarative_part" };
    symbol_scope<block_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(block_header const& node)
{
    static const std::string_view symbol{ "block_header" };
    symbol_scope<block_header> _(*this, symbol);

    if (node.generic_part) {
        auto const& generic_part = *node.generic_part;
        (*this)(generic_part.generic_clause);
        if (generic_part.generic_map_aspect) {
            os << '\n';
            (*this)(*generic_part.generic_map_aspect);
        }
    }

    if (node.port_part) {
        auto const& port_part = *node.port_part;
        if (node.generic_part) {
            os << '\n';
        }
        (*this)(port_part.port_clause);
        if (port_part.port_map_aspect) {
            os << '\n';
            (*this)(*port_part.port_map_aspect);
        }
    }
}

void printer::operator()(block_specification const& node)
{
    static const std::string_view symbol{ "block_specification" };
    symbol_scope<block_specification> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded{
        [this](ast::name const& name) { (*this)(name); },
        [this](ast::block_specification_chunk const& chunk) {
            (*this)(chunk.label);
            if (chunk.index_specification) {
                os << '\n';
                (*this)(*chunk.index_specification);
            }
        },
        [this](ast::nullary const& nullary) { (*this)(nullary); }
    }, node);
    // clang-format on
}

void printer::operator()(block_statement const& node)
{
    static const std::string_view symbol{ "block_statement" };
    symbol_scope<block_statement> _(*this, symbol);

    (*this)(node.label);
    os << '\n';

    if (node.guard_expression) {
        (*this)(*node.guard_expression);
        os << '\n';
    }

    if (node.header.generic_part || node.header.port_part) {
        (*this)(node.header);
        os << '\n';
    }

    if (!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << '\n';
    }

    if (!node.statement_part.empty()) {
        (*this)(node.statement_part);
        os << '\n';
    }

    if (node.end_label) {
        (*this)(*node.end_label);
    }
}

void printer::operator()(block_statement_part const& node)
{
    static const std::string_view symbol{ "block_statement_part" };
    symbol_scope<block_statement_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(case_statement const& node)
{
    static const std::string_view symbol{ "case_statement" };
    symbol_scope<case_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    (*this)(node.expression);
    os << '\n';

    {
        static const std::string_view symbol{ "case_statement_alternative*" };
        symbol_scope<block_statement_part> _(*this, symbol);
        visit(node.alternatives);
    }

    if (node.end_label) {
        os << '\n';
        (*this)(*node.end_label);
    }
}

void printer::operator()(case_statement_alternative const& node)
{
    static const std::string_view symbol{ "case_statement_alternative" };
    symbol_scope<case_statement_alternative> _(*this, symbol);

    (*this)(node.choices);
    os << '\n';
    (*this)(node.sequence_of_statements);
}

void printer::operator()(character_literal const& node)
{
    static const std::string_view symbol{ "character_literal" };
    symbol_scope<character_literal> _(*this, symbol);

    os << "'" << node.literal << "'";
}

void printer::operator()(choice const& node)
{
    static const std::string_view symbol{ "choice" };
    symbol_scope<choice> _(*this, symbol);
    visit(node);
}

void printer::operator()(choices const& node)
{
    static const std::string_view symbol{ "choices" };
    symbol_scope<choices> _(*this, symbol);
    visit(node);
}

void printer::operator()(component_configuration const& node)
{
    static const std::string_view symbol{ "component_configuration" };
    symbol_scope<component_configuration> _(*this, symbol);

    (*this)(node.component_specification);

    if (node.binding_indication) {
        os << '\n';
        (*this)(*node.binding_indication);
    }

    if (node.block_configuration) {
        os << '\n';
        (*this)(*node.block_configuration);
    }
}

void printer::operator()(component_declaration const& node)
{
    static const std::string_view symbol{ "component_declaration" };
    symbol_scope<component_declaration> _(*this, symbol);

    (*this)(node.identifier);

    if (node.local_generic_clause) {
        os << '\n';
        (*this)(*node.local_generic_clause);
    }

    if (node.local_port_clause) {
        os << '\n';
        (*this)(*node.local_port_clause);
    }

    if (node.name) {
        os << '\n';
        (*this)(*node.name);
    }
}

void printer::operator()(component_instantiation_statement const& node)
{
    static const std::string_view symbol{ "component_instantiation_statement" };
    symbol_scope<component_instantiation_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    (*this)(node.instantiated_unit);

    if (node.generic_map_aspect) {
        os << '\n';
        (*this)(*node.generic_map_aspect);
    }

    if (node.port_map_aspect) {
        os << '\n';
        (*this)(*node.port_map_aspect);
    }
}

void printer::operator()(component_specification const& node)
{
    static const std::string_view symbol{ "component_specification" };
    symbol_scope<component_specification> _(*this, symbol);

    (*this)(node.instantiation_list);
    os << '\n';
    (*this)(node.component_name);
}

void printer::operator()(composite_type_definition const& node)
{
    static const std::string_view symbol{ "composite_type_definition" };
    symbol_scope<composite_type_definition> _(*this, symbol);
    visit(node);
}

void printer::operator()(concurrent_assertion_statement const& node)
{
    static const std::string_view symbol{ "concurrent_assertion_statement" };
    symbol_scope<concurrent_assertion_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
    }

    if (node.postponed) {
        os << "\nPOSTPONED,";
    }

    if (node.label || node.postponed) {
        os << '\n';
    }
    (*this)(node.assertion);
}

void printer::operator()(concurrent_procedure_call_statement const& node)
{
    static const std::string_view symbol{ "concurrent_procedure_call_statement" };
    symbol_scope<concurrent_procedure_call_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
    }

    if (node.postponed) {
        os << "\nPOSTPONED,";
    }

    if (node.label || node.postponed) {
        os << '\n';
    }
    (*this)(node.procedure_call);
}

void printer::operator()(concurrent_signal_assignment_statement const& node)
{
    static const std::string_view symbol{ "concurrent_signal_assignment_statement" };
    symbol_scope<concurrent_signal_assignment_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
    }

    if (node.postponed) {
        os << "\nPOSTPONED,";
    }

    if (node.label || node.postponed) {
        os << '\n';
    }

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::conditional_signal_assignment const& signal_assignment) {
            (*this)(signal_assignment);
        },
        [this](ast::selected_signal_assignment const& signal_assignment) {
            (*this)(signal_assignment);
        }
    }, node.signal_assignment);
    // clang-format on
}

void printer::operator()(concurrent_statement const& node)
{
    static const std::string_view symbol{ "concurrent_statement" };
    symbol_scope<concurrent_statement> _(*this, symbol);
    visit(node);
}

void printer::operator()(condition_clause const& node)
{
    static const std::string_view symbol{ "condition_clause" };
    symbol_scope<condition_clause> _(*this, symbol);
    (*this)(node.condition);
}

void printer::operator()(conditional_signal_assignment const& node)
{
    static const std::string_view symbol{ "conditional_signal_assignment" };
    symbol_scope<conditional_signal_assignment> _(*this, symbol);

    (*this)(node.target);
    os << '\n';

    if (node.options.delay_mechanism || node.options.guarded) {
        (*this)(node.options);
        os << '\n';
    }

    (*this)(node.conditional_waveforms);
}

void printer::operator()(conditional_waveforms const& node)
{
    static const std::string_view symbol{ "conditional_waveforms" };
    symbol_scope<conditional_waveforms> _(*this, symbol);

    // mark empty chunks doesn't make sense here
    if (!node.chunks.empty()) {
        std::size_t const N = node.chunks.size() - 1;
        std::size_t i = 0;
        for (auto const& chunk : node.chunks) {
            (*this)(chunk.waveform);
            os << ",\n";
            (*this)(chunk.condition);
            if (i++ != N) {
                os << ",\n";
            }
        }
        os << '\n';
    }

    (*this)(node.waveform);

    if (node.condition) {
        os << '\n';
        (*this)(*node.condition);
    }
}

void printer::operator()(configuration_declaration const& node)
{
    static const std::string_view symbol{ "configuration_declaration" };
    symbol_scope<configuration_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';

    (*this)(node.entity_name);
    os << '\n';

    if (!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << '\n';
    }

    (*this)(node.block_configuration);

    if (node.end_identifier) {
        os << '\n';
        (*this)(*node.end_identifier);
    }
}

void printer::operator()(configuration_declarative_item const& node)
{
    static const std::string_view symbol{ "configuration_declarative_item" };
    symbol_scope<configuration_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(configuration_declarative_part const& node)
{
    static const std::string_view symbol{ "configuration_declarative_part" };
    symbol_scope<configuration_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(configuration_item const& node)
{
    static const std::string_view symbol{ "configuration_item" };
    symbol_scope<configuration_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(configuration_specification const& node)
{
    static const std::string_view symbol{ "configuration_specification" };
    symbol_scope<configuration_specification> _(*this, symbol);

    (*this)(node.component_specification);
    os << '\n';
    (*this)(node.binding_indication);
}

void printer::operator()(constant_declaration const& node)
{
    static const std::string_view symbol{ "constant_declaration" };
    symbol_scope<constant_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << '\n';

    (*this)(node.subtype_indication);

    if (node.expression) {
        os << '\n';
        (*this)(*node.expression);
    }
}

void printer::operator()(constrained_array_definition const& node)
{
    static const std::string_view symbol{ "constrained_array_definition" };
    symbol_scope<constrained_array_definition> _(*this, symbol);

    (*this)(node.index_constraint);
    os << '\n';
    (*this)(node.element_subtype_indication);
}

void printer::operator()(constraint const& node)
{
    static const std::string_view symbol{ "constraint" };
    symbol_scope<constraint> _(*this, symbol);

    visit(node);
}

void printer::operator()(context_clause const& node)
{
    static const std::string_view symbol{ "context_clause" };
    symbol_scope<context_clause> _(*this, symbol);
    visit(node);
}

void printer::operator()(context_item const& node)
{
    static const std::string_view symbol{ "context_item" };
    symbol_scope<context_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(decimal_literal const& node)
{
    static const std::string_view symbol{ "decimal_literal" };
    symbol_scope<decimal_literal> _(*this, symbol);

    using numeric_type_specifier = decimal_literal::numeric_type_specifier;

    os << "literal: " << node.literal << ", type: ";

    switch (node.numeric_type()) {
        case numeric_type_specifier::integer:
            os << "integer";
            break;
        case numeric_type_specifier::real:
            os << "real";
            break;
        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
}

void printer::operator()(delay_mechanism const& node)
{
    static const std::string_view symbol{ "delay_mechanism" };
    symbol_scope<delay_mechanism> _(*this, symbol);

    switch (node.delay_type) {  // invalid keywords call unreachable_bug_triggered() on default
        case ast::keyword_token::INERTIAL: {
            os << "INERTIAL_DELAY";
            break;
        }
        case ast::keyword_token::TRANSPORT: {
            os << "TRANSPORT_DELAY";
            break;
        }
        default:  // unreachable_bug_triggered, covers keywords 'UNSPECIFIED', 'ABS', 'ACCESS'...
            cxx_unreachable_bug_triggered();
    }

    if (node.time_expression) {
        os << '\n';
        (*this)(*node.time_expression);
    }
}

void printer::operator()(design_file const& node)
{
    static const std::string_view symbol{ "design_file" };
    symbol_scope<design_file> _(*this, symbol);
    visit(node);
}

void printer::operator()(design_unit const& node)
{
    static const std::string_view symbol{ "design_unit" };
    symbol_scope<design_unit> _(*this, symbol);

    if (!node.context_clause.empty()) {
        (*this)(node.context_clause);
        os << '\n';
    }
    (*this)(node.library_unit);
}

void printer::operator()(designator const& node)
{
    static const std::string_view symbol{ "designator" };
    symbol_scope<designator> _(*this, symbol);
    visit(node);
}

void printer::operator()(disconnection_specification const& node)
{
    static const std::string_view symbol{ "disconnection_specification" };
    symbol_scope<disconnection_specification> _(*this, symbol);

    (*this)(node.guarded_signal_specification);
    os << '\n';
    (*this)(node.time_expression);
}

void printer::operator()(discrete_range const& node)
{
    static const std::string_view symbol{ "discrete_range" };
    symbol_scope<discrete_range> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::subtype_indication const& discrete_subtype_indication) {
            (*this)(discrete_subtype_indication);
        },
        [this](ast::range const& range) {
            (*this)(range);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    }, node);
    // clang-format on
}

void printer::operator()(element_association const& node)
{
    static const std::string_view symbol{ "element_association" };
    symbol_scope<element_association> _(*this, symbol);

    if (!node.choices.empty()) {
        (*this)(node.choices);
        os << '\n';
    }

    (*this)(node.expression);
}

void printer::operator()(element_declaration const& node)
{
    static const std::string_view symbol{ "element_declaration" };
    symbol_scope<element_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << '\n';
    (*this)(node.element_subtype_definition);
}

void printer::operator()(entity_aspect const& node)
{
    static const std::string_view symbol{ "entity_aspect" };
    symbol_scope<entity_aspect> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::entity_aspect_entity const& entity) {
            static const std::string_view symbol{ "entity_aspect::entity" };
            symbol_scope<entity_aspect_entity> _(*this, symbol);
            (*this)(entity.name);
            if(entity.architecture_identifier) {
                os << '\n';
                (*this)(*entity.architecture_identifier);
            }
        },
        [this](ast::entity_aspect_configuration const& configuration) {
            static const std::string_view symbol{ "entity_aspect::configuration" };
            symbol_scope<entity_aspect_configuration> _(*this, symbol);
            (*this)(configuration.name);
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    }, node);
    // clang-format on
}

void printer::operator()(entity_class_entry_list const& node)
{
    static const std::string_view symbol{ "entity_class_entry_list" };
    symbol_scope<entity_class_entry_list> _(*this, symbol);
    visit(node);
}

void printer::operator()(entity_declaration const& node)
{
    static const std::string_view symbol{ "entity_declaration" };
    symbol_scope<entity_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';

    if (node.header.formal_generic_clause || node.header.formal_port_clause) {
        (*this)(node.header);
        os << '\n';
    }

    if (!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << '\n';
    }

    if (node.statement_part) {
        (*this)(*node.statement_part);
        os << '\n';
    }

    if (node.end_identifier) {
        (*this)(*node.end_identifier);
    }
}

void printer::operator()(entity_declarative_item const& node)
{
    static const std::string_view symbol{ "entity_declarative_item" };
    symbol_scope<entity_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(entity_declarative_part const& node)
{
    static const std::string_view symbol{ "entity_declarative_part" };
    symbol_scope<entity_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(entity_designator const& node)
{
    static const std::string_view symbol{ "entity_designator" };
    symbol_scope<entity_designator> _(*this, symbol);

    (*this)(node.entity_tag);
    if (node.signature) {
        os << '\n';
        (*this)(*node.signature);
    }
}

void printer::operator()(entity_header const& node)
{
    static const std::string_view symbol{ "entity_header" };
    symbol_scope<entity_header> _(*this, symbol);

    if (node.formal_generic_clause) {
        (*this)(*node.formal_generic_clause);
    }

    if (node.formal_port_clause) {
        if (node.formal_generic_clause) {
            os << '\n';
        }
        (*this)(*node.formal_port_clause);
    }
}

void printer::operator()(entity_name_list const& node)
{
    static const std::string_view symbol{ "entity_name_list" };
    symbol_scope<entity_name_list> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::entity_designator_list const& entity_designator_list) {
            static const std::string_view symbol{ "entity_designator*" };
            symbol_scope<entity_designator> _(*this, symbol);
            visit(entity_designator_list);
        },
        [this](ast::keyword_token token) {
            (*this)(token); // OTHERS | ALL
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    }, node);
    // clang-format on
}

void printer::operator()(entity_specification const& node)
{
    static const std::string_view symbol{ "entity_specification" };
    symbol_scope<entity_specification> _(*this, symbol);

    (*this)(node.entity_name_list);
    os << '\n';
    (*this)(node.entity_class);
}

void printer::operator()(entity_statement const& node)
{
    static const std::string_view symbol{ "entity_statement" };
    symbol_scope<entity_statement> _(*this, symbol);
    visit(node);
}

void printer::operator()(entity_statement_part const& node)
{
    static const std::string_view symbol{ "entity_statement_part" };
    symbol_scope<entity_statement_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(entity_tag const& node)
{
    static const std::string_view symbol{ "entity_tag" };
    symbol_scope<entity_tag> _(*this, symbol);
    visit(node);
}

void printer::operator()(enumeration_literal const& node)
{
    static const std::string_view symbol{ "enumeration_literal" };
    symbol_scope<enumeration_literal> _(*this, symbol);
    visit(node);
}

void printer::operator()(enumeration_type_definition const& node)
{
    static const std::string_view symbol{ "enumeration_type_definition" };
    symbol_scope<enumeration_type_definition> _(*this, symbol);
    visit(node);
}

void printer::operator()(exit_statement const& node)
{
    static const std::string_view symbol{ "exit_statement" };
    symbol_scope<exit_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        if (node.loop_label || node.condition) {
            os << '\n';
        }
    }

    if (node.loop_label) {
        (*this)(*node.loop_label);
        if (node.condition) {
            os << '\n';
        }
    }

    if (node.condition) {
        (*this)(*node.condition);
    }
}

void printer::operator()(expression const& node)
{
    static const std::string_view symbol{ "expression" };
    symbol_scope<expression> _(*this, symbol);

    (*this)(node.relation);

    if (node.rest_list.empty()) {
        return;
    }

    std::size_t const N = node.rest_list.size() - 1;
    std::size_t i = 0;
    for (auto const& chunk : node.rest_list) {
        os << ",\n"
           << "(operator: " << chunk.logical_operator << "),\n";
        (*this)(chunk.relation);
        if (i++ != N) {
            os << ",\n";
        }
    }
}

void printer::operator()(factor_binary_operation const& node)
{
    static const std::string_view symbol{ "factor_binary_operation" };
    symbol_scope<factor_binary_operation> _(*this, symbol);

    visit(node.primary_lhs);

    os << '\n' << "(operator: " << node.operator_ << "),\n";

    visit(node.primary_rhs);
}

void printer::operator()(factor_unary_operation const& node)
{
    static const std::string_view symbol{ "factor_unary_operation" };
    symbol_scope<factor_unary_operation> _(*this, symbol);

    os << "(operator: " << node.operator_ << "),\n";
    visit(node.primary);
}

void printer::operator()(factor const& node)
{
    static const std::string_view symbol{ "factor" };
    symbol_scope<factor> _(*this, symbol);
    visit(node);
}

void printer::operator()(file_declaration const& node)
{
    static const std::string_view symbol{ "file_declaration" };
    symbol_scope<file_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << '\n';

    (*this)(node.subtype_indication);

    if (node.file_open_information) {
        os << '\n';
        (*this)(*node.file_open_information);
    }
}

void printer::operator()(file_open_information const& node)
{
    static const std::string_view symbol{ "file_open_information" };
    symbol_scope<file_open_information> _(*this, symbol);

    if (node.file_open_kind_expression) {
        (*this)(*node.file_open_kind_expression);
        os << '\n';
    }
    (*this)(node.file_logical_name);
}

void printer::operator()(formal_part const& node)
{
    static const std::string_view symbol{ "formal_part" };
    symbol_scope<formal_part> _(*this, symbol);

    auto const visit_name = [this](auto const& ctx_name) {
        static const std::string_view symbol{ "{function_name|type_mark}" };
        symbol_scope<name> _(*this, symbol);
        (*this)(ctx_name);
    };

    auto const visit_formal_designator = [this](auto const& ctx_name) {
        static const std::string_view symbol{ "formal_designator" };
        symbol_scope<name> _(*this, symbol);
        (*this)(ctx_name);
    };

    // parsed as list of names
    // formal_designator ::=
    //      formal_designator
    //    | function_name ( formal_designator )
    //    | type_mark ( formal_designator )
    switch (node.context_tied_names.size()) {
        case 1: {
            // BNF: formal_designator
            visit_formal_designator(node.context_tied_names[0]);
            break;
        }

        case 2: {
            // BNF: {function_name|type_mark} ( formal_designator )
            visit_name(node.context_tied_names[0]);
            os << ",\n";
            visit_formal_designator(node.context_tied_names[1]);
            break;
        }

        default: {
            cxx_bug_fatal("VHDL BNF rules violation, parser rule failed!");
        }
    }
}

void printer::operator()(function_call const& node)
{
    static const std::string_view symbol{ "function_call" };
    symbol_scope<function_call> _(*this, symbol);

    (*this)(node.function_name);

    if (node.actual_parameter_part) {
        os << '\n';
        {
            static const std::string_view symbol{ "actual_parameter_part" };
            symbol_scope<function_call> _(*this, symbol);

            (*this)(*node.actual_parameter_part);
        }
    }
}

void printer::operator()(generate_statement const& node)
{
    static const std::string_view symbol{ "generate_statement" };
    symbol_scope<generate_statement> _(*this, symbol);

    (*this)(node.label);
    os << '\n';
    (*this)(node.generation_scheme);

    if (!node.block_declarative_parts.empty()) {
        os << '\n';
        (*this)(node.block_declarative_parts);
    }
    else {
        os << '\n';
    }

    if (!node.concurrent_statements.empty()) {
        static const std::string_view symbol{ "concurrent_statement*" };
        symbol_scope<struct _concurrent_statement> _(*this, symbol);
        visit(node.concurrent_statements);
    }

    if (node.end_label) {
        os << '\n';
        (*this)(*node.end_label);
    }
}

void printer::operator()(generation_scheme const& node)
{
    static const std::string_view symbol{ "generation_scheme" };
    symbol_scope<generation_scheme> _(*this, symbol);
    visit(node);
}

void printer::operator()(generic_clause const& node)
{
    static const std::string_view symbol{ "generic_clause" };
    symbol_scope<generic_clause> _(*this, symbol);
    (*this)(node.generic_list);
}

void printer::operator()(generic_map_aspect const& node)
{
    static const std::string_view symbol{ "generic_map_aspect" };
    symbol_scope<generic_map_aspect> _(*this, symbol);
    (*this)(node.association_list);
}

void printer::operator()(group_constituent const& node)
{
    static const std::string_view symbol{ "group_constituent" };
    symbol_scope<group_constituent> _(*this, symbol);
    visit(node);
}

void printer::operator()(group_constituent_list const& node)
{
    static const std::string_view symbol{ "group_constituent_list" };
    symbol_scope<group_constituent_list> _(*this, symbol);
    visit(node);
}

void printer::operator()(group_declaration const& node)
{
    static const std::string_view symbol{ "group_declaration" };
    symbol_scope<group_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';
    (*this)(node.group_template_name);
    os << '\n';
    (*this)(node.group_constituent_list);
}

void printer::operator()(group_template_declaration const& node)
{
    static const std::string_view symbol{ "group_template_declaration" };
    symbol_scope<group_template_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';
    (*this)(node.entity_class_entry_list);
}

void printer::operator()(guarded_signal_specification const& node)
{
    static const std::string_view symbol{ "guarded_signal_specification" };
    symbol_scope<guarded_signal_specification> _(*this, symbol);

    (*this)(node.guarded_signal_list);
    os << '\n';
    (*this)(node.type_mark);
}

void printer::operator()(identifier const& node)
{
    static const std::string_view symbol{ "identifier" };
    symbol_scope<identifier> _(*this, symbol);

    // Note, even if identifier following the BNF is variant, it's treated as
    // as common identifier for {basic, extended}_identifier
    os << node.name;
}

void printer::operator()(identifier_list const& node)
{
    static const std::string_view symbol{ "identifier_list" };
    symbol_scope<identifier_list> _(*this, symbol);
    visit(node);
}

void printer::operator()(if_statement const& node)
{
    static const std::string_view symbol{ "if_statement" };
    symbol_scope<if_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    (*this)(node.if_condition);
    os << "\nTHAN:\n";

    (*this)(node.then_sequence_of_statements);

    if (!node.elseif_chunks.empty()) {
        os << '\n';
        std::size_t const N = node.elseif_chunks.size() - 1;
        std::size_t i = 0;
        for (auto const& elsif_chunk : node.elseif_chunks) {
            os << "ELSIF:\n";
            (*this)(elsif_chunk.condition);
            os << "\nTHAN:\n";
            (*this)(elsif_chunk.sequence_of_statements);
            if (i++ != N) {
                os << '\n';
            }
        }
    }

    if (!node.else_sequence_of_statements.empty()) {
        os << "\nELSE:\n";
        (*this)(node.else_sequence_of_statements);
    }

    if (node.end_label) {
        os << '\n';
        (*this)(*node.end_label);
    }
}

void printer::operator()(index_constraint const& node)
{
    static const std::string_view symbol{ "index_constraint" };
    symbol_scope<index_constraint> _(*this, symbol);
    visit(node);
}

void printer::operator()(index_specification const& node)
{
    static const std::string_view symbol{ "index_specification" };
    symbol_scope<index_specification> _(*this, symbol);
    visit(node);
}

void printer::operator()(index_subtype_definition const& node)
{
    static const std::string_view symbol{ "index_subtype_definition" };
    symbol_scope<index_subtype_definition> _(*this, symbol);
    (*this)(node.type_mark);
}

void printer::operator()(indexed_name const& node)
{
    static const std::string_view symbol{ "indexed_name" };
    symbol_scope<indexed_name> _(*this, symbol);

    (*this)(node.prefix);
    os << '\n';

    {
        static const std::string_view symbol{ "expression*" };
        symbol_scope<expression> _(*this, symbol);
        visit(node.expression_list);
    }
}

void printer::operator()(instantiated_unit const& node)
{
    static const std::string_view symbol{ "instantiated_unit" };
    symbol_scope<instantiated_unit> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::instantiated_unit_component const& component) {
            static const std::string_view symbol{ "component" };
            symbol_scope<instantiated_unit_component> _(*this, symbol);
            (*this)(component.name);
        },
        [this](ast::instantiated_unit_entity const& entity) {
            static const std::string_view symbol{ "entity" };
            symbol_scope<instantiated_unit_entity> _(*this, symbol);
            (*this)(entity.name);
            if(entity.architecture_identifier) {
                os << '\n';
                (*this)(*entity.architecture_identifier);
            }
        },
        [this](ast::instantiated_unit_configuration const& configuration) {
            static const std::string_view symbol{ "configuration" };
            symbol_scope<instantiated_unit_configuration> _(*this, symbol);
            (*this)(configuration.name);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    }, node);
    // clang-format on
}

void printer::operator()(instantiation_list const& node)
{
    static const std::string_view symbol{ "instantiation_list" };
    symbol_scope<instantiation_list> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::instantiation_label_list const& instantiation_label_list) {
            static const std::string_view symbol{ "label*" };
            symbol_scope<label> _(*this, symbol);
            visit(instantiation_label_list);
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    }, node);
    // clang-format on
}

void printer::operator()(interface_constant_declaration const& node)
{
    static const std::string_view symbol{ "interface_constant_declaration" };
    symbol_scope<interface_constant_declaration> _(*this, symbol);

    if (node.constant) {
        os << "(constant)\n";
    }

    (*this)(node.identifier_list);
    os << '\n';

    if (node.in) {
        os << "(in)\n";
    }

    (*this)(node.subtype_indication);

    if (node.static_expression) {
        os << '\n';
        (*this)(*node.static_expression);
    }
}

void printer::operator()(interface_declaration const& node)
{
    static const std::string_view symbol{ "interface_declaration" };
    symbol_scope<interface_declaration> _(*this, symbol);
    visit(node);
}

void printer::operator()(interface_file_declaration const& node)
{
    static const std::string_view symbol{ "interface_file_declaration" };
    symbol_scope<interface_file_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << '\n';
    (*this)(node.subtype_indication);
}

void printer::operator()(interface_list const& node)
{
    static const std::string_view symbol{ "interface_list" };
    symbol_scope<interface_list> _(*this, symbol);
    visit(node);
}

void printer::operator()(interface_signal_declaration const& node)
{
    static const std::string_view symbol{ "interface_signal_declaration" };
    symbol_scope<interface_signal_declaration> _(*this, symbol);

    if (node.signal) {
        os << "(signal)\n";
    }

    (*this)(node.identifier_list);
    os << '\n';

    if (node.mode) {
        (*this)(*node.mode);
        os << '\n';
    }

    (*this)(node.subtype_indication);

    if (node.bus) {
        os << "\n(bus)";
    }

    if (node.static_expression) {
        os << '\n';
        (*this)(*node.static_expression);
    }
}

void printer::operator()(interface_variable_declaration const& node)
{
    static const std::string_view symbol{ "interface_variable_declaration" };
    symbol_scope<interface_variable_declaration> _(*this, symbol);

    if (node.VARIABLE) {
        os << "(variable)\n";
    }

    (*this)(node.identifier_list);
    os << '\n';

    if (node.mode) {
        (*this)(*node.mode);
        os << '\n';
    }

    (*this)(node.subtype_indication);

    if (node.static_expression) {
        os << '\n';
        (*this)(*node.static_expression);
    }
}

void printer::operator()(iteration_scheme const& node)
{
    static const std::string_view symbol{ "iteration_scheme" };
    symbol_scope<iteration_scheme> _(*this, symbol);
    visit(node);
}

void printer::operator()(library_clause const& node)
{
    static const std::string_view symbol{ "library_clause" };
    symbol_scope<library_clause> _(*this, symbol);
    visit(node.logical_name_list);
}

void printer::operator()(library_unit const& node)
{
    static const std::string_view symbol{ "library_unit" };
    symbol_scope<library_unit> _(*this, symbol);
    visit(node);
}

void printer::operator()(literal const& node)
{
    static const std::string_view symbol{ "literal" };
    symbol_scope<literal> _(*this, symbol);
    visit(node);
}

void printer::operator()(loop_statement const& node)
{
    static const std::string_view symbol{ "loop_statement" };
    symbol_scope<loop_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    if (node.iteration_scheme) {
        (*this)(*node.iteration_scheme);
        os << '\n';
    }

    (*this)(node.sequence_of_statements);

    if (node.end_label) {
        os << '\n';
        (*this)(*node.end_label);
    }
}

void printer::operator()(name const& node)
{
    static const std::string_view symbol{ "name" };
    symbol_scope<name> _(*this, symbol);
    visit(node);
}

void printer::operator()(next_statement const& node)
{
    static const std::string_view symbol{ "next_statement" };
    symbol_scope<next_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        if (node.loop_label || node.condition) {
            os << '\n';
        }
    }

    if (node.loop_label) {
        (*this)(*node.loop_label);
        if (node.condition) {
            os << '\n';
        }
    }

    if (node.condition) {
        (*this)(*node.condition);
    }
}

void printer::operator()(null_statement const& node)
{
    static const std::string_view symbol{ "null_statement" };
    symbol_scope<null_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
    }
}

void printer::operator()(numeric_literal const& node)
{
    static const std::string_view symbol{ "numeric_literal" };
    symbol_scope<numeric_literal> _(*this, symbol);
    visit(node);
}

void printer::operator()(options const& node)
{
    static const std::string_view symbol{ "options" };
    symbol_scope<options> _(*this, symbol);

    if (node.guarded) {
        os << "GUARDED";
    }
    if (node.delay_mechanism) {
        if (node.guarded) {
            os << '\n';
        }
        (*this)(*node.delay_mechanism);
    }
}

void printer::operator()(package_body const& node)
{
    static const std::string_view symbol{ "package_body" };
    symbol_scope<package_body> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';

    (*this)(node.declarative_part);

    if (node.end_identifier) {
        os << '\n';
        (*this)(*node.end_identifier);
    }
}

void printer::operator()(package_body_declarative_item const& node)
{
    static const std::string_view symbol{ "package_body_declarative_item" };
    symbol_scope<package_body_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(package_body_declarative_part const& node)
{
    static const std::string_view symbol{ "package_body_declarative_part" };
    symbol_scope<package_body_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(package_declaration const& node)
{
    static const std::string_view symbol{ "package_declaration" };
    symbol_scope<package_declaration> _(*this, symbol);

    (*this)(node.identifier);

    if (!node.declarative_part.empty()) {
        os << '\n';
        (*this)(node.declarative_part);
    }

    if (node.end_identifier) {
        os << '\n';
        (*this)(*node.end_identifier);
    }
}

void printer::operator()(package_declarative_item const& node)
{
    static const std::string_view symbol{ "package_declarative_item" };
    symbol_scope<package_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(package_declarative_part const& node)
{
    static const std::string_view symbol{ "package_declarative_part" };
    symbol_scope<package_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(parameter_specification const& node)
{
    static const std::string_view symbol{ "parameter_specification" };
    symbol_scope<parameter_specification> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';
    (*this)(node.discrete_range);
}

void printer::operator()(physical_literal const& node)
{
    static const std::string_view symbol{ "physical_literal" };
    symbol_scope<physical_literal> _(*this, symbol);

    (*this)(node.literal);
    os << ",\n"
       << "(unit_name: " << node.unit_name << ")";
}

void printer::operator()(physical_type_definition const& node)
{
    static const std::string_view symbol{ "physical_type_definition" };
    symbol_scope<physical_type_definition> _(*this, symbol);

    (*this)(node.range_constraint);
    os << '\n';
    (*this)(node.primary_unit_declaration);

    if (!node.secondary_unit_declarations.empty()) {
        os << '\n';
    }

    {
        static const std::string_view symbol{ "secondary_unit_declaration*" };
        symbol_scope<struct _secondary_unit_declarations> _(*this, symbol);
        visit(node.secondary_unit_declarations);
    }

    if (node.physical_type_simple_name) {
        os << '\n';
        (*this)(*node.physical_type_simple_name);
    }
}

void printer::operator()(port_clause const& node)
{
    static const std::string_view symbol{ "port_clause" };
    symbol_scope<port_clause> _(*this, symbol);
    (*this)(node.port_list);
}

void printer::operator()(port_map_aspect const& node)
{
    static const std::string_view symbol{ "port_map_aspect" };
    symbol_scope<port_map_aspect> _(*this, symbol);
    (*this)(node.association_list);
}

void printer::operator()(prefix const& node)
{
    static const std::string_view symbol{ "prefix" };
    symbol_scope<prefix> _(*this, symbol);
    visit(node);
}

void printer::operator()(primary const& node)
{
    static const std::string_view symbol{ "primary" };
    symbol_scope<primary> _(*this, symbol);
    visit(node);
}

void printer::operator()(primary_unit const& node)
{
    static const std::string_view symbol{ "primary_unit" };
    symbol_scope<primary_unit> _(*this, symbol);
    visit(node);
}

void printer::operator()(procedure_call const& node)
{
    static const std::string_view symbol{ "procedure_call" };
    symbol_scope<procedure_call> _(*this, symbol);

    (*this)(node.procedure_name);

    if (node.actual_parameter_part) {
        os << '\n';
        {
            static const std::string_view symbol{ "actual_parameter_part" };
            symbol_scope<function_call> _(*this, symbol);
            (*this)(*node.actual_parameter_part);
        }
    }
}

void printer::operator()(procedure_call_statement const& node)
{
    static const std::string_view symbol{ "procedure_call_statement" };
    symbol_scope<procedure_call_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }
    (*this)(node.procedure_call);
}

void printer::operator()(process_declarative_item const& node)
{
    static const std::string_view symbol{ "process_declarative_item" };
    symbol_scope<process_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(process_declarative_part const& node)
{
    static const std::string_view symbol{ "process_declarative_part" };
    symbol_scope<process_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(process_statement const& node)
{
    static const std::string_view symbol{ "process_statement" };
    symbol_scope<process_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    if (node.postponed) {
        os << "POSTPONED\n";
    }

    if (!node.sensitivity_list.empty()) {
        (*this)(node.sensitivity_list);
        os << '\n';
    }

    if (!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << '\n';
    }

    if (!node.statement_part.empty()) {
        (*this)(node.statement_part);
    }

    if (node.end_postponed) {
        os << "\nPOSTPONED";
    }

    if (node.label) {
        os << '\n';
        (*this)(*node.label);
    }
}

void printer::operator()(qualified_expression const& node)
{
    static const std::string_view symbol{ "qualified_expression" };
    symbol_scope<qualified_expression> _(*this, symbol);

    (*this)(node.type_mark);
    os << '\n';

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::expression const& expr) {
            (*this)(expr);
        },
        [this](ast::aggregate const& aggregate) {
            (*this)(aggregate);
        },
        [this](ast::nullary nullary) {
            (*this)(nullary);
        }
    }, node.aggregate_or_expression);
    // clang-format on
}

void printer::operator()(range const& node)  // aka range_constraint
{
    static const std::string_view symbol{ "range" };
    symbol_scope<range> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](range_attribute_name const &name) {
            (*this)(name);
        },
        [this](range_expression const &expr) {
            (*this)(expr.lhs);
            os << '\n';
            (*this)(expr.direction);
            os << '\n';
            (*this)(expr.rhs);
        }
    }, node);
    // clang-format on
}

void printer::operator()(record_type_definition const& node)
{
    static const std::string_view symbol{ "record_type_definition" };
    symbol_scope<record_type_definition> _(*this, symbol);

    {
        static const std::string_view symbol{ "element_declaration*" };
        symbol_scope<element_declaration> _(*this, symbol);
        visit(node.element_declarations);
    }
}

void printer::operator()(relation const& node)
{
    static const std::string_view symbol{ "relation" };
    symbol_scope<relation> _(*this, symbol);

    (*this)(node.shift_expression);

    if (!node.rest) {
        return;
    }

    auto const& chunk = *node.rest;
    os << ",\n"
       << "(operator: " << chunk.relational_operator << "),\n";
    (*this)(chunk.shift_expression);
}

void printer::operator()(report_statement const& node)
{
    static const std::string_view symbol{ "report_statement" };
    symbol_scope<report_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    (*this)(node.report);

    if (node.severity) {
        os << '\n';
        (*this)(*node.severity);
    }
}

void printer::operator()(return_statement const& node)
{
    static const std::string_view symbol{ "return_statement" };
    symbol_scope<report_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
    }

    if (node.expression) {
        if (node.label) {
            os << '\n';
        }
        (*this)(*node.expression);
    }
}

void printer::operator()(scalar_type_definition const& node)
{
    static const std::string_view symbol{ "scalar_type_definition" };
    symbol_scope<scalar_type_definition> _(*this, symbol);
    visit(node);
}

void printer::operator()(secondary_unit const& node)
{
    static const std::string_view symbol{ "secondary_unit" };
    symbol_scope<secondary_unit> _(*this, symbol);
    visit(node);
}

void printer::operator()(secondary_unit_declaration const& node)
{
    static const std::string_view symbol{ "secondary_unit_declaration" };
    symbol_scope<secondary_unit_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << '\n';
    (*this)(node.physical_literal);
}

void printer::operator()(selected_name const& node)
{
    static const std::string_view symbol{ "selected_name" };
    symbol_scope<selected_name> _(*this, symbol);

    (*this)(node.prefix);
    os << '\n';
    (*this)(node.suffix);
}

void printer::operator()(selected_signal_assignment const& node)
{
    static const std::string_view symbol{ "selected_signal_assignment" };
    symbol_scope<selected_signal_assignment> _(*this, symbol);

    (*this)(node.expression);
    os << '\n';

    (*this)(node.target);
    os << '\n';

    (*this)(node.options);
    os << '\n';

    (*this)(node.selected_waveforms);
}

void printer::operator()(selected_waveforms const& node)
{
    static const std::string_view symbol{ "selected_waveforms" };
    symbol_scope<selected_waveforms> _(*this, symbol);

    // doesn't make sense to unify this
    std::size_t const N = node.size() - 1;
    std::size_t i = 0;
    for (auto const& selected_waveform : node) {
        (*this)(selected_waveform.waveform);
        os << '\n';
        (*this)(selected_waveform.choices);
        if (i++ != N) {
            os << ",\n";
        }
    }
}

void printer::operator()(sensitivity_clause const& node)
{
    static const std::string_view symbol{ "sensitivity_clause" };
    symbol_scope<sensitivity_clause> _(*this, symbol);
    (*this)(node.sensitivity_list);
}

void printer::operator()(sensitivity_list const& node)
{
    static const std::string_view symbol{ "sensitivity_list" };
    symbol_scope<sensitivity_list> _(*this, symbol);
    visit(node);
}

void printer::operator()(sequence_of_statements const& node)
{
    static const std::string_view symbol{ "sequence_of_statements" };
    symbol_scope<sequence_of_statements> _(*this, symbol);
    visit(node);
}

void printer::operator()(sequential_statement const& node)
{
    static const std::string_view symbol{ "sequential_statement" };
    symbol_scope<sequential_statement> _(*this, symbol);
    visit(node);
}

void printer::operator()(shift_expression const& node)
{
    static const std::string_view symbol{ "shift_expression" };
    symbol_scope<shift_expression> _(*this, symbol);

    (*this)(node.simple_expression);

    if (!node.rest) {
        return;
    }

    auto const& chunk = *node.rest;
    os << ",\n"
       << "(operator: " << chunk.shift_operator << "),\n";
    (*this)(chunk.simple_expression);
}

void printer::operator()(signal_assignment_statement const& node)
{
    static const std::string_view symbol{ "signal_assignment_statement" };
    symbol_scope<signal_assignment_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }

    (*this)(node.target);
    os << '\n';

    if (node.delay_mechanism) {
        (*this)(*node.delay_mechanism);
        os << '\n';
    }

    (*this)(node.waveform);
}

void printer::operator()(signal_declaration const& node)
{
    static const std::string_view symbol{ "signal_declaration" };
    symbol_scope<signal_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << '\n';

    (*this)(node.subtype_indication);

    if (node.signal_kind) {
        os << '\n';
        (*this)(*node.signal_kind);
    }

    if (node.expression) {
        os << '\n';
        (*this)(*node.expression);
    }
}

void printer::operator()(signal_list_list const& node)
{
    static const std::string_view symbol{ "signal_list.names" };
    symbol_scope<signal_list_list> _(*this, symbol);
    visit(node);
}

void printer::operator()(signal_list const& node)
{
    static const std::string_view symbol{ "signal_list" };
    symbol_scope<signal_list> _(*this, symbol);

    visit(node);
}

void printer::operator()(signature const& node)
{
    static const std::string_view symbol{ "signature" };
    symbol_scope<signature> _(*this, symbol);

    {
        static const std::string_view symbol{ "parameter_type_list" };
        symbol_scope<signature> _(*this, symbol);
        visit(node.parameter_type_list);
    }

    if (node.return_type) {
        if (!node.parameter_type_list.empty()) {
            os << '\n';
        }

        static const std::string_view symbol{ "return_type" };
        symbol_scope<signature> _(*this, symbol);
        (*this)(*node.return_type);
    }
}

void printer::operator()(simple_expression const& node)
{
    static const std::string_view symbol{ "simple_expression" };
    symbol_scope<simple_expression> _(*this, symbol);

    if (node.sign) {  // optional
        os << "sign: " << *node.sign << ",\n";
    }

    (*this)(node.term);

    if (node.rest_list.empty()) {
        return;
    }

    std::size_t const N = node.rest_list.size() - 1;
    std::size_t i = 0;
    for (auto const& chunk : node.rest_list) {
        os << ",\n"
           << "(operator: " << chunk.adding_operator << "),\n";
        (*this)(chunk.term);
        if (i++ != N) {
            os << ",\n";
        }
    }
}

void printer::operator()(slice_name const& node)
{
    static const std::string_view symbol{ "slice_name" };
    symbol_scope<slice_name> _(*this, symbol);

    (*this)(node.prefix);
    os << '\n';

    (*this)(node.discrete_range);
}

void printer::operator()(string_literal const& node)
{
    static const std::string_view symbol{ "string_literal" };
    symbol_scope<string_literal> _(*this, symbol);

    // Note, following the LRM, if a quotation sign has to be used in a string
    // literal, it is denoted by two double quotes side by side. This must
    // be replaced since string_view is used.
    os << node.literal;
}

void printer::operator()(subprogram_body const& node)
{
    static const std::string_view symbol{ "subprogram_body" };
    symbol_scope<subprogram_body> _(*this, symbol);

    (*this)(node.specification);
    os << '\n';

    (*this)(node.declarative_part);
    os << '\n';

    (*this)(node.statement_part);

    if (node.kind) {
        os << '\n';
        (*this)(*node.kind);
    }

    if (node.designator) {
        os << '\n';
        (*this)(*node.designator);
    }
}

void printer::operator()(subprogram_declarative_item const& node)
{
    static const std::string_view symbol{ "subprogram_declarative_item" };
    symbol_scope<subprogram_declarative_item> _(*this, symbol);
    visit(node);
}

void printer::operator()(subprogram_declarative_part const& node)
{
    static const std::string_view symbol{ "subprogram_declarative_part" };
    symbol_scope<subprogram_declarative_part> _(*this, symbol);
    visit(node);
}

void printer::operator()(subprogram_specification const& node)
{
    static const std::string_view symbol{ "subprogram_specification" };
    symbol_scope<subprogram_specification> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::subprogram_specification_procedure const& procedure) {
            os << "PROCEDURE\n";
            (*this)(procedure.designator);
            if(procedure.formal_parameter_list) {
                os << '\n';
                (*this)(*procedure.formal_parameter_list);
            }
        },
        [this](ast::subprogram_specification_function const& function) {
            if(function.impure) { os << "IMPURE FUNCTION\n"; }
            else {                os << "PURE FUNCTION\n"; }
            (*this)(function.designator);
            if(function.formal_parameter_list) {
                os << '\n';
                (*this)(*function.formal_parameter_list);
            }
            os << '\n';
            (*this)(function.return_type_mark);
        }
    }, node);
    // clang-format on
}

void printer::operator()(subtype_declaration const& node)
{
    static const std::string_view symbol{ "subtype_declaration" };
    symbol_scope<subtype_declaration> _(*this, symbol);
    (*this)(node.identifier);
    os << '\n';
    (*this)(node.subtype_indication);
}

void printer::operator()(subtype_indication const& node)
{
    static const std::string_view symbol{ "subtype_indication" };
    symbol_scope<subtype_indication> _(*this, symbol);

    auto const visit_type_mark = [this](auto const& type_mark) {
        static const std::string_view symbol{ "type_mark" };
        symbol_scope<name> _(*this, symbol);
        (*this)(type_mark);
    };

    auto const visit_resolution_function_name = [this](auto const& resolution_function_name) {
        static const std::string_view symbol{ "resolution_function_name" };
        symbol_scope<name> _(*this, symbol);
        (*this)(resolution_function_name);
    };

    // parsed as (name) list with trailing constraint
    // subtype_indication ::=
    //     [ resolution_function_name ] type_mark [ constraint ]
    switch (node.unspecified_name_list.size()) {
        case 1: {
            // BNF: type_mark .... [ constraint ]
            visit_type_mark(node.unspecified_name_list[0]);
            break;
        }

        case 2: {
            // BNF: [ resolution_function_name ] type_mark ... [ constraint ]
            visit_resolution_function_name(node.unspecified_name_list[0]);
            os << '\n';
            visit_type_mark(node.unspecified_name_list[1]);
            break;
        }

        default:
            cxx_bug_fatal("VHDL BNF rules violation, parser rule failed!");
    }

    if (node.constraint) {
        os << '\n';
        (*this)(*node.constraint);
    }
}

void printer::operator()(suffix const& node)
{
    static const std::string_view symbol{ "suffix" };
    symbol_scope<suffix> _(*this, symbol);
    visit(node);
}

void printer::operator()(target const& node)
{
    static const std::string_view symbol{ "target" };
    symbol_scope<target> _(*this, symbol);

    visit(node);
}

void printer::operator()(term const& node)
{
    static const std::string_view symbol{ "term" };
    symbol_scope<term> _(*this, symbol);

    visit(node.factor);

    if (node.rest_list.empty()) {
        return;
    }

    os << ",\n";

    std::size_t const N = node.rest_list.size() - 1;
    std::size_t i = 0;
    for (auto const& term_chunk : node.rest_list) {
        os << "(operator: " << term_chunk.multiplying_operator << "),\n";
        visit(term_chunk.factor);
        if (i++ != N) {
            os << ",\n";
        }
    }
}

void printer::operator()(timeout_clause const& node)
{
    static const std::string_view symbol{ "timeout_clause" };
    symbol_scope<timeout_clause> _(*this, symbol);
    (*this)(node.time_expression);
}

void printer::operator()(type_conversion const& node)
{
    static const std::string_view symbol{ "type_conversion" };
    symbol_scope<type_conversion> _(*this, symbol);
    (*this)(node.type_mark);
    os << '\n';
    (*this)(node.expression);
}

void printer::operator()(type_declaration const& node)
{
    // {full, incomplete}_type_declaration
    static const std::string_view symbol{ "type_declaration" };
    symbol_scope<type_declaration> _(*this, symbol);
    (*this)(node.identifier);

    if (node.type_definition) {
        os << '\n';
        (*this)(*node.type_definition);
    }
}

void printer::operator()(type_definition const& node)
{
    static const std::string_view symbol{ "type_definition" };
    symbol_scope<type_definition> _(*this, symbol);
    visit(node);
}

void printer::operator()(unconstrained_array_definition const& node)
{
    static const std::string_view symbol{ "unconstrained_array_definition" };
    symbol_scope<unconstrained_array_definition> _(*this, symbol);

    for (auto const& index_subtype_definition : node.index_subtype_definitions) {
        (*this)(index_subtype_definition);
        os << '\n';
    }
    (*this)(node.element_subtype_indication);
}

void printer::operator()(use_clause const& node)
{
    static const std::string_view symbol{ "use_clause" };
    symbol_scope<use_clause> _(*this, symbol);

    std::size_t const N = node.list.size() - 1;
    std::size_t i = 0;
    for (auto const& selected_name : node.list) {
        for (auto const& name : selected_name.prefix_list) {
            (*this)(name);
            os << ".\n";
        }
        (*this)(selected_name.suffix);
        if (i++ != N) {
            os << ",\n";
        }
    }
}

void printer::operator()(variable_assignment_statement const& node)
{
    static const std::string_view symbol{ "variable_assignment_statement" };
    symbol_scope<variable_assignment_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
        os << '\n';
    }
    (*this)(node.target);
    os << '\n';
    (*this)(node.expression);
}

void printer::operator()(variable_declaration const& node)
{
    static const std::string_view symbol{ "variable_declaration" };
    symbol_scope<variable_declaration> _(*this, symbol);

    if (node.shared) {
        os << "SHARED\n";
    }

    (*this)(node.identifier_list);
    os << '\n';
    (*this)(node.subtype_indication);

    if (node.expression) {
        os << '\n';
        (*this)(*node.expression);
    }
}

void printer::operator()(wait_statement const& node)
{
    static const std::string_view symbol{ "wait_statement" };
    symbol_scope<wait_statement> _(*this, symbol);

    if (node.label) {
        (*this)(*node.label);
    }
    if (node.sensitivity_clause) {
        if (node.label) {
            os << '\n';
        }
        (*this)(*node.sensitivity_clause);
    }
    if (node.condition_clause) {
        if (node.label || node.sensitivity_clause) {
            os << '\n';
        }
        (*this)(*node.condition_clause);
    }
    if (node.timeout_clause) {
        if (node.label || node.sensitivity_clause || node.condition_clause) {
            os << '\n';
        }
        (*this)(*node.timeout_clause);
    }
}

void printer::operator()(waveform const& node)
{
    static const std::string_view symbol{ "waveform" };
    symbol_scope<waveform> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::waveform_element_list const& list) {
            static const std::string_view symbol{ "waveform_element*" };
            symbol_scope<waveform_element> _(*this, symbol);
            visit(list);
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        }
    }, node);
    // clang-format on
}

void printer::operator()(waveform_element const& node)
{
    static const std::string_view symbol{ "waveform_element" };
    symbol_scope<waveform_element> _(*this, symbol);

    // clang-format off
    boost::apply_visitor(util::overloaded {
        [this](ast::expression const& expr) {
            (*this)(expr);
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        }
    }, node.form);
    // clang-format on

    if (node.time_expression) {
        os << '\n';
        (*this)(*node.time_expression);
    }
}

void printer::operator()([[maybe_unused]] nullary const& node)
{
    os << "\n*****************************";
    os << "\n*    SHALL NEVER BE HERE    *";
    os << "\n*****************************\n";
}

//
// Non AST members, used e.g. for unit tests (namely ast::integer)
//
void printer::operator()(ast::string_span const& node)
{
    // even boost::iterator_range is used, the symbol is string_view
    static const std::string_view symbol{ "std::string_view" };
    symbol_scope<std::string> _(*this, symbol);

    os << node;
}

void printer::operator()(keyword_token token)
{
    static const std::string_view symbol{ "keyword" };
    symbol_scope<keyword_token> _(*this, symbol);

    os << token;
}

template <typename T>
void printer::visit(std::vector<T> const& vector)
{
    if (vector.empty()) {
        os << "()";
    }
    else {
        std::size_t const N = vector.size() - 1;
        std::size_t i = 0;
        for (auto const& e : vector) {
            (*this)(e);
            if (i++ != N) {
                os << ",\n";
            }
        }
    }
}

}  // namespace ibis::vhdl::ast
