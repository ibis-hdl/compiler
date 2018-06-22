/*
 * ast_printer.cpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#include <eda/utils/cxx_bug_fatal.hpp>

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <eda/support/boost/hana_overload.hpp>
#include <eda/vhdl/ast_printer.hpp>

#include <map>


#include <eda/utils/compiler_push.hpp>
#include <eda/utils/compiler_warning.hpp>


namespace eda { namespace vhdl { namespace ast {


using namespace ::eda::utils;


printer::printer(std::ostream& os, uint16_t start_indent)
    : os{ os, start_indent }
    , verbose_symbol {false}
    , verbose_variant{ false }
    { }

struct printer::scope_printer
{
    ostream& os;
    const char* const name{ nullptr };
    bool const verbose;

    scope_printer(ostream& os_, char const name[], bool verbose, char const name_pfx[] = nullptr)
    : os{ os_ }
    , name{ name }
    , verbose{ verbose }
    {
        if(verbose) {
            os << increase_indent << "(";
            os << name;
            if(name_pfx) {
                os << "<" << name_pfx << ">";
            }
            os << "\n";
        }
    }

    ~scope_printer()
    {
        if(verbose) {
            os << decrease_indent << "\n)";
        }
    }
};


template<typename T, typename Enable>
struct printer::symbol_scope
: public scope_printer
{
    symbol_scope(printer& root, char const name[])
    : scope_printer(root.os, name, root.verbose_symbol)
    { }
};

template<typename T>
struct printer::symbol_scope<
    T, typename std::enable_if<x3::traits::is_variant<T>::value>::type
>
: public printer::scope_printer
{
    symbol_scope(printer& root, char const name[])
    : scope_printer(root.os, name, root.verbose_variant, "v")
    { }
};


} } } // namespace eda.vhdl.ast


namespace eda { namespace vhdl { namespace ast {


void printer::operator()(abstract_literal const &node)
{
    static char const symbol[]{ "abstract_literal" };
    symbol_scope<abstract_literal> _(*this, symbol);
    visit(node);
}


void printer::operator()(access_type_definition const &node)
{
    static char const symbol[]{ "access_type_definition" };
    symbol_scope<access_type_definition> _(*this, symbol);
    (*this)(node.subtype_indication);
}


void printer::operator()(actual_designator const &node)
{
    static char const symbol[]{ "actual_designator" };
    symbol_scope<actual_designator> _(*this, symbol);
    visit(node);
}


void printer::operator()(actual_part const &node)
{
    static char const symbol[]{ "actual_part" };
    symbol_scope<actual_part> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::actual_part_chunk const& chunk) {
            (*this)(chunk.context_tied_name);
            os << "\n";
            (*this)(chunk.actual_designator);
        },
        [this](ast::actual_designator node) {
            (*this)(node);
        }
    );
}


void printer::operator()(aggregate const &node)
{
    static char const symbol[]{ "aggregate" };
    symbol_scope<aggregate> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& element_association : node) {
        (*this)(element_association);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(alias_declaration const &node)
{
    static char const symbol[]{ "alias_declaration" };
    symbol_scope<alias_declaration> _(*this, symbol);

    (*this)(node.alias_designator);
    os << "\n";

    if(node.subtype_indication) {
        (*this)(*node.subtype_indication);
        os << "\n";
    }

    (*this)(node.name);

    if(node.signature) {
        os << "\n";
        (*this)(*node.signature);
    }
}


void printer::operator()(alias_designator const &node)
{
    static char const symbol[]{ "alias_designator" };
    symbol_scope<alias_designator> _(*this, symbol);
    visit(node);
}


void printer::operator()(allocator const &node)
{
    static char const symbol[]{ "allocator" };
    symbol_scope<allocator> _(*this, symbol);
    visit(node);
}


void printer::operator()(architecture_body const &node)
{
    static char const symbol[]{ "architecture_body" };
    symbol_scope<architecture_body> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";

    (*this)(node.entity_name);
    os << "\n";

    (*this)(node.declarative_part);
    os << "\n";

    (*this)(node.statement_part);

    if(node.end_name) {
        os << "\n";
        (*this)(*node.end_name);
    }
}


void printer::operator()(architecture_statement_part const &node)
{
    static char const symbol[]{ "architecture_statement_part" };
    symbol_scope<architecture_statement_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& concurrent_statement : node) {
        (*this)(concurrent_statement);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(array_type_definition const &node)
{
    static char const symbol[]{ "array_type_definition" };
    symbol_scope<array_type_definition> _(*this, symbol);
    visit(node);
}


void printer::operator()(assertion const &node)
{
    static char const symbol[]{ "assertion" };
    symbol_scope<assertion> _(*this, symbol);

    (*this)(node.condition);

    if(node.report) {
        static char const symbol[]{ "assertion.report" };
        os << "\n";
        symbol_scope<assertion> _(*this, symbol);
        (*this)(*node.report);
    }
    if(node.severity) {
        static char const symbol[]{ "assertion.severity" };
        os << "\n";
        symbol_scope<assertion> _(*this, symbol);
        (*this)(*node.severity);
    }
}


void printer::operator()(assertion_statement const &node)
{
    static char const symbol[]{ "assertion_statement" };
    symbol_scope<assertion_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }
    (*this)(node.assertion);
}


void printer::operator()(association_element const &node)
{
    static char const symbol[]{ "association_element" };
    symbol_scope<association_element> _(*this, symbol);

    if(node.formal_part) {
        (*this)(*node.formal_part);
        os << "\n";
    }
    (*this)(node.actual_part);
}


void printer::operator()(association_list const &node)
{
    static char const symbol[]{ "association_list" };
    symbol_scope<association_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& association_element : node) {
        (*this)(association_element);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(attribute_declaration const &node)
{
    static char const symbol[]{ "attribute_declaration" };
    symbol_scope<attribute_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";
    (*this)(node.type_mark);
}


void printer::operator()(attribute_name const &node)
{
    static char const symbol[]{ "attribute_name" };
    symbol_scope<attribute_name> _(*this, symbol);

    (*this)(node.prefix);

    if(node.signature) {
        os << "\n";
        (*this)(*node.signature);
    }

    os << "\n";
    {   // no own type, printing here
        static char const symbol[]{ "attribute_designator" };
        symbol_scope<attribute_name> _(*this, symbol);

        (*this)(node.attribute_designator);
    }

    if(node.expression) {
        os << "\n";
        (*this)(*node.expression);
    }
}


void printer::operator()(attribute_specification const &node)
{
    static char const symbol[]{ "attribute_specification" };
    symbol_scope<attribute_specification> _(*this, symbol);

    {
        static char const symbol[]{ "attribute_designator" };
        symbol_scope<based_literal> _(*this, symbol);
        (*this)(node.attribute_designator);
    }

    os << "\n";
    (*this)(node.entity_specification);

    os << "\n";
    (*this)(node.expression);
}


void printer::operator()(based_literal const &node)
{
    static char const symbol[]{ "based_literal" };
    symbol_scope<based_literal> _(*this, symbol);

    os << "base: " << node.base << ", "
       << "integer: " << node.number.integer_part;

    if(!node.number.fractional_part.empty()) {
        os << ", fraction: " << node.number.fractional_part;
    }

    if(!node.number.exponent.empty()) {
        os << ", exp: " << node.number.exponent;
    }

    using kind_specifier = ast::based_literal::kind_specifier;

    os << ", type: ";
    switch(node.number.kind_type) {
        case kind_specifier::integer: { os << "integer"; break; }
        case kind_specifier::real:    { os << "real";    break; }
        default:                        os << "INVALID";
    }
}


void printer::operator()(binding_indication const &node)
{
    static char const symbol[]{ "binding_indication" };
    symbol_scope<binding_indication> _(*this, symbol);

    auto const print_assoc = [this](ast::association_list const& list) {
        auto const N = list.size() - 1;
        unsigned i = 0;
        for(auto const& association_element : list) {
            (*this)(association_element);
            if(i++ != N) {
                os << ",\n";
            }
        }
    };

    if(node.entity_aspect) {
        (*this)(*node.entity_aspect);
    }

    bool generic_map_association = false;
    if(node.generic_map_aspect.association_list.size() > 0) {
        static char const symbol[]{ "generic map" };

        if(node.entity_aspect) { os << "\n"; }
        symbol_scope<ast::association_list> _(*this, symbol);

        print_assoc(node.generic_map_aspect.association_list);
        generic_map_association = true;
    }

    if(node.port_map_aspect.association_list.size() > 0) {
        static char const symbol[]{ "port map" };

        if(node.entity_aspect || generic_map_association) { os << "\n"; }
        symbol_scope<ast::association_list> _(*this, symbol);

        print_assoc(node.port_map_aspect.association_list);
    }
}


void printer::operator()(bit_string_literal const &node)
{
    static char const symbol[]{ "bit_string_literal" };
    symbol_scope<bit_string_literal> _(*this, symbol);

    using base_specifier = bit_string_literal::base_specifier;

    os << "base: ";

    switch(node.base_type) {
        case base_specifier::bin: os << "bin"; break;
        case base_specifier::oct: os << "oct"; break;
        case base_specifier::hex: os << "hex"; break;
        default:                  os << "INVALID";
    }

    os << ", literal: " << node.literal;
}


void printer::operator()(block_configuration const &node)
{
    static char const symbol[]{ "block_configuration" };
    symbol_scope<block_configuration> _(*this, symbol);

    (*this)(node.block_specification);

    if(node.use_clause_list.size() > 0) {
        os << "\n";
        auto const N = node.use_clause_list.size() - 1;
        unsigned i = 0;
        for(auto const& use_clause : node.use_clause_list) {
            (*this)(use_clause);
            if(i++ != N) {
                os << ",\n";
            }
        }
    }

    if(node.configuration_item_list.size() > 0) {
        os << "\n";
        auto const N = node.configuration_item_list.size() - 1;
        unsigned i = 0;
        for(auto const& configuration_item : node.configuration_item_list) {
            (*this)(configuration_item);
            if(i++ != N) {
                os << ",\n";
            }
        }
    }
}


void printer::operator()(block_declarative_item const &node)
{
    static char const symbol[]{ "block_declarative_item" };
    symbol_scope<block_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(block_declarative_part const &node)
{
    static char const symbol[]{ "block_declarative_part" };
    symbol_scope<block_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& block_declarative_item : node) {
        (*this)(block_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(block_header const &node)
{
    static char const symbol[]{ "block_header" };
    symbol_scope<block_header> _(*this, symbol);

    if(node.generic_part) {
        auto const& generic_part = *node.generic_part;
        (*this)(generic_part.generic_clause);
        if(generic_part.generic_map_aspect) {
            os << "\n";
            (*this)(*generic_part.generic_map_aspect);
        }
    }

    if(node.port_part) {
        auto const& port_part = *node.port_part;
        if(node.generic_part) { os << "\n"; }
        (*this)(port_part.port_clause);
        if(port_part.port_map_aspect) {
            os << "\n";
            (*this)(*port_part.port_map_aspect);
        }
    }
}


void printer::operator()(block_specification const &node)
{
    static char const symbol[]{ "block_specification" };
    symbol_scope<block_specification> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::name const& name) {
            (*this)(name);
        },
        [this](ast::block_specification_chunk const& chunk) {
            (*this)(chunk.label);
            if(chunk.index_specification) {
                os << "\n";
                (*this)(*chunk.index_specification);
            }
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    );
}


void printer::operator()(block_statement const &node)
{
    static char const symbol[]{ "block_statement" };
    symbol_scope<block_statement> _(*this, symbol);

    (*this)(node.label);
    os << "\n";

    if(node.guard_expression) {
        (*this)(*node.guard_expression);
        os << "\n";
    }

    if(node.header.generic_part || node.header.port_part) {
        (*this)(node.header);
        os << "\n";
    }

    if(!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << "\n";
    }

    if(!node.statement_part.empty()) {
        (*this)(node.statement_part);
        os << "\n";
    }

    if(node.end_label) {
        (*this)(*node.end_label);
    }
}


void printer::operator()(block_statement_part const &node)
{
    static char const symbol[]{ "block_statement_part" };
    symbol_scope<block_statement_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& concurrent_statement : node) {
        (*this)(concurrent_statement);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(case_statement const &node)
{
    static char const symbol[]{ "case_statement" };
    symbol_scope<case_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    (*this)(node.expression);
    os << "\n";

    auto const N = node.alternatives.size() - 1;
    unsigned i = 0;
    for(auto const& case_statement_alternative : node.alternatives) {
        (*this)(case_statement_alternative);
        if(i++ != N) {
            os << ",\n";
        }
    }

    if(node.end_label) {
        os << "\n";
        (*this)(*node.end_label);
    }
}


void printer::operator()(case_statement_alternative const &node)
{
    static char const symbol[]{ "case_statement_alternative" };
    symbol_scope<case_statement_alternative> _(*this, symbol);

    (*this)(node.choices);
    os << "\n";
    (*this)(node.sequence_of_statements);
}


void printer::operator()(character_literal const &node)
{
    static char const symbol[]{ "character_literal" };
    symbol_scope<character_literal> _(*this, symbol);

    os << "'" << node.literal << "'";
}


void printer::operator()(choice const &node)
{
    static char const symbol[]{ "choice" };
    symbol_scope<choice> _(*this, symbol);
    visit(node);
}


void printer::operator()(choices const &node)
{
    static char const symbol[]{ "choices" };
    symbol_scope<choices> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& choice : node) {
        (*this)(choice);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(component_configuration const &node)
{
    static char const symbol[]{ "component_configuration" };
    symbol_scope<component_configuration> _(*this, symbol);

    (*this)(node.component_specification);

    if(node.binding_indication) {
        os << "\n";
        (*this)(*node.binding_indication);
    }

    if(node.block_configuration) {
        os << "\n";
        (*this)(*node.block_configuration);
    }
}


void printer::operator()(component_declaration const &node)
{
    static char const symbol[]{ "component_declaration" };
    symbol_scope<component_declaration> _(*this, symbol);

    (*this)(node.identifier);

    if(node.local_generic_clause) {
        os << "\n";
        (*this)(*node.local_generic_clause);
    }

    if(node.local_port_clause) {
        os << "\n";
        (*this)(*node.local_port_clause);
    }

    if(node.name) {
        os << "\n";
        (*this)(*node.name);
    }
}


void printer::operator()(component_instantiation_statement const &node)
{
    static char const symbol[]{ "component_instantiation_statement" };
    symbol_scope<component_instantiation_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    (*this)(node.instantiated_unit);

    if(node.generic_map_aspect) {
        os << "\n";
        (*this)(*node.generic_map_aspect);
    }

    if(node.port_map_aspect) {
        os << "\n";
        (*this)(*node.port_map_aspect);
    }
}


void printer::operator()(component_specification const &node)
{
    static char const symbol[]{ "component_specification" };
    symbol_scope<component_specification> _(*this, symbol);

    (*this)(node.instantiation_list);
    os << "\n";
    (*this)(node.component_name);
}


void printer::operator()(composite_type_definition const &node)
{
    static char const symbol[]{ "composite_type_definition" };
    symbol_scope<composite_type_definition> _(*this, symbol);
    visit(node);
}


void printer::operator()(concurrent_assertion_statement const &node)
{
    static char const symbol[]{ "concurrent_assertion_statement" };
    symbol_scope<concurrent_assertion_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
    }

    if(node.postponed) { os << "\nPOSTPONED,"; }

    if(node.label || node.postponed) { os << "\n"; }
    (*this)(node.assertion);
}


void printer::operator()(concurrent_procedure_call_statement const &node)
{
    static char const symbol[]{ "concurrent_procedure_call_statement" };
    symbol_scope<concurrent_procedure_call_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
    }

    if(node.postponed) { os << "\nPOSTPONED,"; }

    if(node.label || node.postponed) { os << "\n"; }
    (*this)(node.procedure_call);
}


void printer::operator()(concurrent_signal_assignment_statement const &node)
{
    static char const symbol[]{ "concurrent_signal_assignment_statement" };
    symbol_scope<concurrent_signal_assignment_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
    }

    if(node.postponed) { os << "\nPOSTPONED,"; }

    if(node.label || node.postponed) { os << "\n"; }
    util::visit_in_place(
        node.signal_assignment,
        [this](ast::conditional_signal_assignment const& signal_assignment) {
            (*this)(signal_assignment);
        },
        [this](ast::selected_signal_assignment const& signal_assignment) {
            (*this)(signal_assignment);
        }
    );
}


void printer::operator()(concurrent_statement const &node)
{
    static char const symbol[]{ "concurrent_statement" };
    symbol_scope<concurrent_statement> _(*this, symbol);
    visit(node);
}


void printer::operator()(condition_clause const &node)
{
    static char const symbol[]{ "condition_clause" };
    symbol_scope<condition_clause> _(*this, symbol);
    (*this)(node.condition);
}


void printer::operator()(conditional_signal_assignment const &node)
{
    static char const symbol[]{ "conditional_signal_assignment" };
    symbol_scope<conditional_signal_assignment> _(*this, symbol);

    (*this)(node.target);
    os << "\n";
    (*this)(node.options);
    os << "\n";
    (*this)(node.conditional_waveforms);
}


void printer::operator()(conditional_waveforms const &node)
{
    static char const symbol[]{ "conditional_waveforms" };
    symbol_scope<conditional_waveforms> _(*this, symbol);

    if(node.chunks.size() > 0) {
        auto const N = node.chunks.size() - 1;
        unsigned i = 0;
        for(auto const& chunk : node.chunks) {
            (*this)(chunk.waveform);
            os << ",\n";
            (*this)(chunk.condition);
            if(i++ != N) {
                os << ",\n";
            }
        }
        os << "\n";
    }

    (*this)(node.waveform);

    if(node.condition) {
        os << "\n";
        (*this)(*node.condition);
    }
}


void printer::operator()(configuration_declaration const &node)
{
    static char const symbol[]{ "configuration_declaration" };
    symbol_scope<configuration_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";

    (*this)(node.entity_name);
    os << "\n";

    if(!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << "\n";
    }

    (*this)(node.block_configuration);

    if(node.end_label) {
        os << "\n";
        (*this)(*node.end_label);
    }
}


void printer::operator()(configuration_declarative_item const &node)
{
    static char const symbol[]{ "configuration_declarative_item" };
    symbol_scope<configuration_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(configuration_declarative_part const &node)
{
    static char const symbol[]{ "configuration_declarative_part" };
    symbol_scope<configuration_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& configuration_declarative_item : node) {
        (*this)(configuration_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(configuration_item const &node)
{
    static char const symbol[]{ "configuration_item" };
    symbol_scope<configuration_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(configuration_specification const &node)
{
    static char const symbol[]{ "configuration_specification" };
    symbol_scope<configuration_specification> _(*this, symbol);

    (*this)(node.component_specification);
    os << "\n";
    (*this)(node.binding_indication);
}


void printer::operator()(constant_declaration const &node)
{
    static char const symbol[]{ "constant_declaration" };
    symbol_scope<constant_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << "\n";

    (*this)(node.subtype_indication);

    if(node.expression) {
        os << "\n";
        (*this)(*node.expression);
    }
}


void printer::operator()(constrained_array_definition const &node)
{
    static char const symbol[]{ "constrained_array_definition" };
    symbol_scope<constrained_array_definition> _(*this, symbol);

    (*this)(node.index_constraint);
    os << "\n";
    (*this)(node.element_subtype_indication);
}


void printer::operator()(constraint const &node)
{
    static char const symbol[]{ "constraint" };
    symbol_scope<constraint> _(*this, symbol);

    visit(node);
}


void printer::operator()(context_clause const &node)
{
    static char const symbol[]{ "context_clause" };
    symbol_scope<context_clause> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& context_item : node) {
        (*this)(context_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(context_item const &node)
{
    static char const symbol[]{ "context_item" };
    symbol_scope<context_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(decimal_literal const &node)
{
    static char const symbol[]{ "decimal_literal" };
    symbol_scope<decimal_literal> _(*this, symbol);

    using kind_specifier = decimal_literal::kind_specifier;


    os << "literal: " << node.literal << ", type: ";

    switch(node.kind_type) {
        case kind_specifier::integer: os << "integer"; break;
        case kind_specifier::real:    os << "real";    break;
        default:                      os << "INVALID";
    }
}


void printer::operator()(delay_mechanism const &node)
{
    static char const symbol[]{ "delay_mechanism" };
    symbol_scope<delay_mechanism> _(*this, symbol);

    switch(node.delay_type) {
        case ast::keyword_token::INERTIAL: {
            os << "INERTIAL_DELAY";
            break;
        }
        case ast::keyword_token::TRANSPORT: {
            os << "TRANSPORT_DELAY";
            break;
        }
        default:
            os << "INVALID";
    }

    if(node.time_expression) {
        os << "\n";
        (*this)(*node.time_expression);
    }
}


void printer::operator()(design_file const &node)
{
    static char const symbol[]{ "design_file" };
    symbol_scope<design_file> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& design_unit : node) {
        (*this)(design_unit);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(design_unit const &node)
{
    static char const symbol[]{ "design_unit" };
    symbol_scope<design_unit> _(*this, symbol);

    (*this)(node.context_clause);
    os << "\n";

    (*this)(node.library_unit);
}


void printer::operator()(designator const &node)
{
    static char const symbol[]{ "designator" };
    symbol_scope<designator> _(*this, symbol);
    visit(node);
}


void printer::operator()(disconnection_specification const &node)
{
    static char const symbol[]{ "disconnection_specification" };
    symbol_scope<disconnection_specification> _(*this, symbol);

    (*this)(node.guarded_signal_specification);
    os << "\n";
    (*this)(node.time_expression);
}


void printer::operator()(discrete_range const &node)
{
    static char const symbol[]{ "discrete_range" };
    symbol_scope<discrete_range> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::subtype_indication const& discrete_subtype_indication) {
            (*this)(discrete_subtype_indication);
        },
        [this](ast::range const& range) {
            (*this)(range);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    );
}


void printer::operator()(element_association const &node)
{
    static char const symbol[]{ "element_association" };
    symbol_scope<element_association> _(*this, symbol);

    if(!node.choices.empty()) {
        (*this)(node.choices);
        os << "\n";
    }

    (*this)(node.expression);
}


void printer::operator()(element_declaration const &node)
{
    static char const symbol[]{ "element_declaration" };
    symbol_scope<element_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << "\n";
    (*this)(node.element_subtype_definition);
}


void printer::operator()(entity_aspect const &node)
{
    static char const symbol[]{ "entity_aspect" };
    symbol_scope<entity_aspect> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::entity_aspect_entity const& entity) {
            static char const symbol[]{ "entity_aspect::entity" };
            symbol_scope<entity_aspect_entity> _(*this, symbol);
            (*this)(entity.name);
            if(entity.architecture_identifier) {
                os << "\n";
                (*this)(*entity.architecture_identifier);
            }
        },
        [this](ast::entity_aspect_configuration const& configuration) {
            static char const symbol[]{ "entity_aspect::configuration" };
            symbol_scope<entity_aspect_configuration> _(*this, symbol);
            (*this)(configuration.name);
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    );
}


void printer::operator()(entity_class_entry_list const &node)
{
    static char const symbol[]{ "entity_class_entry_list" };
    symbol_scope<entity_class_entry_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& token : node) {
        (*this)(token);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(entity_declaration const &node)
{
    static char const symbol[]{ "entity_declaration" };
    symbol_scope<entity_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";

    if(node.header.formal_generic_clause || node.header.formal_port_clause) {
        (*this)(node.header);
        os << "\n";
    }

    if(!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << "\n";
    }

    if(node.statement_part) {
        (*this)(*node.statement_part);
        os << "\n";
    }

    if(node.name) {
        (*this)(*node.name);
    }
}


void printer::operator()(entity_declarative_item const &node)
{
    static char const symbol[]{ "entity_declarative_item" };
    symbol_scope<entity_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(entity_declarative_part const &node)
{
    static char const symbol[]{ "entity_declarative_part" };
    symbol_scope<entity_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& entity_declarative_item : node) {
        (*this)(entity_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(entity_designator const &node)
{
    static char const symbol[]{ "entity_designator" };
    symbol_scope<entity_designator> _(*this, symbol);

    (*this)(node.entity_tag);
    if(node.signature) {
        os << "\n";
        (*this)(*node.signature);
    }
}


void printer::operator()(entity_header const &node)
{
    static char const symbol[]{ "entity_header" };
    symbol_scope<entity_header> _(*this, symbol);

    if(node.formal_generic_clause) {
        (*this)(*node.formal_generic_clause);
    }

    if(node.formal_port_clause) {
        if(node.formal_generic_clause) { os << "\n"; }
        (*this)(*node.formal_port_clause);
    }
}


void printer::operator()(entity_name_list const &node)
{
    static char const symbol[]{ "entity_name_list" };
    symbol_scope<entity_name_list> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::entity_designator_list const& entity_designator_list) {
            auto const N = entity_designator_list.size() - 1;
            unsigned i = 0;
            for(auto const& entity_designator : entity_designator_list) {
                (*this)(entity_designator);
                if(i++ != N) {
                    os << ",\n";
                }
            }
        },
        [this](ast::keyword_token token) {
            (*this)(token); // OTHERS | ALL
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    );
}


void printer::operator()(entity_specification const &node)
{
    static char const symbol[]{ "entity_specification" };
    symbol_scope<entity_specification> _(*this, symbol);

    (*this)(node.entity_name_list);
    os << "\n";
    (*this)(node.entity_class);
}


void printer::operator()(entity_statement const &node)
{
    static char const symbol[]{ "entity_statement" };
    symbol_scope<entity_statement> _(*this, symbol);
    visit(node);
}


void printer::operator()(entity_statement_part const &node)
{
    static char const symbol[]{ "entity_statement_part" };
    symbol_scope<entity_statement_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& entity_statement : node) {
        (*this)(entity_statement);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(entity_tag const &node)
{
    static char const symbol[]{ "entity_tag" };
    symbol_scope<entity_tag> _(*this, symbol);
    visit(node);
}


void printer::operator()(enumeration_literal const &node)
{
    static char const symbol[]{ "enumeration_literal" };
    symbol_scope<enumeration_literal> _(*this, symbol);
    visit(node);
}


void printer::operator()(enumeration_type_definition const &node)
{
    static char const symbol[]{ "enumeration_type_definition" };
    symbol_scope<enumeration_type_definition> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& enumeration_literal : node) {
        (*this)(enumeration_literal);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(exit_statement const &node)
{
    static char const symbol[]{ "exit_statement" };
    symbol_scope<exit_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        if(node.loop_label || node.condition) { os << "\n"; }
    }

    if(node.loop_label) {
        (*this)(*node.loop_label);
        if(node.condition) { os << "\n"; }
    }

    if(node.condition) {
        (*this)(*node.condition);
    }
}


void printer::operator()(expression const &node)
{
    static char const symbol[]{ "expression" };
    symbol_scope<expression> _(*this, symbol);

    (*this)(node.relation);

    if(node.rest_list.empty()) {
        return;
    }

    auto const N = node.rest_list.size() - 1;
    unsigned i = 0;
    for(auto const& chunk : node.rest_list) {
        os << ",\n" << "(operator: " << chunk.logical_operator << "),\n";
        (*this)(chunk.relation);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(factor_binary_operation const& node)
{
    static char const symbol[]{ "factor_binary_operation" };
    symbol_scope<factor_binary_operation> _(*this, symbol);

    visit(node.primary_lhs);

    os << "\n" << "(operator: " << node.operator_ << "),\n";

    visit(node.primary_rhs);
}


void printer::operator()(factor_unary_operation const& node)
{
    static char const symbol[]{ "factor_unary_operation" };
    symbol_scope<factor_unary_operation> _(*this, symbol);

    os << "(operator: " << node.operator_ << "),\n";
    visit(node.primary);
}

void printer::operator()(factor const &node)
{
    static char const symbol[]{ "factor" };
    symbol_scope<factor> _(*this, symbol);
    visit(node);
}


void printer::operator()(file_declaration const &node)
{
    static char const symbol[]{ "file_declaration" };
    symbol_scope<file_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << "\n";

    (*this)(node.subtype_indication);

    if(node.file_open_information) {
        os << "\n";
        (*this)(*node.file_open_information);
    }
}


void printer::operator()(file_open_information const &node)
{
    static char const symbol[]{ "file_open_information" };
    symbol_scope<file_open_information> _(*this, symbol);

    if(node.file_open_kind_expression) {
        (*this)(*node.file_open_kind_expression);
        os << "\n";
    }
    (*this)(node.file_logical_name);
}


void printer::operator()(formal_part const &node)
{
    static char const symbol[]{ "formal_part" };
    symbol_scope<formal_part> _(*this, symbol);

    auto const visit_name = [this](auto const& ctx_name) {
        static char const symbol[]{ "{function_name|type_mark}" };
        symbol_scope<name> _(*this, symbol);
        (*this)(ctx_name);
    };

    auto const visit_formal_designator = [this](auto const& ctx_name) {
        static char const symbol[]{ "formal_designator" };
        symbol_scope<name> _(*this, symbol);
        (*this)(ctx_name);
    };

    /* parsed as (name) list
     * formal_designator ::=
     *    | function_name ( formal_designator )
     *    | type_mark ( formal_designator ) */
    switch(node.context_tied_names.size()) {

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


void printer::operator()(function_call const &node)
{
    static char const symbol[]{ "function_call" };
    symbol_scope<function_call> _(*this, symbol);

    (*this)(node.function_name);

    if(node.actual_parameter_part) {
        os << "\n";
        {
            static char const symbol[]{ "actual_parameter_part" };
            symbol_scope<function_call> _(*this, symbol);

            (*this)(*node.actual_parameter_part);
        }
    }
}


void printer::operator()(generate_statement const &node)
{
    static char const symbol[]{ "generate_statement" };
    symbol_scope<generate_statement> _(*this, symbol);

    (*this)(node.label);
    os << "\n";

    (*this)(node.generation_scheme);
    os << "\n";


    if(node.block_declarative_parts.size() > 0) {
        (*this)(node.block_declarative_parts);
        os << "\n";
    }

    if(node.concurrent_statements.size() > 0) {
        auto const N = node.concurrent_statements.size() - 1;
        unsigned i = 0;
        for(auto const& concurrent_statement : node.concurrent_statements) {
            (*this)(concurrent_statement);
            if(i++ != N) {
                os << ",\n";
            }
        }
    }

    if(node.end_label) {
        os << "\n";
        (*this)(*node.end_label);
    }
}


void printer::operator()(generation_scheme const &node)
{
    static char const symbol[]{ "generation_scheme" };
    symbol_scope<generation_scheme> _(*this, symbol);
    visit(node);
}


void printer::operator()(generic_clause const &node)
{
    static char const symbol[]{ "generic_clause" };
    symbol_scope<generic_clause> _(*this, symbol);
    (*this)(node.generic_list);
}


void printer::operator()(generic_map_aspect const &node)
{
    static char const symbol[]{ "generic_map_aspect" };
    symbol_scope<generic_map_aspect> _(*this, symbol);
    (*this)(node.association_list);
}


void printer::operator()(group_constituent const &node)
{
    static char const symbol[]{ "group_constituent" };
    symbol_scope<group_constituent> _(*this, symbol);
    visit(node);
}


void printer::operator()(group_constituent_list const &node)
{
    static char const symbol[]{ "group_constituent_list" };
    symbol_scope<group_constituent_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& group_constituent : node) {
        (*this)(group_constituent);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(group_declaration const &node)
{
    static char const symbol[]{ "group_declaration" };
    symbol_scope<group_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";
    (*this)(node.group_template_name);
    os << "\n";
    (*this)(node.group_constituent_list);
}


void printer::operator()(group_template_declaration const &node)
{
    static char const symbol[]{ "group_template_declaration" };
    symbol_scope<group_template_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";
    (*this)(node.entity_class_entry_list);
}


void printer::operator()(guarded_signal_specification const &node)
{
    static char const symbol[]{ "guarded_signal_specification" };
    symbol_scope<guarded_signal_specification> _(*this, symbol);

    (*this)(node.guarded_signal_list);
    os << "\n";
    (*this)(node.type_mark);
}


void printer::operator()(identifier const &node)
{
    static char const symbol[]{ "identifier" };
    symbol_scope<identifier> _(*this, symbol);

    /* Note, even if identifier following the BNF is variant, it's treated as
     * as common identifier for {basic, extended}_identifier */
    os << node.name;
}


void printer::operator()(identifier_list const &node)
{
    static char const symbol[]{ "identifier_list" };
    symbol_scope<identifier_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& identifier : node) {
        (*this)(identifier);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(if_statement const &node)
{
    static char const symbol[]{ "if_statement" };
    symbol_scope<if_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    (*this)(node.if_condition);
    os << "\nTHAN:\n";

    (*this)(node.then_sequence_of_statements);

    if(node.elseif_chunks.size() > 0) {
        os << "\n";
        auto const N = node.elseif_chunks.size() - 1;
        unsigned i = 0;
        for(auto const& elsif_chunk : node.elseif_chunks) {
            os << "ELSIF:\n";
            (*this)(elsif_chunk.condition);
            os << "\nTHAN:\n";
            (*this)(elsif_chunk.sequence_of_statements);
            if(i++ != N) {
                os << "\n";
            }
        }
    }

    if(node.else_sequence_of_statements.size() > 0) {
        os << "\nELSE:\n";
        (*this)(node.else_sequence_of_statements);
    }

    if(node.end_label) {
        os << "\n";
        (*this)(*node.end_label);
    }
}


void printer::operator()(index_constraint const &node)
{
    static char const symbol[]{ "index_constraint" };
    symbol_scope<index_constraint> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& discrete_range : node) {
        (*this)(discrete_range);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(index_specification const &node)
{
    static char const symbol[]{ "index_specification" };
    symbol_scope<index_specification> _(*this, symbol);
    visit(node);
}


void printer::operator()(index_subtype_definition const &node)
{
    static char const symbol[]{ "index_subtype_definition" };
    symbol_scope<index_subtype_definition> _(*this, symbol);

    (*this)(node.type_mark);
}


void printer::operator()(indexed_name const &node)
{
    static char const symbol[]{ "indexed_name" };
    symbol_scope<indexed_name> _(*this, symbol);

    (*this)(node.prefix);
    os << "\n";

    auto const N = node.expression_list.size() - 1;
    unsigned i = 0;
    for(auto const& expression : node.expression_list) {
        (*this)(expression);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(instantiated_unit const &node)
{
    static char const symbol[]{ "instantiated_unit" };
    symbol_scope<instantiated_unit> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::instantiated_unit_component const& component) {
            static char const symbol[]{ "component" };
            symbol_scope<instantiated_unit_component> _(*this, symbol);
            (*this)(component.name);
        },
        [this](ast::instantiated_unit_entity const& entity) {
            static char const symbol[]{ "entity" };
            symbol_scope<instantiated_unit_entity> _(*this, symbol);
            (*this)(entity.name);
            if(entity.architecture_identifier) {
                os << "\n";
                (*this)(*entity.architecture_identifier);
            }
        },
        [this](ast::instantiated_unit_configuration const& configuration) {
            static char const symbol[]{ "configuration" };
            symbol_scope<instantiated_unit_configuration> _(*this, symbol);
            (*this)(configuration.name);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }
    );
}


void printer::operator()(instantiation_list const &node)
{
    static char const symbol[]{ "instantiation_list" };
    symbol_scope<instantiation_list> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::instantiation_label_list const& instantiation_label_list) {
            auto const N = instantiation_label_list.size() - 1;
            unsigned i = 0;
            for(auto const& label : instantiation_label_list) {
                (*this)(label);
                if(i++ != N) {
                    os << ",\n";
                }
            }
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        },
        [this](ast::nullary const& nullary) {
            (*this)(nullary);
        }

    );
}


void printer::operator()(interface_constant_declaration const &node)
{
    static char const symbol[]{ "interface_constant_declaration" };
    symbol_scope<interface_constant_declaration> _(*this, symbol);

    if(node.constant) { os << "(constant)\n"; }

    (*this)(node.identifier_list);
    os << "\n";

    if(node.in) { os << "(in)\n";  }

    (*this)(node.subtype_indication);

    if(node.static_expression) {
        os << "\n";
        (*this)(*node.static_expression);
    }
}


void printer::operator()(interface_declaration const &node)
{
    static char const symbol[]{ "interface_declaration" };
    symbol_scope<interface_declaration> _(*this, symbol);
    visit(node);
}


void printer::operator()(interface_file_declaration const &node)
{
    static char const symbol[]{ "interface_file_declaration" };
    symbol_scope<interface_file_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << "\n";
    (*this)(node.subtype_indication);
}


void printer::operator()(interface_list const &node)
{
    static char const symbol[]{ "interface_list" };
    symbol_scope<interface_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& interface_element : node) {
        (*this)(interface_element);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(interface_signal_declaration const &node)
{
    static char const symbol[]{ "interface_signal_declaration" };
    symbol_scope<interface_signal_declaration> _(*this, symbol);

    if(node.signal) { os << "(signal)\n"; }

    (*this)(node.identifier_list);
    os << "\n";

    if(node.mode) {
        (*this)(*node.mode);
        os << "\n";
    }

    (*this)(node.subtype_indication);

    if(node.bus) { os << "\n(bus)"; }

    if(node.static_expression) {
        os << "\n";
        (*this)(*node.static_expression);
    }
}


void printer::operator()(interface_variable_declaration const &node)
{
    static char const symbol[]{ "interface_variable_declaration" };
    symbol_scope<interface_variable_declaration> _(*this, symbol);

    if(node.VARIABLE) { os << "(variable)\n"; }

    (*this)(node.identifier_list);
    os << "\n";

    if(node.mode) {
        (*this)(*node.mode);
        os << "\n";
    }

    (*this)(node.subtype_indication);

    if(node.static_expression) {
        os << "\n";
        (*this)(*node.static_expression);
    }
}


void printer::operator()(iteration_scheme const &node)
{
    static char const symbol[]{ "iteration_scheme" };
    symbol_scope<iteration_scheme> _(*this, symbol);
    visit(node);
}


void printer::operator()(library_clause const &node)
{
    static char const symbol[]{ "library_clause" };
    symbol_scope<library_clause> _(*this, symbol);

    auto const N = node.logical_name_list.size() - 1;
    unsigned i = 0;
    for(auto const& logical_name : node.logical_name_list) {
        (*this)(logical_name);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(library_unit const &node)
{
    static char const symbol[]{ "library_unit" };
    symbol_scope<library_unit> _(*this, symbol);
    visit(node);
}


void printer::operator()(literal const &node)
{
    static char const symbol[]{ "literal" };
    symbol_scope<literal> _(*this, symbol);
    visit(node);
}


void printer::operator()(loop_statement const &node)
{
    static char const symbol[]{ "loop_statement" };
    symbol_scope<loop_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    if(node.iteration_scheme) {
        (*this)(*node.iteration_scheme);
        os << "\n";
    }

    (*this)(node.sequence_of_statements);

    if(node.end_label) {
        os << "\n";
        (*this)(*node.end_label);
    }
}


void printer::operator()(name const &node)
{
    static char const symbol[]{ "name" };
    symbol_scope<name> _(*this, symbol);
    visit(node);
}


void printer::operator()(next_statement const &node)
{
    static char const symbol[]{ "next_statement" };
    symbol_scope<next_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        if(node.loop_label || node.condition) { os << "\n"; }
    }

    if(node.loop_label) {
        (*this)(*node.loop_label);
        if(node.condition) { os << "\n"; }
    }

    if(node.condition) {
        (*this)(*node.condition);
    }
}


void printer::operator()(null_statement const &node)
{
    static char const symbol[]{ "null_statement" };
    symbol_scope<null_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
    }
}


void printer::operator()(numeric_literal const &node)
{
    static char const symbol[]{ "numeric_literal" };
    symbol_scope<numeric_literal> _(*this, symbol);
    visit(node);
}


void printer::operator()(options const &node)
{
    static char const symbol[]{ "options" };
    symbol_scope<options> _(*this, symbol);

    if(node.guarded) {
        os << "GUARDED";
    }
    if(node.delay_mechanism) {
        if(node.guarded) { os << "\n"; }
        (*this)(*node.delay_mechanism);
    }
}


void printer::operator()(package_body const &node)
{
    static char const symbol[]{ "package_body" };
    symbol_scope<package_body> _(*this, symbol);

    (*this)(node.name);
    os << "\n";

    (*this)(node.declarative_part);

    if(node.end_name) {
        os << "\n";
        (*this)(*node.end_name);
    }
}


void printer::operator()(package_body_declarative_item const &node)
{
    static char const symbol[]{ "package_body_declarative_item" };
    symbol_scope<package_body_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(package_body_declarative_part const &node)
{
    static char const symbol[]{ "package_body_declarative_part" };
    symbol_scope<package_body_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& package_body_declarative_item : node) {
        (*this)(package_body_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(package_declaration const &node)
{
    static char const symbol[]{ "package_declaration" };
    symbol_scope<package_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";

    (*this)(node.declarative_part);

    if(node.end_label) {
        os << "\n";
        (*this)(*node.end_label);
    }
}


void printer::operator()(package_declarative_item const &node)
{
    static char const symbol[]{ "package_declarative_item" };
    symbol_scope<package_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(package_declarative_part const &node)
{
    static char const symbol[]{ "package_declarative_part" };
    symbol_scope<package_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& package_declarative_item : node) {
        (*this)(package_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(parameter_specification const &node)
{
    static char const symbol[]{ "parameter_specification" };
    symbol_scope<parameter_specification> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";
    (*this)(node.discrete_range);
}


void printer::operator()(physical_literal const &node)
{
    static char const symbol[]{ "physical_literal" };
    symbol_scope<physical_literal> _(*this, symbol);

    (*this)(node.literal);
    os << ",\n" << "(unit_name: " << node.unit_name << ")";
}


void printer::operator()(physical_type_definition const &node)
{
    static char const symbol[]{ "physical_type_definition" };
    symbol_scope<physical_type_definition> _(*this, symbol);

    (*this)(node.range_constraint);
    os << "\n";
    (*this)(node.primary_unit_declaration);

    auto const N = node.secondary_unit_declarations.size() - 1;
    unsigned i = 0;
    if(node.secondary_unit_declarations.size() != 0) { os << "\n"; }
    for(auto const& secondary_unit_declaration : node.secondary_unit_declarations) {
        (*this)(secondary_unit_declaration);
        if(i++ != N) {
            os << ",\n";
        }
    }

    if(node.physical_type_simple_name) {
        os << "\n";
        (*this)(*node.physical_type_simple_name);
    }
}


void printer::operator()(port_clause const &node)
{
    static char const symbol[]{ "port_clause" };
    symbol_scope<port_clause> _(*this, symbol);
    (*this)(node.port_list);
}


void printer::operator()(port_map_aspect const &node)
{
    static char const symbol[]{ "port_map_aspect" };
    symbol_scope<port_map_aspect> _(*this, symbol);
    (*this)(node.association_list);
}


void printer::operator()(prefix const &node)
{
    static char const symbol[]{ "prefix" };
    symbol_scope<prefix> _(*this, symbol);
    visit(node);
}


void printer::operator()(primary const &node)
{
    static char const symbol[]{ "primary" };
    symbol_scope<primary> _(*this, symbol);
    visit(node);
}


void printer::operator()(primary_unit const &node)
{
    static char const symbol[]{ "primary_unit" };
    symbol_scope<primary_unit> _(*this, symbol);
    visit(node);
}


void printer::operator()(procedure_call const &node)
{
    static char const symbol[]{ "procedure_call" };
    symbol_scope<procedure_call> _(*this, symbol);

    (*this)(node.procedure_name);

    if(node.actual_parameter_part) {
        os << "\n";
        {
            static char const symbol[]{ "actual_parameter_part" };
            symbol_scope<function_call> _(*this, symbol);

            (*this)(*node.actual_parameter_part);
        }
    }
}


void printer::operator()(procedure_call_statement const &node)
{
    static char const symbol[]{ "procedure_call_statement" };
    symbol_scope<procedure_call_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }
    (*this)(node.procedure_call);
}


void printer::operator()(process_declarative_item const &node)
{
    static char const symbol[]{ "process_declarative_item" };
    symbol_scope<process_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(process_declarative_part const &node)
{
    static char const symbol[]{ "process_declarative_part" };
    symbol_scope<process_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& process_declarative_item : node) {
        (*this)(process_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(process_statement const &node)
{
    static char const symbol[]{ "process_statement" };
    symbol_scope<process_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    if(node.postponed) { os << "POSTPONED\n"; }

    if(!node.sensitivity_list.empty()) {
        (*this)(node.sensitivity_list);
        os << "\n";
    }

    if(!node.declarative_part.empty()) {
        (*this)(node.declarative_part);
        os << "\n";
    }

    if(!node.statement_part.empty()) {
        (*this)(node.statement_part);
    }

    if(node.end_postponed) { os << "\nPOSTPONED"; }

    if(node.label) {
        os << "\n";
        (*this)(*node.label);
    }
}


void printer::operator()(qualified_expression const &node)
{
    static char const symbol[]{ "qualified_expression" };
    symbol_scope<qualified_expression> _(*this, symbol);

    (*this)(node.type_mark);
    os << "\n";

    util::visit_in_place(
        node.aggregate_or_expression,
        [this](ast::expression const& expr) {
            (*this)(expr);
        },
        [this](ast::aggregate const& aggregate) {
            (*this)(aggregate);
        },
        [this](ast::nullary nullary) {
            (*this)(nullary);
        }
    );
}


void printer::operator()(range const &node) // aka range_constraint
{
    static char const symbol[]{ "range" };
    symbol_scope<range> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](range_attribute_name const &name) {
            (*this)(name);
        },
        [this](range_expression const &expr) {
            (*this)(expr.lhs);
            os << "\n";
            (*this)(expr.direction);
            os << "\n";
            (*this)(expr.rhs);
        }
    );
}


void printer::operator()(record_type_definition const &node)
{
    static char const symbol[]{ "record_type_definition" };
    symbol_scope<record_type_definition> _(*this, symbol);

    auto const N = node.element_declarations.size() - 1;
    unsigned i = 0;
    for(auto const& element_declaration : node.element_declarations) {
        (*this)(element_declaration);
        if(i++ != N) {
            os << ",\n";
        }
    }
    if(node.name) {
        os << "\n";
        (*this)(*node.name);
    }
}


void printer::operator()(relation const &node)
{
    static char const symbol[]{ "relation" };
    symbol_scope<relation> _(*this, symbol);

    (*this)(node.shift_expression);

    if(!node.rest) {
        return;
    }

    auto const& chunk = *node.rest;
    os << ",\n" << "(operator: " << chunk.relational_operator << "),\n";
    (*this)(chunk.shift_expression);
}


void printer::operator()(report_statement const &node)
{
    static char const symbol[]{ "report_statement" };
    symbol_scope<report_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    (*this)(node.report);

    if(node.severity) {
        os << "\n";
        (*this)(*node.severity);
    }
}


void printer::operator()(return_statement const &node)
{
    static char const symbol[]{ "return_statement" };
    symbol_scope<report_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
    }

    if(node.expression) {
        if(node.label) { os << "\n"; }
        (*this)(*node.expression);
    }
}


void printer::operator()(scalar_type_definition const &node)
{
    static char const symbol[]{ "scalar_type_definition" };
    symbol_scope<scalar_type_definition> _(*this, symbol);
    visit(node);
}


void printer::operator()(secondary_unit const &node)
{
    static char const symbol[]{ "secondary_unit" };
    symbol_scope<secondary_unit> _(*this, symbol);
    visit(node);
}


void printer::operator()(secondary_unit_declaration const &node)
{
    static char const symbol[]{ "secondary_unit_declaration" };
    symbol_scope<secondary_unit_declaration> _(*this, symbol);

    (*this)(node.identifier);
    os << "\n";
    (*this)(node.physical_literal);
}


void printer::operator()(selected_name const &node)
{
    static char const symbol[]{ "selected_name" };
    symbol_scope<selected_name> _(*this, symbol);

    (*this)(node.prefix);
    os << "\n";
    (*this)(node.suffix);
}


void printer::operator()(selected_signal_assignment const &node)
{
    static char const symbol[]{ "selected_signal_assignment" };
    symbol_scope<selected_signal_assignment> _(*this, symbol);

    (*this)(node.expression);
    os << "\n";

    (*this)(node.target);
    os << "\n";

    (*this)(node.options);
    os << "\n";

    (*this)(node.selected_waveforms);
}


void printer::operator()(selected_waveforms const &node)
{
    static char const symbol[]{ "selected_waveforms" };
    symbol_scope<selected_waveforms> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& selected_waveform : node) {
        (*this)(selected_waveform.waveform);
        os << "\n";
        (*this)(selected_waveform.choices);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(sensitivity_clause const &node)
{
    static char const symbol[]{ "sensitivity_clause" };
    symbol_scope<sensitivity_clause> _(*this, symbol);
    (*this)(node.sensitivity_list);
}


void printer::operator()(sensitivity_list const& node)
{
    static char const symbol[]{ "sensitivity_list" };
    symbol_scope<sensitivity_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& signal_name : node) {
        (*this)(signal_name);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(sequence_of_statements const &node)
{
    static char const symbol[]{ "sequence_of_statements" };
    symbol_scope<sequence_of_statements> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& sequential_statement : node) {
        (*this)(sequential_statement);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(sequential_statement const &node)
{
    static char const symbol[]{ "sequential_statement" };
    symbol_scope<sequential_statement> _(*this, symbol);
    visit(node);
}


void printer::operator()(shift_expression const &node)
{
    static char const symbol[]{ "shift_expression" };
    symbol_scope<shift_expression> _(*this, symbol);

    (*this)(node.simple_expression);

    if(!node.rest) {
        return;
    }

    auto const& chunk = *node.rest;
    os << ",\n" << "(operator: " << chunk.shift_operator << "),\n";
    (*this)(chunk.simple_expression);
}


void printer::operator()(signal_assignment_statement const &node)
{
    static char const symbol[]{ "signal_assignment_statement" };
    symbol_scope<signal_assignment_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }

    (*this)(node.target);
    os << "\n";

    if(node.delay_mechanism) {
        (*this)(*node.delay_mechanism);
        os << "\n";
    }

    (*this)(node.waveform);
}


void printer::operator()(signal_declaration const &node)
{
    static char const symbol[]{ "signal_declaration" };
    symbol_scope<signal_declaration> _(*this, symbol);

    (*this)(node.identifier_list);
    os << "\n";

    (*this)(node.subtype_indication);

    if(node.signal_kind) {
        os << "\n";
        (*this)(*node.signal_kind);
    }

    if(node.expression) {
        os << "\n";
        (*this)(*node.expression);
    }
}


void printer::operator()(signal_list_list const& node)
{
    static char const symbol[]{ "signal_list.names" };
    symbol_scope<signal_list_list> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& name : node) {
        visit(name);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(signal_list const &node)
{
    static char const symbol[]{ "signal_list" };
    symbol_scope<signal_list> _(*this, symbol);

    visit(node);
}


void printer::operator()(signature const &node)
{
    static char const symbol[]{ "signature" };
    symbol_scope<signature> _(*this, symbol);

    auto const N = node.parameter_type_list.size() - 1;
    unsigned i = 0;
    for(auto const& type_mark : node.parameter_type_list) {
        (*this)(type_mark);
        if(i++ != N) {
            os << ",\n";
        }
    }

    if(node.return_type) {
        if(node.parameter_type_list.size() != 0) { os << "\n"; }

        static char const symbol[]{ "signature.return_type" };
        symbol_scope<signature> _(*this, symbol);

        (*this)(*node.return_type);
    }
}

void printer::operator()(simple_expression const &node)
{
    static char const symbol[]{ "simple_expression" };
    symbol_scope<simple_expression> _(*this, symbol);

    if(node.sign) { // optional
        os << "sign: " << *node.sign << ",\n";
    }

    (*this)(node.term);

    if(node.rest_list.empty()) {
        return;
    }

    auto const N = node.rest_list.size()- 1;
    unsigned i= 0;
    for(auto const& chunk : node.rest_list) {
        os << ",\n" << "(operator: " << chunk.adding_operator << "),\n";
        (*this)(chunk.term);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(slice_name const &node)
{
    static char const symbol[]{ "slice_name" };
    symbol_scope<slice_name> _(*this, symbol);

    (*this)(node.prefix);
    os << "\n";

    (*this)(node.discrete_range);
}


void printer::operator()(string_literal const &node)
{
    static char const symbol[]{ "string_literal" };
    symbol_scope<string_literal> _(*this, symbol);

    /* Note, following the LRM, if a quotation sign has to be used in a string
     * literal, it is denoted by two double quotes side by side. This must
     * be replaced since string_view is used. */
    os << node.literal;
}


void printer::operator()(subprogram_body const &node)
{
    static char const symbol[]{ "subprogram_body" };
    symbol_scope<subprogram_body> _(*this, symbol);

    (*this)(node.specification);
    os << "\n";

    (*this)(node.declarative_part);
    os << "\n";

    (*this)(node.statement_part);

    if(node.kind) {
        os << "\n";
        (*this)(*node.kind);
    }

    if(node.designator) {
        os << "\n";
        (*this)(*node.designator);
    }
}


void printer::operator()(subprogram_declarative_item const &node)
{
    static char const symbol[]{ "subprogram_declarative_item" };
    symbol_scope<subprogram_declarative_item> _(*this, symbol);
    visit(node);
}


void printer::operator()(subprogram_declarative_part const &node)
{
    static char const symbol[]{ "subprogram_declarative_part" };
    symbol_scope<subprogram_declarative_part> _(*this, symbol);

    auto const N = node.size() - 1;
    unsigned i = 0;
    for(auto const& subprogram_declarative_item : node) {
        (*this)(subprogram_declarative_item);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(subprogram_specification const &node)
{
    static char const symbol[]{ "subprogram_specification" };
    symbol_scope<subprogram_specification> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::subprogram_specification_procedure const& procedure) {
            os << "PROCEDURE\n";
            (*this)(procedure.designator);
            if(procedure.formal_parameter_list) {
                os << "\n";
                (*this)(*procedure.formal_parameter_list);
            }
        },
        [this](ast::subprogram_specification_function const& function) {
            if(function.impure) { os << "IMPURE FUNCTION\n"; }
            else {                os << "PURE FUNCTION\n"; }
            (*this)(function.designator);
            if(function.formal_parameter_list) {
                os << "\n";
                (*this)(*function.formal_parameter_list);
            }
            os << "\n";
            (*this)(function.return_type_mark);
        }
    );
}


void printer::operator()(subtype_declaration const &node)
{
    static char const symbol[]{ "subtype_declaration" };
    symbol_scope<subtype_declaration> _(*this, symbol);
    (*this)(node.identifier);
    os << "\n";
    (*this)(node.subtype_indication);
}


void printer::operator()(subtype_indication const &node)
{
    static char const symbol[]{ "subtype_indication" };
    symbol_scope<subtype_indication> _(*this, symbol);

    auto const visit_type_mark = [this](auto const& type_mark) {
        static char const symbol[]{ "type_mark" };
        symbol_scope<name> _(*this, symbol);
        (*this)(type_mark);
    };

    auto const visit_resolution_function_name = [this](auto const& resolution_function_name) {
        static char const symbol[]{ "resolution_function_name" };
        symbol_scope<name> _(*this, symbol);
        (*this)(resolution_function_name);
    };

    /* parsed as (name) list with trailing constraint
     * subtype_indication ::=
     *     [ resolution_function_name ] type_mark [ constraint ] */
    switch(node.unspecified_name_list.size()) {

        case 1: {
            // BNF: type_mark .... [ constraint ]
            visit_type_mark(node.unspecified_name_list[0]);
            break;
        }

        case 2: {
            // BNF: [ resolution_function_name ] type_mark ... [ constraint ]
            visit_resolution_function_name(node.unspecified_name_list[0]);
            os << "\n";
            visit_type_mark(node.unspecified_name_list[1]);
            break;
        }

        default:
            cxx_bug_fatal("VHDL BNF rules violation, parser rule failed!");
    }

    if(node.constraint) {
        os << "\n";
        (*this)(*node.constraint);
    }
}


void printer::operator()(suffix const &node)
{
    static char const symbol[]{ "suffix" };
    symbol_scope<suffix> _(*this, symbol);
    visit(node);
}


void printer::operator()(target const &node)
{
    static char const symbol[]{ "target" };
    symbol_scope<target> _(*this, symbol);

    boost::apply_visitor(*this, node);
}


void printer::operator()(term const &node)
{
    static char const symbol[]{ "term" };
    symbol_scope<term> _(*this, symbol);

    visit(node.factor);

    if(node.rest_list.empty()) {
        return;
    }

    os << ",\n";

    auto const N = node.rest_list.size() - 1;
    unsigned i = 0;
    for(auto const& term_chunk: node.rest_list) {
        os << "(operator: " << term_chunk.multiplying_operator << "),\n";
        visit(term_chunk.factor);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(timeout_clause const &node)
{
    static char const symbol[]{ "timeout_clause" };
    symbol_scope<timeout_clause> _(*this, symbol);
    (*this)(node.time_expression);
}


void printer::operator()(type_conversion const &node)
{
    static char const symbol[]{ "type_conversion" };
    symbol_scope<type_conversion> _(*this, symbol);
    (*this)(node.type_mark);
    os << "\n";
    (*this)(node.expression);
}


void printer::operator()(type_declaration const &node)
{
    // {full, incomplete}_type_declaration
    static char const symbol[]{ "type_declaration" };
    symbol_scope<type_declaration> _(*this, symbol);
    (*this)(node.identifier);

    if(node.type_definition) {
        os << "\n";
        (*this)(*node.type_definition);
    }
}


void printer::operator()(type_definition const &node)
{
    static char const symbol[]{ "type_definition" };
    symbol_scope<type_definition> _(*this, symbol);
    visit(node);
}


void printer::operator()(unconstrained_array_definition const &node)
{
    static char const symbol[]{ "unconstrained_array_definition" };
    symbol_scope<unconstrained_array_definition> _(*this, symbol);

    for(auto const& index_subtype_definition : node.index_subtype_definitions) {
        (*this)(index_subtype_definition);
        os << "\n";
    }
    (*this)(node.element_subtype_indication);
}


void printer::operator()(use_clause const &node)
{
    static char const symbol[]{ "use_clause" };
    symbol_scope<use_clause> _(*this, symbol);

    auto const N = node.list.size() - 1;
    unsigned i = 0;
    for(auto const& selected_name : node.list) {
        for(auto const& name : selected_name.prefix_list) {
            (*this)(name);
            os << ".\n";
        }
        (*this)(selected_name.suffix);
        if(i++ != N) {
            os << ",\n";
        }
    }
}


void printer::operator()(variable_assignment_statement const &node)
{
    static char const symbol[]{ "variable_assignment_statement" };
    symbol_scope<variable_assignment_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
        os << "\n";
    }
    (*this)(node.target);
    os << "\n";
    (*this)(node.expression);
}


void printer::operator()(variable_declaration const &node)
{
    static char const symbol[]{ "variable_declaration" };
    symbol_scope<variable_declaration> _(*this, symbol);

    if(node.shared) { os << "SHARED\n"; }

    (*this)(node.identifier_list);
    os << "\n";
    (*this)(node.subtype_indication);

    if(node.expression) {
        os << "\n";
        (*this)(*node.expression);
    }
}


void printer::operator()(wait_statement const &node)
{
    static char const symbol[]{ "wait_statement" };
    symbol_scope<wait_statement> _(*this, symbol);

    if(node.label) {
        (*this)(*node.label);
    }
    if(node.sensitivity_clause) {
        if(node.label) { os << "\n"; }
        (*this)(*node.sensitivity_clause);
    }
    if(node.condition_clause) {
        if(node.label || node.sensitivity_clause) { os << "\n"; }
        (*this)(*node.condition_clause);
    }
    if(node.timeout_clause) {
        if(node.label || node.sensitivity_clause || node.condition_clause) { os << "\n"; }
        (*this)(*node.timeout_clause);
    }
}


void printer::operator()(waveform const &node)
{
    static char const symbol[]{ "waveform" };
    symbol_scope<waveform> _(*this, symbol);

    util::visit_in_place(
        node,
        [this](ast::waveform_element_list const& list) {
            auto const N = list.size() - 1;
            unsigned i = 0;
            for(auto const& waveform_element : list) {
                (*this)(waveform_element);
                if(i++ != N) {
                    os << ",\n";
                }
            }
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        }
    );
}


void printer::operator()(waveform_element const &node)
{
    static char const symbol[]{ "waveform_element" };
    symbol_scope<waveform_element> _(*this, symbol);

    util::visit_in_place(
        node.form,
        [this](ast::expression const& expr) {
            (*this)(expr);
        },
        [this](ast::keyword_token token) {
            (*this)(token);
        }
    );

    if(node.time_expression) {
        os << "\n";
        (*this)(*node.time_expression);
    }
}


/*
 * Non AST members, used e.g. for unit tests (namely ast::integer)
 */
void printer::operator()(boost::iterator_range<parser::iterator_type> const &node)
{
    // even boost::iterator_range is used, the symbol is string_view
    static char const symbol[]{ "std::string_view" };
    symbol_scope<std::string> _(*this, symbol);

    os << node;
}


void printer::operator()(keyword_token token)
{
    static char const symbol[]{ "keyword" };
    symbol_scope<keyword_token> _(*this, symbol);

    os << token;
}


void printer::operator()(nullary const&)
{
    os << "\n*****************************";
    os << "\n*    SHALL NEVER BE HERE    *";
    os << "\n*****************************\n";
}





} } } // namespace eda.vhdl.ast


#include <eda/utils/compiler_pop.hpp>

