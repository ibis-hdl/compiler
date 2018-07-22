/*
 * tagged_stats.hpp
 *
 *  Created on: 21.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_TAGGED_STATS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_TAGGED_STATS_HPP_

#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <string>
#include <map>


namespace eda { namespace vhdl { namespace ast {


namespace detail {


struct stats_map
{

    void operator()(std::string const& node_name) {
        ++count_map[node_name];
    }

    typedef std::map<std::string, std::size_t>      map_type;
    typedef map_type::iterator                      iterator_type;

    map_type                                        count_map;
};


} // namespace detail


class tagged_stats : boost::static_visitor<void>
{
public:
    void operator()(ast::abstract_literal const& node) const;
    void operator()(ast::access_type_definition const& node) const;
    void operator()(ast::actual_designator const& node) const;
    void operator()(ast::actual_part const& node) const;
    void operator()(ast::aggregate const& node) const;
    void operator()(ast::alias_declaration const& node) const;
    void operator()(ast::alias_designator const& node) const;
    void operator()(ast::allocator const& node) const;
    void operator()(ast::architecture_body const& node) const;
    void operator()(ast::architecture_statement_part const& node) const;
    void operator()(ast::array_type_definition const& node) const;
    void operator()(ast::assertion const& node) const;
    void operator()(ast::assertion_statement const& node) const;
    void operator()(ast::association_element const& node) const;
    void operator()(ast::association_list const& node) const;
    void operator()(ast::attribute_declaration const& node) const;
    void operator()(ast::attribute_name const& node) const;
    void operator()(ast::attribute_specification const& node) const;
    void operator()(ast::based_literal const& node) const;
    void operator()(ast::binding_indication const& node) const;
    void operator()(ast::bit_string_literal const& node) const;
    void operator()(ast::block_configuration const& node) const;
    void operator()(ast::block_declarative_item const& node) const;
    void operator()(ast::block_declarative_part const& node) const;
    void operator()(ast::block_header const& node) const;
    void operator()(ast::block_specification const& node) const;
    void operator()(ast::block_statement const& node) const;
    void operator()(ast::block_statement_part const& node) const;
    void operator()(ast::case_statement const& node) const;
    void operator()(ast::case_statement_alternative const& node) const;
    void operator()(ast::character_literal const& node) const;
    void operator()(ast::choice const& node) const;
    void operator()(ast::choices const& node) const;
    void operator()(ast::component_configuration const& node) const;
    void operator()(ast::component_declaration const& node) const;
    void operator()(ast::component_instantiation_statement const& node) const;
    void operator()(ast::component_specification const& node) const;
    void operator()(ast::composite_type_definition const& node) const;
    void operator()(ast::concurrent_assertion_statement const& node) const;
    void operator()(ast::concurrent_procedure_call_statement const& node) const;
    void operator()(ast::concurrent_signal_assignment_statement const& node) const;
    void operator()(ast::concurrent_statement const& node) const;
    void operator()(ast::condition_clause const& node) const;
    void operator()(ast::conditional_signal_assignment const& node) const;
    void operator()(ast::conditional_waveforms const& node) const;
    void operator()(ast::configuration_declaration const& node) const;
    void operator()(ast::configuration_declarative_item const& node) const;
    void operator()(ast::configuration_declarative_part const& node) const;
    void operator()(ast::configuration_item const& node) const;
    void operator()(ast::configuration_specification const& node) const;
    void operator()(ast::constant_declaration const& node) const;
    void operator()(ast::constrained_array_definition const& node) const;
    void operator()(ast::constraint const& node) const;
    void operator()(ast::context_clause const& node) const;
    void operator()(ast::context_item const& node) const;
    void operator()(ast::decimal_literal const& node) const;
    void operator()(ast::delay_mechanism const& node) const;
    void operator()(ast::design_file const& node) const;
    void operator()(ast::design_unit const& node) const;
    void operator()(ast::designator const& node) const;
    void operator()(ast::disconnection_specification const& node) const;
    void operator()(ast::discrete_range const& node) const;
    void operator()(ast::element_association const& node) const;
    void operator()(ast::element_declaration const& node) const;
    void operator()(ast::entity_aspect const& node) const;
    void operator()(ast::entity_class_entry_list const& node) const;
    void operator()(ast::entity_declaration const& node) const;
    void operator()(ast::entity_declarative_item const& node) const;
    void operator()(ast::entity_declarative_part const& node) const;
    void operator()(ast::entity_designator const& node) const;
    void operator()(ast::entity_header const& node) const;
    void operator()(ast::entity_name_list const& node) const;
    void operator()(ast::entity_specification const& node) const;
    void operator()(ast::entity_statement const& node) const;
    void operator()(ast::entity_statement_part const& node) const;
    void operator()(ast::entity_tag const& node) const;
    void operator()(ast::enumeration_literal const& node) const;
    void operator()(ast::enumeration_type_definition const& node) const;
    void operator()(ast::exit_statement const& node) const;
    void operator()(ast::expression const& node) const;
    void operator()(ast::factor_binary_operation const& node) const;
    void operator()(ast::factor_unary_operation const& node) const;
    void operator()(ast::factor const& node) const;
    void operator()(ast::file_declaration const& node) const;
    void operator()(ast::file_open_information const& node) const;
    void operator()(ast::formal_part const& node) const;
    void operator()(ast::function_call const& node) const;
    void operator()(ast::generate_statement const& node) const;
    void operator()(ast::generation_scheme const& node) const;
    void operator()(ast::generic_clause const& node) const;
    void operator()(ast::generic_map_aspect const& node) const;
    void operator()(ast::group_constituent const& node) const;
    void operator()(ast::group_constituent_list const& node) const;
    void operator()(ast::group_declaration const& node) const;
    void operator()(ast::group_template_declaration const& node) const;
    void operator()(ast::guarded_signal_specification const& node) const;
    void operator()(ast::identifier const& node) const;
    void operator()(ast::identifier_list const& node) const;
    void operator()(ast::if_statement const& node) const;
    void operator()(ast::index_constraint const& node) const;
    void operator()(ast::index_specification const& node) const;
    void operator()(ast::index_subtype_definition const& node) const;
    void operator()(ast::indexed_name const& node) const;
    void operator()(ast::instantiated_unit const& node) const;
    void operator()(ast::instantiation_list const& node) const;
    void operator()(ast::interface_constant_declaration const& node) const;
    void operator()(ast::interface_declaration const& node) const;
    void operator()(ast::interface_file_declaration const& node) const;
    void operator()(ast::interface_list const& node) const;
    void operator()(ast::interface_signal_declaration const& node) const;
    void operator()(ast::interface_variable_declaration const& node) const;
    void operator()(ast::iteration_scheme const& node) const;
    void operator()(ast::library_clause const& node) const;
    void operator()(ast::library_unit const& node) const;
    void operator()(ast::literal const& node) const;
    void operator()(ast::loop_statement const& node) const;
    void operator()(ast::name const& node) const;
    void operator()(ast::next_statement const& node) const;
    void operator()(ast::null_statement const& node) const;
    void operator()(ast::numeric_literal const& node) const;
    void operator()(ast::options const& node) const;
    void operator()(ast::package_body const& node) const;
    void operator()(ast::package_body_declarative_item const& node) const;
    void operator()(ast::package_body_declarative_part const& node) const;
    void operator()(ast::package_declaration const& node) const;
    void operator()(ast::package_declarative_item const& node) const;
    void operator()(ast::package_declarative_part const& node) const;
    void operator()(ast::parameter_specification const& node) const;
    void operator()(ast::physical_literal const& node) const;
    void operator()(ast::physical_type_definition const& node) const;
    void operator()(ast::port_clause const& node) const;
    void operator()(ast::port_map_aspect const& node) const;
    void operator()(ast::prefix const& node) const;
    void operator()(ast::primary const& node) const;
    void operator()(ast::primary_unit const& node) const;
    void operator()(ast::procedure_call const& node) const;
    void operator()(ast::procedure_call_statement const& node) const;
    void operator()(ast::process_declarative_item const& node) const;
    void operator()(ast::process_declarative_part const& node) const;
    void operator()(ast::process_statement const& node) const;
    void operator()(ast::qualified_expression const& node) const;
    void operator()(ast::range const& node) const;
    void operator()(ast::record_type_definition const& node) const;
    void operator()(ast::relation const& node) const;
    void operator()(ast::report_statement const& node) const;
    void operator()(ast::return_statement const& node) const;
    void operator()(ast::scalar_type_definition const& node) const;
    void operator()(ast::secondary_unit const& node) const;
    void operator()(ast::secondary_unit_declaration const& node) const;
    void operator()(ast::selected_name const& node) const;
    void operator()(ast::selected_signal_assignment const& node) const;
    void operator()(ast::selected_waveforms const& node) const;
    void operator()(ast::sensitivity_clause const& node) const;
    void operator()(ast::sensitivity_list const& node) const;
    void operator()(ast::sequence_of_statements const& node) const;
    void operator()(ast::sequential_statement const& node) const;
    void operator()(ast::shift_expression const& node) const;
    void operator()(ast::signal_assignment_statement const& node) const;
    void operator()(ast::signal_declaration const& node) const;
    void operator()(ast::signal_list_list const& node) const; // signal_list helper (not in BNF)
    void operator()(ast::signal_list const& node) const;
    void operator()(ast::signature const& node) const;
    void operator()(ast::simple_expression const& node) const;
    void operator()(ast::slice_name const& node) const;
    void operator()(ast::string_literal const& node) const;
    void operator()(ast::subprogram_body const& node) const;
    void operator()(ast::subprogram_declarative_item const& node) const;
    void operator()(ast::subprogram_declarative_part const& node) const;
    void operator()(ast::subprogram_specification const& node) const;
    void operator()(ast::subtype_declaration const& node) const;
    void operator()(ast::subtype_indication const& node) const;
    void operator()(ast::suffix const& node) const;
    void operator()(ast::target const& node) const;
    void operator()(ast::term const& node) const;
    void operator()(ast::timeout_clause const& node) const;
    void operator()(ast::type_conversion const& node) const;
    void operator()(ast::type_declaration const& node) const;
    void operator()(ast::type_definition const& node) const;
    void operator()(ast::unconstrained_array_definition const& node) const;
    void operator()(ast::use_clause const& node) const;
    void operator()(ast::variable_assignment_statement const& node) const;
    void operator()(ast::variable_declaration const& node) const;
    void operator()(ast::wait_statement const& node) const;
    void operator()(ast::waveform const& node) const;
    void operator()(ast::waveform_element const& node) const;

    void operator()(ast::string_span const& node) const;

    void operator()(ast::keyword_token token) const;

    void operator()(ast::nullary const& node) const;

private:
    detail::stats_map                               stats_map;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_TAGGED_STATS_HPP_ */
