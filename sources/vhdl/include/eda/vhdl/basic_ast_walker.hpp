/*
 * basic_ast_walker.hpp
 *
 *  Created on: 24.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_BASIC_AST_WALKER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_BASIC_AST_WALKER_HPP_

#include <eda/vhdl/ast_fwd.hpp>

#include <eda/compiler/warnings_off.hpp>
#include <eda/support/boost/hana_overload.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <boost/variant/apply_visitor.hpp>


namespace eda { namespace vhdl { namespace ast {

/*
 * useful? https://stackoverflow.com/questions/26380420/boost-fusion-sequence-type-and-name-identification-for-structs-and-class
 */
template<typename WorkerT>
class basic_ast_walker
{
    WorkerT const                              worker;

private:
    template<typename NodeT>
    void visit(NodeT const& node) const {
        boost::apply_visitor(*this, node);
    }

public:
    template <typename... WorkerArgs>
    basic_ast_walker(WorkerArgs&&... args)
    : worker{ std::forward<WorkerArgs>(args)... }
    { }

    basic_ast_walker(basic_ast_walker const&) = delete;
    basic_ast_walker const& operator=(basic_ast_walker const&) = delete;

public:
    void operator()(ast::abstract_literal const& node) const {
        static char const symbol[]{ "abstract_literal" };
        worker(node, symbol);

        visit(node);
    }

    void operator()(ast::access_type_definition const& node) const {
        static char const symbol[]{ "access_type_definition" };
        worker(node, symbol);

        (*this)(node.subtype_indication);
    }

    void operator()(ast::actual_designator const& node) const {
        static char const symbol[]{ "actual_designator" };
        worker(node, symbol);

        visit(node);
    }

    void operator()(ast::actual_part const &node) const {
        static char const symbol[]{ "actual_part" };
        worker(node, symbol);

        util::visit_in_place(
            node,
            [this](ast::actual_part_chunk const& chunk) {
                (*this)(chunk.context_tied_name);
                (*this)(chunk.actual_designator);
            },
            [this](ast::actual_designator node_) {
                (*this)(node_);
            }
        );
    }

    void operator()(ast::aggregate const& node) const {
        static char const symbol[]{ "aggregate" };
        worker(node, symbol);

        for(auto const& element_association : node) {
            (*this)(element_association);
        }
    }

    void operator()(ast::alias_declaration const& node) const {
        static char const symbol[]{ "alias_declaration" };
        worker(node, symbol);

        (*this)(node.alias_designator);

        if(node.subtype_indication) {
            (*this)(*node.subtype_indication);
        }

        (*this)(node.name);

        if(node.signature) {
            (*this)(*node.signature);
        }
    }

    void operator()(ast::alias_designator const& node) const {
        static char const symbol[]{ "alias_designator" };
        worker(node, symbol);

        visit(node);
    }

    void operator()(ast::allocator const& node) const {
        static char const symbol[]{ "allocator" };
        worker(node, symbol);

        visit(node);
    }

    void operator()(ast::architecture_body const& node) const {
        static char const symbol[]{ "architecture_body" };
        worker(node, symbol);

        (*this)(node.identifier);
        (*this)(node.entity_name);

        if(!node.declarative_part.empty()) {
            (*this)(node.declarative_part);
        }

        if(!node.statement_part.empty()) {
            (*this)(node.statement_part);
        }

        if(node.end_name) {
            (*this)(*node.end_name);
        }
    }

    void operator()(ast::architecture_statement_part const& node) const {
        static char const symbol[]{ "architecture_statement_part" };
        worker(node, symbol);

        for(auto const& concurrent_statement : node) {
            (*this)(concurrent_statement);
        }
    }

    void operator()(ast::array_type_definition const& node) const {
        static char const symbol[]{ "array_type_definition" };
        worker(node, symbol);

        visit(node);
    }

    void operator()(ast::assertion const& node) const {
        static char const symbol[]{ "assertion" };
        worker(node, symbol);

        (*this)(node.condition);

        if(node.report) {
            (*this)(*node.report);
        }

        if(node.severity) {
            (*this)(*node.severity);
        }
    }

    void operator()(ast::assertion_statement const& node) const {
        static char const symbol[]{ "assertion_statement" };
        worker(node, symbol);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.assertion);
    }

    void operator()(ast::association_element const& node) const {
        static char const symbol[]{ "association_element" };
        worker(node, symbol);

        if(node.formal_part) {
            (*this)(*node.formal_part);
        }

        (*this)(node.actual_part);
    }

    void operator()(ast::association_list const& node) const {
        static char const symbol[]{ "association_list" };
        worker(node, symbol);

        for(auto const& association_element : node) {
            (*this)(association_element);
        }
    }

    void operator()(ast::attribute_declaration const& node) const {
        static char const symbol[]{ "attribute_declaration" };
        worker(node, symbol);

        (*this)(node.identifier);
        (*this)(node.type_mark);
    }

    void operator()(ast::attribute_name const& node) const {
        static char const symbol[]{ "attribute_name" };
        worker(node, symbol);

        (*this)(node.prefix);

        if(node.signature) {
            (*this)(*node.signature);
        }

        (*this)(node.attribute_designator);

        if(node.expression) {
            (*this)(*node.expression);
        }
    }

    void operator()(ast::attribute_specification const& node) const {
        static char const symbol[]{ "attribute_specification" };
        worker(node, symbol);

        (*this)(node.attribute_designator);
        (*this)(node.entity_specification);
        (*this)(node.expression);
    }

    void operator()(ast::based_literal const& node) const {
        static char const symbol[]{ "based_literal" };
        worker(node, symbol);
    }

    void operator()(ast::binding_indication const& node) const {
        static char const symbol[]{ "binding_indication" };
        worker(node, symbol);

        if(node.entity_aspect) {
            (*this)(*node.entity_aspect);
        }

        (*this)(node.generic_map_aspect);
        (*this)(node.port_map_aspect);
    }

    void operator()(ast::bit_string_literal const& node) const {
        static char const symbol[]{ "bit_string_literal" };
        worker(node, symbol);
    }

    void operator()(ast::block_configuration const& node) const {
        static char const symbol[]{ "block_configuration" };
        worker(node, symbol);

        (*this)(node.block_specification);

        for(auto const& use_clause : node.use_clause_list) {
            (*this)(use_clause);
        }

        for(auto const& configuration_item : node.configuration_item_list) {
            (*this)(configuration_item);
        }
    }

    void operator()(ast::block_declarative_part const& node) const {
        static char const symbol[]{ "block_declarative_part" };
        worker(node, symbol);
    }

    void operator()(ast::block_header const& node) const {
        static char const symbol[]{ "block_header" };
        worker(node, symbol);

        if(node.generic_part) {
            auto const& generic_part = *node.generic_part;
            (*this)(generic_part.generic_clause);

            if(generic_part.generic_map_aspect) {
            	(*this)(*generic_part.generic_map_aspect);
            }
        }

        if(node.port_part) {
            auto const& port_part = *node.port_part;
            (*this)(port_part.port_clause);

            if(port_part.port_map_aspect) {
            	(*this)(*port_part.port_map_aspect);
            }
        }
    }
////////////////////////////////////////////////////////////////////////////////
    void operator()(ast::block_specification const& node) const {
        static char const symbol[]{ "block_specification" };
        worker(node, symbol);
    }
    void operator()(ast::block_statement const& node) const {
        static char const symbol[]{ "block_statement" };
        worker(node, symbol);
    }
    void operator()(ast::concurrent_statement const& node) const {
        static char const symbol[]{ "concurrent_statement" };
        worker(node, symbol);
    }
    void operator()(ast::block_statement_part const& node) const {
        static char const symbol[]{ "block_statement_part" };
        worker(node, symbol);
    }
    void operator()(ast::case_statement_alternative const& node) const {
        static char const symbol[]{ "case_statement_alternative" };
        worker(node, symbol);
    }
    void operator()(ast::case_statement const& node) const {
        static char const symbol[]{ "case_statement" };
        worker(node, symbol);
    }
    void operator()(ast::character_literal const& node) const {
        static char const symbol[]{ "character_literal" };
        worker(node, symbol);
    }
    void operator()(ast::component_configuration const& node) const {
        static char const symbol[]{ "component_configuration" };
        worker(node, symbol);
    }
    void operator()(ast::component_declaration const& node) const {
        static char const symbol[]{ "component_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::component_instantiation_statement const& node) const {
        static char const symbol[]{ "component_instantiation_statement" };
        worker(node, symbol);
    }
    void operator()(ast::component_specification const& node) const {
        static char const symbol[]{ "component_specification" };
        worker(node, symbol);
    }
    void operator()(ast::composite_type_definition const& node) const {
        static char const symbol[]{ "composite_type_definition" };
        worker(node, symbol);
    }
    void operator()(ast::concurrent_assertion_statement const& node) const {
        static char const symbol[]{ "concurrent_assertion_statement" };
        worker(node, symbol);
    }
    void operator()(ast::concurrent_procedure_call_statement const& node) const {
        static char const symbol[]{ "concurrent_procedure_call_statement" };
        worker(node, symbol);
    }
    void operator()(ast::concurrent_signal_assignment_statement const& node) const {
        static char const symbol[]{ "concurrent_signal_assignment_statement" };
        worker(node, symbol);
    }
    void operator()(ast::concurrent_statement const& node) const {
        static char const symbol[]{ "concurrent_statement" };
        worker(node, symbol);
    }
    void operator()(ast::conditional_signal_assignment const& node) const {
        static char const symbol[]{ "conditional_signal_assignment" };
        worker(node, symbol);
    }
    void operator()(ast::conditional_waveforms const& node) const {
        static char const symbol[]{ "conditional_waveforms" };
        worker(node, symbol);
    }
    void operator()(ast::condition_clause const& node) const {
        static char const symbol[]{ "condition_clause" };
        worker(node, symbol);
    }
    void operator()(ast::configuration_declaration const& node) const {
        static char const symbol[]{ "configuration_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::configuration_declarative_part const& node) const {
        static char const symbol[]{ "configuration_declarative_part" };
        worker(node, symbol);
    }
    void operator()(ast::block_configuration const& node) const {
        static char const symbol[]{ "block_configuration" };
        worker(node, symbol);
    }
    void operator()(ast::component_configuration const& node) const {
        static char const symbol[]{ "component_configuration" };
        worker(node, symbol);
    }
    void operator()(ast::configuration_specification const& node) const {
        static char const symbol[]{ "configuration_specification" };
        worker(node, symbol);
    }
    void operator()(ast::constant_declaration const& node) const {
        static char const symbol[]{ "constant_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::constrained_array_definition const& node) const {
        static char const symbol[]{ "constrained_array_definition" };
        worker(node, symbol);
    }
    void operator()(ast::constraint const& node) const {
        static char const symbol[]{ "constraint" };
        worker(node, symbol);
    }
    void operator()(ast::node const& node) const {
            static char const symbol[]{ "node" };
            worker(node, symbol);
    }
    void operator()(ast::decimal_literal const& node) const {
        static char const symbol[]{ "decimal_literal" };
        worker(node, symbol);
    }
    void operator()(ast::delay_mechanism const& node) const {
        static char const symbol[]{ "delay_mechanism" };
        worker(node, symbol);
    }
    void operator()(ast::designator const& node) const {
        static char const symbol[]{ "designator" };
        worker(node, symbol);
    }
    void operator()(ast::design_file const& node) const {
        static char const symbol[]{ "design_file" };
        worker(node, symbol);
    }
    void operator()(ast::design_unit const& node) const {
        static char const symbol[]{ "design_unit" };
        worker(node, symbol);
    }
    void operator()(ast::disconnection_specification const& node) const {
        static char const symbol[]{ "disconnection_specification" };
        worker(node, symbol);
    }
    void operator()(ast::subtype_indication const& node) const {
        static char const symbol[]{ "subtype_indication" };
        worker(node, symbol);
    }
    void operator()(ast::discrete_range const& node) const {
        static char const symbol[]{ "discrete_range" };
        worker(node, symbol);
    }
    void operator()(ast::element_association const& node) const {
        static char const symbol[]{ "element_association" };
        worker(node, symbol);
    }
    void operator()(ast::element_declaration const& node) const {
        static char const symbol[]{ "element_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::entity_aspect_entity const& node) const {
        static char const symbol[]{ "entity_aspect_entity" };
        worker(node, symbol);
    }
    void operator()(ast::entity_aspect_configuration const& node) const {
        static char const symbol[]{ "entity_aspect_configuration" };
        worker(node, symbol);
    }
    void operator()(ast::entity_aspect const& node) const {
        static char const symbol[]{ "entity_aspect" };
        worker(node, symbol);
    }
    void operator()(ast::entity_class_entry_list const& node) const {
        static char const symbol[]{ "entity_class_entry_list" };
        worker(node, symbol);
    }
    void operator()(ast::entity_declaration const& node) const {
        static char const symbol[]{ "entity_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::entity_declarative_part const& node) const {
        static char const symbol[]{ "entity_declarative_part" };
        worker(node, symbol);
    }
    void operator()(ast::entity_designator const& node) const {
        static char const symbol[]{ "entity_designator" };
        worker(node, symbol);
    }
    void operator()(ast::entity_header const& node) const {
        static char const symbol[]{ "entity_header" };
        worker(node, symbol);
    }
    void operator()(ast::entity_designator_list const& node) const {
        static char const symbol[]{ "entity_designator_list" };
        worker(node, symbol);
    }
    void operator()(ast::entity_name_list const& node) const {
        static char const symbol[]{ "entity_name_list" };
        worker(node, symbol);
    }
    void operator()(ast::entity_specification const& node) const {
        static char const symbol[]{ "entity_specification" };
        worker(node, symbol);
    }
    void operator()(ast::entity_statement_part const& node) const {
        static char const symbol[]{ "entity_statement_part" };
        worker(node, symbol);
    }
    void operator()(ast::enumeration_literal const& node) const {
        static char const symbol[]{ "enumeration_literal" };
        worker(node, symbol);
    }
    void operator()(ast::enumeration_type_definition const& node) const {
        static char const symbol[]{ "enumeration_type_definition" };
        worker(node, symbol);
    }
    void operator()(ast::exit_statement const& node) const {
        static char const symbol[]{ "exit_statement" };
        worker(node, symbol);
    }
    void operator()(ast::expression const& node) const {
        static char const symbol[]{ "expression" };
        worker(node, symbol);
    }
    void operator()(ast::factor_binary_operation const& node) const {
        static char const symbol[]{ "factor_binary_operation" };
        worker(node, symbol);
    }
    void operator()(ast::factor_unary_operation const& node) const {
        static char const symbol[]{ "factor_unary_operation" };
        worker(node, symbol);
    }
    void operator()(ast::factor const& node) const {
        static char const symbol[]{ "factor" };
        worker(node, symbol);
    }
    void operator()(ast::file_declaration const& node) const {
        static char const symbol[]{ "file_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::file_open_information const& node) const {
        static char const symbol[]{ "file_open_information" };
        worker(node, symbol);
    }
    void operator()(ast::name const& node) const {
        static char const symbol[]{ "name" };
        worker(node, symbol);
    }
    void operator()(ast::formal_part const& node) const {
        static char const symbol[]{ "formal_part" };
        worker(node, symbol);
    }
    void operator()(ast::name const& node) const {
        static char const symbol[]{ "name" };
        worker(node, symbol);
    }
    void operator()(ast::function_call const& node) const {
        static char const symbol[]{ "function_call" };
        worker(node, symbol);
    }
    void operator()(ast::concurrent_statement const& node) const {
        static char const symbol[]{ "concurrent_statement" };
        worker(node, symbol);
    }
    void operator()(ast::generate_statement const& node) const {
        static char const symbol[]{ "generate_statement" };
        worker(node, symbol);
    }
    void operator()(ast::generation_scheme const& node) const {
        static char const symbol[]{ "generation_scheme" };
        worker(node, symbol);
    }
    void operator()(ast::generic_clause const& node) const {
        static char const symbol[]{ "generic_clause" };
        worker(node, symbol);
    }
    void operator()(ast::generic_map_aspect const& node) const {
        static char const symbol[]{ "generic_map_aspect" };
        worker(node, symbol);
    }
    void operator()(ast::group_declaration const& node) const {
        static char const symbol[]{ "group_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::group_template_declaration const& node) const {
        static char const symbol[]{ "group_template_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::guarded_signal_specification const& node) const {
        static char const symbol[]{ "guarded_signal_specification" };
        worker(node, symbol);
    }
    void operator()(ast::identifier const& node) const {
        static char const symbol[]{ "identifier" };
        worker(node, symbol);
    }
    void operator()(ast::identifier_list const& node) const {
        static char const symbol[]{ "identifier_list" };
        worker(node, symbol);
    }
    void operator()(ast::if_statement const& node) const {
        static char const symbol[]{ "if_statement" };
        worker(node, symbol);
    }
    void operator()(ast::index_constraint const& node) const {
        static char const symbol[]{ "index_constraint" };
        worker(node, symbol);
    }
    void operator()(ast::expression const& node) const {
        static char const symbol[]{ "expression" };
        worker(node, symbol);
    }
    void operator()(ast::indexed_name const& node) const {
        static char const symbol[]{ "indexed_name" };
        worker(node, symbol);
    }
    void operator()(ast::index_specification const& node) const {
        static char const symbol[]{ "index_specification" };
        worker(node, symbol);
    }
    void operator()(ast::index_subtype_definition const& node) const {
        static char const symbol[]{ "index_subtype_definition" };
        worker(node, symbol);
    }
    void operator()(ast::instantiated_unit_component const& node) const {
        static char const symbol[]{ "instantiated_unit_component" };
        worker(node, symbol);
    }
    void operator()(ast::instantiated_unit_entity const& node) const {
        static char const symbol[]{ "instantiated_unit_entity" };
        worker(node, symbol);
    }
    void operator()(ast::instantiated_unit_configuration const& node) const {
        static char const symbol[]{ "instantiated_unit_configuration" };
        worker(node, symbol);
    }
    void operator()(ast::instantiated_unit const& node) const {
        static char const symbol[]{ "instantiated_unit" };
        worker(node, symbol);
    }
    void operator()(ast::instantiation_list const& node) const {
        static char const symbol[]{ "instantiation_list" };
        worker(node, symbol);
    }
    void operator()(ast::interface_constant_declaration const& node) const {
        static char const symbol[]{ "interface_constant_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::interface_file_declaration const& node) const {
        static char const symbol[]{ "interface_file_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::interface_list const& node) const {
        static char const symbol[]{ "interface_list" };
        worker(node, symbol);
    }
    void operator()(ast::interface_signal_declaration const& node) const {
        static char const symbol[]{ "interface_signal_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::interface_variable_declaration const& node) const {
        static char const symbol[]{ "interface_variable_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::iteration_scheme const& node) const {
        static char const symbol[]{ "iteration_scheme" };
        worker(node, symbol);
    }
    void operator()(ast::library_clause const& node) const {
        static char const symbol[]{ "library_clause" };
        worker(node, symbol);
    }
    void operator()(ast::literal const& node) const {
        static char const symbol[]{ "literal" };
        worker(node, symbol);
    }
    void operator()(ast::loop_statement const& node) const {
        static char const symbol[]{ "loop_statement" };
        worker(node, symbol);
    }
    void operator()(ast::name const& node) const {
        static char const symbol[]{ "name" };
        worker(node, symbol);
    }
    void operator()(ast::next_statement const& node) const {
        static char const symbol[]{ "next_statement" };
        worker(node, symbol);
    }
    void operator()(ast::null_statement const& node) const {
        static char const symbol[]{ "null_statement" };
        worker(node, symbol);
    }
    void operator()(ast::numeric_literal const& node) const {
        static char const symbol[]{ "numeric_literal" };
        worker(node, symbol);
    }
    void operator()(ast::options const& node) const {
        static char const symbol[]{ "options" };
        worker(node, symbol);
    }
    void operator()(ast::package_body const& node) const {
        static char const symbol[]{ "package_body" };
        worker(node, symbol);
    }
    void operator()(ast::package_declaration const& node) const {
        static char const symbol[]{ "package_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::parameter_specification const& node) const {
        static char const symbol[]{ "parameter_specification" };
        worker(node, symbol);
    }
    void operator()(ast::physical_literal const& node) const {
        static char const symbol[]{ "physical_literal" };
        worker(node, symbol);
    }
    void operator()(ast::physical_type_definition const& node) const {
        static char const symbol[]{ "physical_type_definition" };
        worker(node, symbol);
    }
    void operator()(ast::port_clause const& node) const {
        static char const symbol[]{ "port_clause" };
        worker(node, symbol);
    }
    void operator()(ast::port_map_aspect const& node) const {
        static char const symbol[]{ "port_map_aspect" };
        worker(node, symbol);
    }
    void operator()(ast::name const& node) const {
        static char const symbol[]{ "name" };
        worker(node, symbol);
    }
    void operator()(ast::prefix const& node) const {
        static char const symbol[]{ "prefix" };
        worker(node, symbol);
    }
    void operator()(ast::name const& node) const {
        static char const symbol[]{ "name" };
        worker(node, symbol);
    }
    void operator()(ast::aggregate const& node) const {
        static char const symbol[]{ "aggregate" };
        worker(node, symbol);
    }
    void operator()(ast::expression const& node) const {
        static char const symbol[]{ "expression" };
        worker(node, symbol);
    }
    void operator()(ast::function_call const& node) const {
        static char const symbol[]{ "function_call" };
        worker(node, symbol);
    }
    void operator()(ast::qualified_expression const& node) const {
        static char const symbol[]{ "qualified_expression" };
        worker(node, symbol);
    }
    void operator()(ast::allocator const& node) const {
        static char const symbol[]{ "allocator" };
        worker(node, symbol);
    }
    void operator()(ast::primary const& node) const {
        static char const symbol[]{ "primary" };
        worker(node, symbol);
    }
    void operator()(ast::primary_unit const& node) const {
        static char const symbol[]{ "primary_unit" };
        worker(node, symbol);
    }
    void operator()(ast::name const& node) const {
        static char const symbol[]{ "name" };
        worker(node, symbol);
    }
    void operator()(ast::procedure_call const& node) const {
        static char const symbol[]{ "procedure_call" };
        worker(node, symbol);
    }
    void operator()(ast::procedure_call_statement const& node) const {
        static char const symbol[]{ "procedure_call_statement" };
        worker(node, symbol);
    }
    void operator()(ast::process_declarative_part const& node) const {
        static char const symbol[]{ "process_declarative_part" };
        worker(node, symbol);
    }
    void operator()(ast::process_statement const& node) const {
        static char const symbol[]{ "process_statement" };
        worker(node, symbol);
    }
    void operator()(ast::qualified_expression const& node) const {
        static char const symbol[]{ "qualified_expression" };
        worker(node, symbol);
    }
    void operator()(ast::range_expression const& node) const {
        static char const symbol[]{ "range_expression" };
        worker(node, symbol);
    }
    void operator()(ast::range const& node) const {
        static char const symbol[]{ "range" };
        worker(node, symbol);
    }
    void operator()(ast::record_type_definition const& node) const {
        static char const symbol[]{ "record_type_definition" };
        worker(node, symbol);
    }
    void operator()(ast::relation const& node) const {
        static char const symbol[]{ "relation" };
        worker(node, symbol);
    }
    void operator()(ast::report_statement const& node) const {
        static char const symbol[]{ "report_statement" };
        worker(node, symbol);
    }
    void operator()(ast::return_statement const& node) const {
        static char const symbol[]{ "return_statement" };
        worker(node, symbol);
    }
    void operator()(ast::scalar_type_definition const& node) const {
        static char const symbol[]{ "scalar_type_definition" };
        worker(node, symbol);
    }
    void operator()(ast::secondary_unit_declaration const& node) const {
        static char const symbol[]{ "secondary_unit_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::secondary_unit const& node) const {
        static char const symbol[]{ "secondary_unit" };
        worker(node, symbol);
    }
    void operator()(ast::selected_name const& node) const {
        static char const symbol[]{ "selected_name" };
        worker(node, symbol);
    }
    void operator()(ast::selected_signal_assignment const& node) const {
        static char const symbol[]{ "selected_signal_assignment" };
        worker(node, symbol);
    }
    void operator()(ast::selected_waveform const& node) const {
        static char const symbol[]{ "selected_waveform" };
        worker(node, symbol);
    }
    void operator()(ast::selected_waveforms const& node) const {
        static char const symbol[]{ "selected_waveforms" };
        worker(node, symbol);
    }
    void operator()(ast::sensitivity_clause const& node) const {
        static char const symbol[]{ "sensitivity_clause" };
        worker(node, symbol);
    }
    void operator()(ast::sensitivity_list const& node) const {
        static char const symbol[]{ "sensitivity_list" };
        worker(node, symbol);
    }
    void operator()(ast::sequence_of_statements const& node) const {
        static char const symbol[]{ "sequence_of_statements" };
        worker(node, symbol);
    }
    void operator()(ast::if_statement const& node) const {
        static char const symbol[]{ "if_statement" };
        worker(node, symbol);
    }
    void operator()(ast::case_statement const& node) const {
        static char const symbol[]{ "case_statement" };
        worker(node, symbol);
    }
    void operator()(ast::loop_statement const& node) const {
        static char const symbol[]{ "loop_statement" };
        worker(node, symbol);
    }
    void operator()(ast::shift_expression const& node) const {
        static char const symbol[]{ "shift_expression" };
        worker(node, symbol);
    }
    void operator()(ast::signal_assignment_statement const& node) const {
        static char const symbol[]{ "signal_assignment_statement" };
        worker(node, symbol);
    }
    void operator()(ast::signal_declaration const& node) const {
        static char const symbol[]{ "signal_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::signal_list_list const& node) const {
        static char const symbol[]{ "signal_list_list" };
        worker(node, symbol);
    }
    void operator()(ast::signal_list const& node) const {
        static char const symbol[]{ "signal_list" };
        worker(node, symbol);
    }
    void operator()(ast::signature const& node) const {
        static char const symbol[]{ "signature" };
        worker(node, symbol);
    }
    void operator()(ast::simple_expression const& node) const {
        static char const symbol[]{ "simple_expression" };
        worker(node, symbol);
    }
    void operator()(ast::slice_name const& node) const {
        static char const symbol[]{ "slice_name" };
        worker(node, symbol);
    }
    void operator()(ast::string_literal const& node) const {
        static char const symbol[]{ "string_literal" };
        worker(node, symbol);
    }
    void operator()(ast::subprogram_body const& node) const {
        static char const symbol[]{ "subprogram_body" };
        worker(node, symbol);
    }
    void operator()(ast::subprogram_body const& node) const {
        static char const symbol[]{ "subprogram_body" };
        worker(node, symbol);
    }
    void operator()(ast::subprogram_specification_procedure const& node) const {
        static char const symbol[]{ "subprogram_specification_procedure" };
        worker(node, symbol);
    }
    void operator()(ast::subprogram_specification_function const& node) const {
        static char const symbol[]{ "subprogram_specification_function" };
        worker(node, symbol);
    }
    void operator()(ast::subprogram_specification const& node) const {
        static char const symbol[]{ "subprogram_specification" };
        worker(node, symbol);
    }
    void operator()(ast::subtype_declaration const& node) const {
        static char const symbol[]{ "subtype_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::subtype_indication const& node) const {
        static char const symbol[]{ "subtype_indication" };
        worker(node, symbol);
    }
    void operator()(ast::suffix const& node) const {
        static char const symbol[]{ "suffix" };
        worker(node, symbol);
    }
    void operator()(ast::target const& node) const {
        static char const symbol[]{ "target" };
        worker(node, symbol);
    }
    void operator()(ast::term const& node) const {
        static char const symbol[]{ "term" };
        worker(node, symbol);
    }
    void operator()(ast::timeout_clause const& node) const {
        static char const symbol[]{ "timeout_clause" };
        worker(node, symbol);
    }
    void operator()(ast::type_conversion const& node) const {
        static char const symbol[]{ "type_conversion" };
        worker(node, symbol);
    }
    void operator()(ast::type_declaration const& node) const {
        static char const symbol[]{ "type_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::type_definition const& node) const {
        static char const symbol[]{ "type_definition" };
        worker(node, symbol);
    }
    void operator()(ast::unconstrained_array_definition const& node) const {
        static char const symbol[]{ "unconstrained_array_definition" };
        worker(node, symbol);
    }
    void operator()(ast::use_clause const& node) const {
        static char const symbol[]{ "use_clause" };
        worker(node, symbol);
    }
    void operator()(ast::variable_assignment_statement const& node) const {
        static char const symbol[]{ "variable_assignment_statement" };
        worker(node, symbol);
    }
    void operator()(ast::variable_declaration const& node) const {
        static char const symbol[]{ "variable_declaration" };
        worker(node, symbol);
    }
    void operator()(ast::wait_statement const& node) const {
        static char const symbol[]{ "wait_statement" };
        worker(node, symbol);
    }
    void operator()(ast::waveform_element const& node) const {
        static char const symbol[]{ "waveform_element" };
        worker(node, symbol);
    }
    void operator()(ast::waveform_element_list const& node) const {
        static char const symbol[]{ "waveform_element_list" };
        worker(node, symbol);
    }
    void operator()(ast::waveform const& node) const {
        static char const symbol[]{ "waveform" };
        worker(node, symbol);
    }

    void operator()(ast::nullary const& node) const {
        static char const symbol[]{ "nullary" };
        worker(node, symbol);
    }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_BASIC_AST_WALKER_HPP_ */
