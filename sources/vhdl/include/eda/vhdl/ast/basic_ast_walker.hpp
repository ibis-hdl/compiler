/*
 * basic_ast_walker.hpp
 *
 *  Created on: 24.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_BASIC_AST_WALKER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_BASIC_AST_WALKER_HPP_

//#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast.hpp>

#include <eda/compiler/warnings_off.hpp>
#include <eda/support/boost/hana_overload.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <algorithm>

#include <boost/core/ignore_unused.hpp>

#include <eda/util/cxx_bug_fatal.hpp>


namespace eda { namespace vhdl { namespace ast {

/*
 * useful? https://stackoverflow.com/questions/26380420/boost-fusion-sequence-type-and-name-identification-for-structs-and-class
 */
template<typename WorkerT>
class basic_ast_walker : boost::static_visitor<void>
{
    WorkerT const                              		worker;

private:
    template<typename... Ts>
    void visit(variant<Ts ...> const& node) {
    	boost::apply_visitor(*this, node);
    }

    template<typename T>
    void visit(std::vector<T> const& vector) {
    	std::for_each(vector.begin(), vector.end(),
    			     [this](auto const& e) { (*this)(e); });
    }

public:
    template <typename... WorkerArgs>
    basic_ast_walker(WorkerArgs&&... args)
    : worker{ std::forward<WorkerArgs>(args)... }
    { }

    basic_ast_walker(basic_ast_walker const&) = delete;
    basic_ast_walker const& operator=(basic_ast_walker const&) = delete;

public:
    WorkerT const& get_worker() const { return worker; }

public:
    void operator()(ast::abstract_literal const &node)
    {
        static char const node_typename[]{ "abstract_literal" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::access_type_definition const &node)
    {
        static char const node_typename[]{ "access_type_definition" };
        worker(node, node_typename);

        (*this)(node.subtype_indication);
    }


    void operator()(ast::actual_designator const &node)
    {
        static char const node_typename[]{ "actual_designator" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::actual_part const &node)
    {
        static char const node_typename[]{ "actual_part" };
        worker(node, node_typename);

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


    void operator()(ast::aggregate const &node)
    {
        static char const node_typename[]{ "aggregate" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::alias_declaration const &node)
    {
        static char const node_typename[]{ "alias_declaration" };
        worker(node, node_typename);

        (*this)(node.alias_designator);

        if(node.subtype_indication) {
            (*this)(*node.subtype_indication);
        }

        (*this)(node.name);

        if(node.signature) {
            (*this)(*node.signature);
        }
    }


    void operator()(ast::alias_designator const &node)
    {
        static char const node_typename[]{ "alias_designator" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::allocator const &node)
    {
        static char const node_typename[]{ "allocator" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::architecture_body const &node)
    {
        static char const node_typename[]{ "architecture_body" };
        worker(node, node_typename);

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


    void operator()(ast::architecture_statement_part const &node)
    {
        static char const node_typename[]{ "architecture_statement_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::array_type_definition const &node)
    {
        static char const node_typename[]{ "array_type_definition" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::assertion const &node)
    {
        static char const node_typename[]{ "assertion" };
        worker(node, node_typename);

        (*this)(node.condition);

        if(node.report) {
            static char const node_typename[]{ "assertion.report" };
            worker(node.report, node_typename);
            // XXXX
            (*this)(*node.report);
        }

        if(node.severity) {
            static char const node_typename[]{ "assertion.severity" };
            worker(node.severity, node_typename);
            // XXX
            (*this)(*node.severity);
        }
    }


    void operator()(ast::assertion_statement const &node)
    {
        static char const node_typename[]{ "assertion_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.assertion);
    }


    void operator()(ast::association_element const &node)
    {
        static char const node_typename[]{ "association_element" };
        worker(node, node_typename);

        if(node.formal_part) {
            (*this)(*node.formal_part);

        }
        (*this)(node.actual_part);
    }


    void operator()(ast::association_list const &node)
    {
        static char const node_typename[]{ "association_list" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::attribute_declaration const &node)
    {
        static char const node_typename[]{ "attribute_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);
        (*this)(node.type_mark);
    }


    void operator()(ast::attribute_name const &node)
    {
        static char const node_typename[]{ "attribute_name" };
        worker(node, node_typename);

        (*this)(node.prefix);

        if(node.signature) {
            (*this)(*node.signature);
        }

        if(node.expression) {
            (*this)(*node.expression);
        }
    }


    void operator()(ast::attribute_specification const &node)
    {
        static char const node_typename[]{ "attribute_specification" };
        worker(node, node_typename);

        (*this)(node.entity_specification);
        (*this)(node.expression);
    }


    void operator()(ast::based_literal const &node)
    {
        static char const node_typename[]{ "based_literal" };
        worker(node, node_typename);
    }


    void operator()(ast::binding_indication const &node)
    {
        static char const node_typename[]{ "binding_indication" };
        worker(node, node_typename);

        if(node.entity_aspect) {
            (*this)(*node.entity_aspect);
        }

        (*this)(node.generic_map_aspect);
        (*this)(node.port_map_aspect);
    }


    void operator()(ast::bit_string_literal const &node)
    {
        static char const node_typename[]{ "bit_string_literal" };
        worker(node, node_typename);
    }


    void operator()(ast::block_configuration const &node)
    {
        static char const node_typename[]{ "block_configuration" };
        worker(node, node_typename);

        (*this)(node.block_specification);

        {
            static char const node_typename[]{ "use_clause*" };
            worker(node.use_clause_list, node_typename);
            // XXX
            visit(node.use_clause_list);
        }

        {
            static char const node_typename[]{ "configuration_item*" };
            worker(node.configuration_item_list, node_typename);
            // XXX
            visit(node.configuration_item_list);
        }
    }


    void operator()(ast::block_declarative_item const &node)
    {
        static char const node_typename[]{ "block_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::block_declarative_part const &node)
    {
        static char const node_typename[]{ "block_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::block_header const &node)
    {
        static char const node_typename[]{ "block_header" };
        worker(node, node_typename);

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


    void operator()(ast::block_specification const &node)
    {
        static char const node_typename[]{ "block_specification" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::name const& name) {
                (*this)(name);
            },
            [this](ast::block_specification_chunk const& chunk) {
                (*this)(chunk.label);
                if(chunk.index_specification) {
                    (*this)(*chunk.index_specification);
                }
            },
            [this](ast::nullary const& nullary) {
                (*this)(nullary);
            }
        );
    }


    void operator()(ast::block_statement const &node)
    {
        static char const node_typename[]{ "block_statement" };
        worker(node, node_typename);

        (*this)(node.label);

        if(node.guard_expression) {
            (*this)(*node.guard_expression);
        }

        if(node.header.generic_part || node.header.port_part) {
            (*this)(node.header);
        }

        if(!node.declarative_part.empty()) {
            (*this)(node.declarative_part);
        }

        if(!node.statement_part.empty()) {
            (*this)(node.statement_part);
        }

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }


    void operator()(ast::block_statement_part const &node)
    {
        static char const node_typename[]{ "block_statement_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::case_statement const &node)
    {
        static char const node_typename[]{ "case_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.expression);

        {
            static char const node_typename[]{ "case_statement_alternative*" };
            worker(node.alternatives, node_typename);
            // XXX
        	visit(node.alternatives);
        }

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }

    void operator()(ast::case_statement_alternative const &node)
    {
        static char const node_typename[]{ "case_statement_alternative" };
        worker(node, node_typename);

        (*this)(node.choices);
        (*this)(node.sequence_of_statements);
    }


    void operator()(ast::character_literal const &node)
    {
        static char const node_typename[]{ "character_literal" };
        worker(node, node_typename);
    }


    void operator()(ast::choice const &node)
    {
        static char const node_typename[]{ "choice" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::choices const &node)
    {
        static char const node_typename[]{ "choices" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::component_configuration const &node)
    {
        static char const node_typename[]{ "component_configuration" };
        worker(node, node_typename);

        (*this)(node.component_specification);

        if(node.binding_indication) {
            (*this)(*node.binding_indication);
        }

        if(node.block_configuration) {
            (*this)(*node.block_configuration);
        }
    }


    void operator()(ast::component_declaration const &node)
    {
        static char const node_typename[]{ "component_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);

        if(node.local_generic_clause) {
            (*this)(*node.local_generic_clause);
        }

        if(node.local_port_clause) {
            (*this)(*node.local_port_clause);
        }

        if(node.name) {
            (*this)(*node.name);
        }
    }


    void operator()(ast::component_instantiation_statement const &node)
    {
        static char const node_typename[]{ "component_instantiation_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.instantiated_unit);

        if(node.generic_map_aspect) {
            (*this)(*node.generic_map_aspect);
        }

        if(node.port_map_aspect) {
            (*this)(*node.port_map_aspect);
        }
    }


    void operator()(ast::component_specification const &node)
    {
        static char const node_typename[]{ "component_specification" };
        worker(node, node_typename);

        (*this)(node.instantiation_list);
        (*this)(node.component_name);
    }


    void operator()(ast::composite_type_definition const &node)
    {
        static char const node_typename[]{ "composite_type_definition" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::concurrent_assertion_statement const &node)
    {
        static char const node_typename[]{ "concurrent_assertion_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.assertion);
    }


    void operator()(ast::concurrent_procedure_call_statement const &node)
    {
        static char const node_typename[]{ "concurrent_procedure_call_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.procedure_call);
    }


    void operator()(ast::concurrent_signal_assignment_statement const &node)
    {
        static char const node_typename[]{ "concurrent_signal_assignment_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

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


    void operator()(ast::concurrent_statement const &node)
    {
        static char const node_typename[]{ "concurrent_statement" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::condition_clause const &node)
    {
        static char const node_typename[]{ "condition_clause" };
        worker(node, node_typename);

        (*this)(node.condition);
    }


    void operator()(ast::conditional_signal_assignment const &node)
    {
        static char const node_typename[]{ "conditional_signal_assignment" };
        worker(node, node_typename);

        (*this)(node.target);

        if(node.options.delay_mechanism || node.options.guarded) {
            (*this)(node.options);
        }

        (*this)(node.conditional_waveforms);
    }


    void operator()(ast::conditional_waveforms const &node)
    {
        static char const node_typename[]{ "conditional_waveforms" };
        worker(node, node_typename);

        if(!node.chunks.empty()) {
    		for(auto const& chunk : node.chunks) {
    			(*this)(chunk.waveform);
    			(*this)(chunk.condition);
    		}
        }

        (*this)(node.waveform);

        if(node.condition) {
            (*this)(*node.condition);
        }
    }


    void operator()(ast::configuration_declaration const &node)
    {
        static char const node_typename[]{ "configuration_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);	// XXX HAS LABEL PAIR !!!
        (*this)(node.entity_name);

        if(!node.declarative_part.empty()) {
            (*this)(node.declarative_part);
        }

        (*this)(node.block_configuration);

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }


    void operator()(ast::configuration_declarative_item const &node)
    {
        static char const node_typename[]{ "configuration_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::configuration_declarative_part const &node)
    {
        static char const node_typename[]{ "configuration_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::configuration_item const &node)
    {
        static char const node_typename[]{ "configuration_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::configuration_specification const &node)
    {
        static char const node_typename[]{ "configuration_specification" };
        worker(node, node_typename);

        (*this)(node.component_specification);
        (*this)(node.binding_indication);
    }


    void operator()(ast::constant_declaration const &node)
    {
        static char const node_typename[]{ "constant_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);
        (*this)(node.subtype_indication);

        if(node.expression) {
            (*this)(*node.expression);
        }
    }


    void operator()(ast::constrained_array_definition const &node)
    {
        static char const node_typename[]{ "constrained_array_definition" };
        worker(node, node_typename);

        (*this)(node.index_constraint);
        (*this)(node.element_subtype_indication);
    }


    void operator()(ast::constraint const &node)
    {
        static char const node_typename[]{ "constraint" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::context_clause const &node)
    {
        static char const node_typename[]{ "context_clause" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::context_item const &node)
    {
        static char const node_typename[]{ "context_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::decimal_literal const &node)
    {
        static char const node_typename[]{ "decimal_literal" };
        worker(node, node_typename);
    }


    void operator()(ast::delay_mechanism const &node)
    {
        static char const node_typename[]{ "delay_mechanism" };
        worker(node, node_typename);

        if(node.time_expression) {
            (*this)(*node.time_expression);
        }
    }


    void operator()(ast::design_file const &node)
    {
        static char const node_typename[]{ "design_file" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::design_unit const &node)
    {
        static char const node_typename[]{ "design_unit" };
        worker(node, node_typename);

        (*this)(node.context_clause);
        (*this)(node.library_unit);
    }


    void operator()(ast::designator const &node)
    {
        static char const node_typename[]{ "designator" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::disconnection_specification const &node)
    {
        static char const node_typename[]{ "disconnection_specification" };
        worker(node, node_typename);

        (*this)(node.guarded_signal_specification);
        (*this)(node.time_expression);
    }


    void operator()(ast::discrete_range const &node)
    {
        static char const node_typename[]{ "discrete_range" };
        worker(node, node_typename);

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


    void operator()(ast::element_association const &node)
    {
        static char const node_typename[]{ "element_association" };
        worker(node, node_typename);

        if(!node.choices.empty()) {
            (*this)(node.choices);
        }

        (*this)(node.expression);
    }


    void operator()(ast::element_declaration const &node)
    {
        static char const node_typename[]{ "element_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);
        (*this)(node.element_subtype_definition);
    }


    void operator()(ast::entity_aspect const &node)
    {
        static char const node_typename[]{ "entity_aspect" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::entity_aspect_entity const& entity) {
                (*this)(entity.name);
                if(entity.architecture_identifier) {
                    (*this)(*entity.architecture_identifier);
                }
            },
            [this](ast::entity_aspect_configuration const& configuration) {
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


    void operator()(ast::entity_class_entry_list const &node)
    {
        static char const node_typename[]{ "entity_class_entry_list" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::entity_declaration const &node)
    {
        static char const node_typename[]{ "entity_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier); // XXX LABEL PAIR

        if(node.header.formal_generic_clause || node.header.formal_port_clause) {
            (*this)(node.header);
        }

        if(!node.declarative_part.empty()) {
            (*this)(node.declarative_part);
        }

        if(node.statement_part) {
            (*this)(*node.statement_part);
        }

        if(node.name) {
            (*this)(*node.name);
        }
    }


    void operator()(ast::entity_declarative_item const &node)
    {
        static char const node_typename[]{ "entity_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::entity_declarative_part const &node)
    {
        static char const node_typename[]{ "entity_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::entity_designator const &node)
    {
        static char const node_typename[]{ "entity_designator" };
        worker(node, node_typename);

        (*this)(node.entity_tag);
        if(node.signature) {
            (*this)(*node.signature);
        }
    }


    void operator()(ast::entity_header const &node)
    {
        static char const node_typename[]{ "entity_header" };
        worker(node, node_typename);

        if(node.formal_generic_clause) {
            (*this)(*node.formal_generic_clause);
        }

        if(node.formal_port_clause) {
            (*this)(*node.formal_port_clause);
        }
    }


    void operator()(ast::entity_name_list const &node)
    {
        static char const node_typename[]{ "entity_name_list" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::entity_designator_list const& entity_designator_list) {
            	visit(entity_designator_list);
            },
            [this](ast::keyword_token token) {
                (*this)(token); // OTHERS | ALL
            },
            [this](ast::nullary const& nullary) {
                (*this)(nullary);
            }
        );
    }


    void operator()(ast::entity_specification const &node)
    {
        static char const node_typename[]{ "entity_specification" };
        worker(node, node_typename);

        (*this)(node.entity_name_list);
        (*this)(node.entity_class);
    }


    void operator()(ast::entity_statement const &node)
    {
        static char const node_typename[]{ "entity_statement" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::entity_statement_part const &node)
    {
        static char const node_typename[]{ "entity_statement_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::entity_tag const &node)
    {
        static char const node_typename[]{ "entity_tag" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::enumeration_literal const &node)
    {
        static char const node_typename[]{ "enumeration_literal" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::enumeration_type_definition const &node)
    {
        static char const node_typename[]{ "enumeration_type_definition" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::exit_statement const &node)
    {
        static char const node_typename[]{ "exit_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        if(node.loop_label) {
            (*this)(*node.loop_label);
        }

        if(node.condition) {
            (*this)(*node.condition);
        }
    }


    void operator()(ast::expression const &node)
    {
        static char const node_typename[]{ "expression" };
        worker(node, node_typename);

        (*this)(node.relation);

        if(node.rest_list.empty()) {
            return;
        }

        for(auto const& chunk : node.rest_list) {
            (*this)(chunk.relation);
        }
    }


    void operator()(ast::factor_binary_operation const& node)
    {
        static char const node_typename[]{ "factor_binary_operation" };
        worker(node, node_typename);

        visit(node.primary_lhs);
        visit(node.primary_rhs);
    }


    void operator()(ast::factor_unary_operation const& node)
    {
        static char const node_typename[]{ "factor_unary_operation" };
        worker(node, node_typename);

        visit(node.primary);
    }

    void operator()(ast::factor const &node)
    {
        static char const node_typename[]{ "factor" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::file_declaration const &node)
    {
        static char const node_typename[]{ "file_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);
        (*this)(node.subtype_indication);

        if(node.file_open_information) {
            (*this)(*node.file_open_information);
        }
    }


    void operator()(ast::file_open_information const &node)
    {
        static char const node_typename[]{ "file_open_information" };
        worker(node, node_typename);

        if(node.file_open_kind_expression) {
            (*this)(*node.file_open_kind_expression);
        }
        (*this)(node.file_logical_name);
    }


    void operator()(ast::formal_part const &node)
    {
        static char const node_typename[]{ "formal_part" };
        worker(node, node_typename);

        auto const visit_name = [this](auto const& ctx_name) {
            (*this)(ctx_name);
        };

        auto const visit_formal_designator = [this](auto const& ctx_name) {
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
                visit_formal_designator(node.context_tied_names[1]);
                break;
            }

            default: {
                cxx_bug_fatal("VHDL BNF rules violation, parser rule failed!");
            }
        }
    }


    void operator()(ast::function_call const &node)
    {
        static char const node_typename[]{ "function_call" };
        worker(node, node_typename);

        (*this)(node.function_name);

        if(node.actual_parameter_part) {
            {
                static char const node_typename[]{ "actual_parameter_part" };
                worker(node, node_typename);

                (*this)(*node.actual_parameter_part);
            }
        }
    }


    void operator()(ast::generate_statement const &node)
    {
        static char const node_typename[]{ "generate_statement" };
        worker(node, node_typename);

        (*this)(node.label);
        (*this)(node.generation_scheme);

        if(!node.block_declarative_parts.empty()) {
            (*this)(node.block_declarative_parts);
        }

        if(!node.concurrent_statements.empty()) {
            static char const node_typename[]{ "concurrent_statement*" };
            worker(node, node_typename);
            visit(node.concurrent_statements);
        }

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }


    void operator()(ast::generation_scheme const &node)
    {
        static char const node_typename[]{ "generation_scheme" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::generic_clause const &node)
    {
        static char const node_typename[]{ "generic_clause" };
        worker(node, node_typename);

        (*this)(node.generic_list);
    }


    void operator()(ast::generic_map_aspect const &node)
    {
        static char const node_typename[]{ "generic_map_aspect" };
        worker(node, node_typename);

        (*this)(node.association_list);
    }


    void operator()(ast::group_constituent const &node)
    {
        static char const node_typename[]{ "group_constituent" };
        worker(node, node_typename);
        visit(node);
    }


    void operator()(ast::group_constituent_list const &node)
    {
        static char const node_typename[]{ "group_constituent_list" };
        worker(node, node_typename);

        visit(node);
    }

    void operator()(ast::group_declaration const &node)
    {
        static char const node_typename[]{ "group_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);
        (*this)(node.group_template_name);
        (*this)(node.group_constituent_list);
    }


    void operator()(ast::group_template_declaration const &node)
    {
        static char const node_typename[]{ "group_template_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);
        (*this)(node.entity_class_entry_list);
    }


    void operator()(ast::guarded_signal_specification const &node)
    {
        static char const node_typename[]{ "guarded_signal_specification" };
        worker(node, node_typename);

        (*this)(node.guarded_signal_list);
        (*this)(node.type_mark);
    }


    void operator()(ast::identifier const &node)
    {
        static char const node_typename[]{ "identifier" };
        worker(node, node_typename);
    }


    void operator()(ast::identifier_list const &node)
    {
        static char const node_typename[]{ "identifier_list" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::if_statement const &node)
    {
        static char const node_typename[]{ "if_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.if_condition);

        (*this)(node.then_sequence_of_statements);

        if(!node.elseif_chunks.empty()) {
            for(auto const& elsif_chunk : node.elseif_chunks) {
                (*this)(elsif_chunk.condition);
                (*this)(elsif_chunk.sequence_of_statements);
            }
        }

        if(!node.else_sequence_of_statements.empty()) {
            (*this)(node.else_sequence_of_statements);
        }

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }


    void operator()(ast::index_constraint const &node)
    {
        static char const node_typename[]{ "index_constraint" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::index_specification const &node)
    {
        static char const node_typename[]{ "index_specification" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::index_subtype_definition const &node)
    {
        static char const node_typename[]{ "index_subtype_definition" };
        worker(node, node_typename);

        (*this)(node.type_mark);
    }


    void operator()(ast::indexed_name const &node)
    {
        static char const node_typename[]{ "indexed_name" };
        worker(node, node_typename);

        (*this)(node.prefix);

        {
            static char const node_typename[]{ "expression*" };
            worker(node, node_typename);
            visit(node.expression_list);
        }
    }


    void operator()(ast::instantiated_unit const &node)
    {
        static char const node_typename[]{ "instantiated_unit" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::instantiated_unit_component const& component) {
                (*this)(component.name);
            },
            [this](ast::instantiated_unit_entity const& entity) {
                (*this)(entity.name);
                if(entity.architecture_identifier) {
                    (*this)(*entity.architecture_identifier);
                }
            },
            [this](ast::instantiated_unit_configuration const& configuration) {
                (*this)(configuration.name);
            },
            [this](ast::nullary const& nullary) {
                (*this)(nullary);
            }
        );
    }


    void operator()(ast::instantiation_list const &node)
    {
        static char const node_typename[]{ "instantiation_list" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::instantiation_label_list const& instantiation_label_list) {
                visit(instantiation_label_list);
            },
            [this](ast::keyword_token token) {
                (*this)(token);
            },
            [this](ast::nullary const& nullary) {
                (*this)(nullary);
            }

        );
    }


    void operator()(ast::interface_constant_declaration const &node)
    {
        static char const node_typename[]{ "interface_constant_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);

        (*this)(node.subtype_indication);

        if(node.static_expression) {
            (*this)(*node.static_expression);
        }
    }


    void operator()(ast::interface_declaration const &node)
    {
        static char const node_typename[]{ "interface_declaration" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::interface_file_declaration const &node)
    {
        static char const node_typename[]{ "interface_file_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);
        (*this)(node.subtype_indication);
    }


    void operator()(ast::interface_list const &node)
    {
        static char const node_typename[]{ "interface_list" };
        worker(node, node_typename);
        visit(node);
    }


    void operator()(ast::interface_signal_declaration const &node)
    {
        static char const node_typename[]{ "interface_signal_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);

        if(node.mode) {
            (*this)(*node.mode);
        }

        (*this)(node.subtype_indication);

        if(node.static_expression) {
            (*this)(*node.static_expression);
        }
    }


    void operator()(ast::interface_variable_declaration const &node)
    {
        static char const node_typename[]{ "interface_variable_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);

        if(node.mode) {
            (*this)(*node.mode);
        }

        (*this)(node.subtype_indication);

        if(node.static_expression) {
            (*this)(*node.static_expression);
        }
    }


    void operator()(ast::iteration_scheme const &node)
    {
        static char const node_typename[]{ "iteration_scheme" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::library_clause const &node)
    {
        static char const node_typename[]{ "library_clause" };
        worker(node, node_typename);

        visit(node.logical_name_list);
    }


    void operator()(ast::library_unit const &node)
    {
        static char const node_typename[]{ "library_unit" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::literal const &node)
    {
        static char const node_typename[]{ "literal" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::loop_statement const &node)
    {
        static char const node_typename[]{ "loop_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        if(node.iteration_scheme) {
            (*this)(*node.iteration_scheme);
        }

        (*this)(node.sequence_of_statements);

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }


    void operator()(ast::name const &node)
    {
        static char const node_typename[]{ "name" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::next_statement const &node)
    {
        static char const node_typename[]{ "next_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        if(node.loop_label) {
            (*this)(*node.loop_label);
        }

        if(node.condition) {
            (*this)(*node.condition);
        }
    }


    void operator()(ast::null_statement const &node)
    {
        static char const node_typename[]{ "null_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }
    }


    void operator()(ast::numeric_literal const &node)
    {
        static char const node_typename[]{ "numeric_literal" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::options const &node)
    {
        static char const node_typename[]{ "options" };
        worker(node, node_typename);

        if(node.delay_mechanism) {
            (*this)(*node.delay_mechanism);
        }
    }


    void operator()(ast::package_body const &node)
    {
        static char const node_typename[]{ "package_body" };
        worker(node, node_typename);

        (*this)(node.name);
        (*this)(node.declarative_part);

        if(node.end_name) {
            (*this)(*node.end_name);
        }
    }


    void operator()(ast::package_body_declarative_item const &node)
    {
        static char const node_typename[]{ "package_body_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::package_body_declarative_part const &node)
    {
        static char const node_typename[]{ "package_body_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::package_declaration const &node)
    {
        static char const node_typename[]{ "package_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);

        (*this)(node.declarative_part);

        if(node.end_label) {
            (*this)(*node.end_label);
        }
    }


    void operator()(ast::package_declarative_item const &node)
    {
        static char const node_typename[]{ "package_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::package_declarative_part const &node)
    {
        static char const node_typename[]{ "package_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::parameter_specification const &node)
    {
        static char const node_typename[]{ "parameter_specification" };
        worker(node, node_typename);

        (*this)(node.identifier);
        (*this)(node.discrete_range);
    }


    void operator()(ast::physical_literal const &node)
    {
        static char const node_typename[]{ "physical_literal" };
        worker(node, node_typename);

        (*this)(node.literal);
    }


    void operator()(ast::physical_type_definition const &node)
    {
        static char const node_typename[]{ "physical_type_definition" };
        worker(node, node_typename);

        (*this)(node.range_constraint);
        (*this)(node.primary_unit_declaration);

        if (!node.secondary_unit_declarations.empty()) {
        }

        visit(node.secondary_unit_declarations);

        if(node.physical_type_simple_name) {
            (*this)(*node.physical_type_simple_name);
        }
    }


    void operator()(ast::port_clause const &node)
    {
        static char const node_typename[]{ "port_clause" };
        worker(node, node_typename);

        (*this)(node.port_list);
    }


    void operator()(ast::port_map_aspect const &node)
    {
        static char const node_typename[]{ "port_map_aspect" };
        worker(node, node_typename);

        (*this)(node.association_list);
    }


    void operator()(ast::prefix const &node)
    {
        static char const node_typename[]{ "prefix" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::primary const &node)
    {
        static char const node_typename[]{ "primary" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::primary_unit const &node)
    {
        static char const node_typename[]{ "primary_unit" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::procedure_call const &node)
    {
        static char const node_typename[]{ "procedure_call" };
        worker(node, node_typename);

        (*this)(node.procedure_name);

        if(node.actual_parameter_part) {
            (*this)(*node.actual_parameter_part);
        }
    }


    void operator()(ast::procedure_call_statement const &node)
    {
        static char const node_typename[]{ "procedure_call_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.procedure_call);
    }


    void operator()(ast::process_declarative_item const &node)
    {
        static char const node_typename[]{ "process_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::process_declarative_part const &node)
    {
        static char const node_typename[]{ "process_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::process_statement const &node)
    {
        static char const node_typename[]{ "process_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        if(!node.sensitivity_list.empty()) {
            (*this)(node.sensitivity_list);
        }

        if(!node.declarative_part.empty()) {
            (*this)(node.declarative_part);
        }

        if(!node.statement_part.empty()) {
            (*this)(node.statement_part);
        }

        if(node.label) {
            (*this)(*node.label);
        }
    }


    void operator()(ast::qualified_expression const &node)
    {
        static char const node_typename[]{ "qualified_expression" };
        worker(node, node_typename);

        (*this)(node.type_mark);

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


    void operator()(ast::range const &node) // aka range_constraint
    {
        static char const node_typename[]{ "range" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](range_attribute_name const &name) {
                (*this)(name);
            },
            [this](range_expression const &expr) {
                (*this)(expr.lhs);
                (*this)(expr.direction);
                (*this)(expr.rhs);
            }
        );
    }


    void operator()(ast::record_type_definition const &node)
    {
        static char const node_typename[]{ "record_type_definition" };
        worker(node, node_typename);

        {
            static char const node_typename[]{ "element_declaration*" };
            worker(node, node_typename);
            visit(node.element_declarations);
        }
    }


    void operator()(ast::relation const &node)
    {
        static char const node_typename[]{ "relation" };
        worker(node, node_typename);

        (*this)(node.shift_expression);

        if(!node.rest) {
            return;
        }

        auto const& chunk = *node.rest;
        (*this)(chunk.shift_expression);
    }


    void operator()(ast::report_statement const &node)
    {
        static char const node_typename[]{ "report_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.report);

        if(node.severity) {
            (*this)(*node.severity);
        }
    }


    void operator()(ast::return_statement const &node)
    {
        static char const node_typename[]{ "return_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        if(node.expression) {
            (*this)(*node.expression);
        }
    }


    void operator()(ast::scalar_type_definition const &node)
    {
        static char const node_typename[]{ "scalar_type_definition" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::secondary_unit const &node)
    {
        static char const node_typename[]{ "secondary_unit" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::secondary_unit_declaration const &node)
    {
        static char const node_typename[]{ "secondary_unit_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);
        (*this)(node.physical_literal);
    }


    void operator()(ast::selected_name const &node)
    {
        static char const node_typename[]{ "selected_name" };
        worker(node, node_typename);

        (*this)(node.prefix);
        (*this)(node.suffix);
    }


    void operator()(ast::selected_signal_assignment const &node)
    {
        static char const node_typename[]{ "selected_signal_assignment" };
        worker(node, node_typename);

        (*this)(node.expression);
        (*this)(node.target);
        (*this)(node.options);
        (*this)(node.selected_waveforms);
    }


    void operator()(ast::selected_waveforms const &node)
    {
        static char const node_typename[]{ "selected_waveforms" };
        worker(node, node_typename);

        for(auto const& selected_waveform : node) {
            (*this)(selected_waveform.waveform);
            (*this)(selected_waveform.choices);
        }
    }


    void operator()(ast::sensitivity_clause const &node)
    {
        static char const node_typename[]{ "sensitivity_clause" };
        worker(node, node_typename);

        (*this)(node.sensitivity_list);
    }


    void operator()(ast::sensitivity_list const& node)
    {
        static char const node_typename[]{ "sensitivity_list" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::sequence_of_statements const &node)
    {
        static char const node_typename[]{ "sequence_of_statements" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::sequential_statement const &node)
    {
        static char const node_typename[]{ "sequential_statement" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::shift_expression const &node)
    {
        static char const node_typename[]{ "shift_expression" };
        worker(node, node_typename);

        (*this)(node.simple_expression);

        if(!node.rest) {
            return;
        }

        auto const& chunk = *node.rest;
        (*this)(chunk.simple_expression);
    }


    void operator()(ast::signal_assignment_statement const &node)
    {
        static char const node_typename[]{ "signal_assignment_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.target);

        if(node.delay_mechanism) {
            (*this)(*node.delay_mechanism);
        }

        (*this)(node.waveform);
    }


    void operator()(ast::signal_declaration const &node)
    {
        static char const node_typename[]{ "signal_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);
        (*this)(node.subtype_indication);

        if(node.signal_kind) {
            (*this)(*node.signal_kind);
        }

        if(node.expression) {
            (*this)(*node.expression);
        }
    }


    void operator()(ast::signal_list_list const& node)
    {
        static char const node_typename[]{ "signal_list.names" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::signal_list const &node)
    {
        static char const node_typename[]{ "signal_list" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::signature const &node)
    {
        static char const node_typename[]{ "signature" };
        worker(node, node_typename);

        {
            static char const node_typename[]{ "parameter_type_list" };
            worker(node, node_typename);
            visit(node.parameter_type_list);
        }

        if(node.return_type) {
            static char const node_typename[]{ "return_type" };
            worker(node, node_typename);
            (*this)(*node.return_type);
        }
    }

    void operator()(ast::simple_expression const &node)
    {
        static char const node_typename[]{ "simple_expression" };
        worker(node, node_typename);

        (*this)(node.term);

        if(node.rest_list.empty()) {
            return;
        }

        for(auto const& chunk : node.rest_list) {
            (*this)(chunk.term);
        }
    }


    void operator()(ast::slice_name const &node)
    {
        static char const node_typename[]{ "slice_name" };
        worker(node, node_typename);

        (*this)(node.prefix);
        (*this)(node.discrete_range);
    }


    void operator()(ast::string_literal const &node)
    {
        static char const node_typename[]{ "string_literal" };
        worker(node, node_typename);
    }


    void operator()(ast::subprogram_body const &node)
    {
        static char const node_typename[]{ "subprogram_body" };
        worker(node, node_typename);

        (*this)(node.specification);
        (*this)(node.declarative_part);
        (*this)(node.statement_part);

        if(node.kind) {
            (*this)(*node.kind);
        }

        if(node.designator) {
            (*this)(*node.designator);
        }
    }


    void operator()(ast::subprogram_declarative_item const &node)
    {
        static char const node_typename[]{ "subprogram_declarative_item" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::subprogram_declarative_part const &node)
    {
        static char const node_typename[]{ "subprogram_declarative_part" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::subprogram_specification const &node)
    {
        static char const node_typename[]{ "subprogram_specification" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::subprogram_specification_procedure const& procedure) {
                (*this)(procedure.designator);
                if(procedure.formal_parameter_list) {
                    (*this)(*procedure.formal_parameter_list);
                }
            },
            [this](ast::subprogram_specification_function const& function) {
                (*this)(function.designator);
                if(function.formal_parameter_list) {
                    (*this)(*function.formal_parameter_list);
                }
                (*this)(function.return_type_mark);
            }
        );
    }


    void operator()(ast::subtype_declaration const &node)
    {
        static char const node_typename[]{ "subtype_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);
        (*this)(node.subtype_indication);
    }


    void operator()(ast::subtype_indication const &node)
    {
        static char const node_typename[]{ "subtype_indication" };
        worker(node, node_typename);

        auto const visit_type_mark = [this](auto const& type_mark) {
            (*this)(type_mark);
        };

        auto const visit_resolution_function_name = [this](auto const& resolution_function_name) {
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
                visit_type_mark(node.unspecified_name_list[1]);
                break;
            }

            default:
                cxx_bug_fatal("VHDL BNF rules violation, parser rule failed!");
        }

        if(node.constraint) {
            (*this)(*node.constraint);
        }
    }


    void operator()(ast::suffix const &node)
    {
        static char const node_typename[]{ "suffix" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::target const &node)
    {
        static char const node_typename[]{ "target" };
        worker(node, node_typename);

        boost::apply_visitor(*this, node);
    }


    void operator()(ast::term const &node)
    {
        static char const node_typename[]{ "term" };
        worker(node, node_typename);

        visit(node.factor);

        if(node.rest_list.empty()) {
            return;
        }

        for(auto const& term_chunk: node.rest_list) {
            visit(term_chunk.factor);
        }
    }


    void operator()(ast::timeout_clause const &node)
    {
        static char const node_typename[]{ "timeout_clause" };
        worker(node, node_typename);

        (*this)(node.time_expression);
    }


    void operator()(ast::type_conversion const &node)
    {
        static char const node_typename[]{ "type_conversion" };
        worker(node, node_typename);

        (*this)(node.type_mark);
        (*this)(node.expression);
    }


    void operator()(ast::type_declaration const &node)
    {
        // {full, incomplete}_type_declaration
        static char const node_typename[]{ "type_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier);

        if(node.type_definition) {
            (*this)(*node.type_definition);
        }
    }


    void operator()(ast::type_definition const &node)
    {
        static char const node_typename[]{ "type_definition" };
        worker(node, node_typename);

        visit(node);
    }


    void operator()(ast::unconstrained_array_definition const &node)
    {
        static char const node_typename[]{ "unconstrained_array_definition" };
        worker(node, node_typename);

        for(auto const& index_subtype_definition : node.index_subtype_definitions) {
            (*this)(index_subtype_definition);
        }

        (*this)(node.element_subtype_indication);
    }


    void operator()(ast::use_clause const &node)
    {
        static char const node_typename[]{ "use_clause" };
        worker(node, node_typename);

        for(auto const& selected_name : node.list) {
            for(auto const& name : selected_name.prefix_list) {
                (*this)(name);
            }
            (*this)(selected_name.suffix);
        }
    }


    void operator()(ast::variable_assignment_statement const &node)
    {
        static char const node_typename[]{ "variable_assignment_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }

        (*this)(node.target);

        (*this)(node.expression);
    }


    void operator()(ast::variable_declaration const &node)
    {
        static char const node_typename[]{ "variable_declaration" };
        worker(node, node_typename);

        (*this)(node.identifier_list);
        (*this)(node.subtype_indication);

        if(node.expression) {
            (*this)(*node.expression);
        }
    }


    void operator()(ast::wait_statement const &node)
    {
        static char const node_typename[]{ "wait_statement" };
        worker(node, node_typename);

        if(node.label) {
            (*this)(*node.label);
        }
        if(node.sensitivity_clause) {
            (*this)(*node.sensitivity_clause);
        }
        if(node.condition_clause) {
            (*this)(*node.condition_clause);
        }
        if(node.timeout_clause) {
            (*this)(*node.timeout_clause);
        }
    }


    void operator()(ast::waveform const &node)
    {
        static char const node_typename[]{ "waveform" };
        worker(node, node_typename);

        util::visit_in_place(
            node,
            [this](ast::waveform_element_list const& list) {
        		visit(list);
            },
            [this](ast::keyword_token token) {
                (*this)(token);
            }
        );
    }


    void operator()(ast::waveform_element const &node)
    {
        static char const node_typename[]{ "waveform_element" };
        worker(node, node_typename);

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
            (*this)(*node.time_expression);
        }
    }


    /*
     * Non AST members, used e.g. for unit tests (namely ast::integer)
     */
    void operator()(ast::string_span const &node)
    {
        // even boost::iterator_range is used, the symbol is string_view
        static char const node_typename[]{ "std::string_view" };
        worker(node, node_typename);
    }


    void operator()(ast::keyword_token token)
    {
    	boost::ignore_unused(token);
#if 0
        static char const node_typename[]{ "keyword" };
        //XXX worker(node, node_typename);
#endif
    }


    void operator()(ast::nullary const& node)
    {
    	boost::ignore_unused(node);
#if 0
        /******************************/
        /*    SHALL NEVER BE HERE     */
        /******************************/
        static char const node_typename[]{ "*** nullary ***" };
        // XXX call worker::fatal_failure() ????
        worker(node, node_typename);
#endif
    }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_BASIC_AST_WALKER_HPP_ */
