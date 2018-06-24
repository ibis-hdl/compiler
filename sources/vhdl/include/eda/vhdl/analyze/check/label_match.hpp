/*
 * check_label_match.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_


#include <eda/vhdl/ast.hpp>

#include <iosfwd>


namespace eda { namespace vhdl { namespace analyze {


class check_label_match : public boost::static_visitor<bool>
{
    std::ostream&                                   os;

public:
    // check for label pairs
    check_label_match(std::ostream& os_);

    bool operator()(ast::block_statement const& node);
//    bool operator()(ast::block_statement_part const& node);
//    bool operator()(ast::case_statement const& node);
//    bool operator()(ast::case_statement_alternative const& node);
//    bool operator()(ast::character_literal const& node);
//    bool operator()(ast::choice const& node);
//    bool operator()(ast::choices const& node);
//    bool operator()(ast::component_configuration const& node);
//    bool operator()(ast::component_declaration const& node);
//    bool operator()(ast::component_instantiation_statement const& node);
//    bool operator()(ast::component_specification const& node);
//    bool operator()(ast::composite_type_definition const& node);
//    bool operator()(ast::concurrent_assertion_statement const& node);
//    bool operator()(ast::concurrent_procedure_call_statement const& node);
//    bool operator()(ast::concurrent_signal_assignment_statement const& node);
//    bool operator()(ast::concurrent_statement const& node);
//    bool operator()(ast::condition_clause const& node);
//    bool operator()(ast::conditional_signal_assignment const& node);
//    bool operator()(ast::conditional_waveforms const& node);
//    bool operator()(ast::configuration_declaration const& node);
//    bool operator()(ast::configuration_declarative_item const& node);
//    bool operator()(ast::configuration_declarative_part const& node);
//    bool operator()(ast::configuration_item const& node);
//    bool operator()(ast::configuration_specification const& node);
//    bool operator()(ast::constant_declaration const& node);
//    bool operator()(ast::constrained_array_definition const& node);
//    bool operator()(ast::constraint const& node);
//    bool operator()(ast::context_clause const& node);
//    bool operator()(ast::context_item const& node);
//    bool operator()(ast::decimal_literal const& node);
//    bool operator()(ast::delay_mechanism const& node);
    bool operator()(ast::design_file const& node);
//    bool operator()(ast::design_unit const& node);
//    bool operator()(ast::designator const& node);
//    bool operator()(ast::disconnection_specification const& node);
//    bool operator()(ast::discrete_range const& node);
//    bool operator()(ast::element_association const& node);
//    bool operator()(ast::element_declaration const& node);
//    bool operator()(ast::entity_aspect const& node);
//    bool operator()(ast::entity_class_entry_list const& node);
//    bool operator()(ast::entity_declaration const& node);
//    bool operator()(ast::entity_declarative_item const& node);
//    bool operator()(ast::entity_declarative_part const& node);
//    bool operator()(ast::entity_designator const& node);
//    bool operator()(ast::entity_header const& node);
//    bool operator()(ast::entity_name_list const& node);
//    bool operator()(ast::entity_specification const& node);
//    bool operator()(ast::entity_statement const& node);
//    bool operator()(ast::entity_statement_part const& node);
//    bool operator()(ast::entity_tag const& node);
//    bool operator()(ast::enumeration_literal const& node);
//    bool operator()(ast::enumeration_type_definition const& node);
//    bool operator()(ast::exit_statement const& node);
//    bool operator()(ast::expression const& node);
//    bool operator()(ast::factor_binary_operation const& node);
//    bool operator()(ast::factor_unary_operation const& node);
//    bool operator()(ast::factor const& node);
//    bool operator()(ast::file_declaration const& node);
//    bool operator()(ast::file_open_information const& node);
//    bool operator()(ast::formal_part const& node);
//    bool operator()(ast::function_call const& node);
//    bool operator()(ast::generate_statement const& node);
//    bool operator()(ast::generation_scheme const& node);
//    bool operator()(ast::generic_clause const& node);
//    bool operator()(ast::generic_map_aspect const& node);
//    bool operator()(ast::group_constituent const& node);
//    bool operator()(ast::group_constituent_list const& node);
//    bool operator()(ast::group_declaration const& node);
//    bool operator()(ast::group_template_declaration const& node);
//    bool operator()(ast::guarded_signal_specification const& node);
//    bool operator()(ast::identifier const& node);
//    bool operator()(ast::identifier_list const& node);
//    bool operator()(ast::if_statement const& node);
//    bool operator()(ast::index_constraint const& node);
//    bool operator()(ast::index_specification const& node);
//    bool operator()(ast::index_subtype_definition const& node);
//    bool operator()(ast::indexed_name const& node);
//    bool operator()(ast::instantiated_unit const& node);
//    bool operator()(ast::instantiation_list const& node);
//    bool operator()(ast::interface_constant_declaration const& node);
//    bool operator()(ast::interface_declaration const& node);
//    bool operator()(ast::interface_file_declaration const& node);
//    bool operator()(ast::interface_list const& node);
//    bool operator()(ast::interface_signal_declaration const& node);
//    bool operator()(ast::interface_variable_declaration const& node);
//    bool operator()(ast::iteration_scheme const& node);
//    bool operator()(ast::library_clause const& node);
//    bool operator()(ast::library_unit const& node);
//    bool operator()(ast::literal const& node);
//    bool operator()(ast::loop_statement const& node);
//    bool operator()(ast::name const& node);
//    bool operator()(ast::next_statement const& node);
//    bool operator()(ast::null_statement const& node);
//    bool operator()(ast::numeric_literal const& node);
//    bool operator()(ast::options const& node);
//    bool operator()(ast::package_body const& node);
//    bool operator()(ast::package_body_declarative_item const& node);
//    bool operator()(ast::package_body_declarative_part const& node);
//    bool operator()(ast::package_declaration const& node);
//    bool operator()(ast::package_declarative_item const& node);
//    bool operator()(ast::package_declarative_part const& node);
//    bool operator()(ast::parameter_specification const& node);
//    bool operator()(ast::physical_literal const& node);
//    bool operator()(ast::physical_type_definition const& node);
//    bool operator()(ast::port_clause const& node);
//    bool operator()(ast::port_map_aspect const& node);
//    bool operator()(ast::prefix const& node);
//    bool operator()(ast::primary const& node);
//    bool operator()(ast::primary_unit const& node);
//    bool operator()(ast::procedure_call const& node);
//    bool operator()(ast::procedure_call_statement const& node);
//    bool operator()(ast::process_declarative_item const& node);
//    bool operator()(ast::process_declarative_part const& node);
//    bool operator()(ast::process_statement const& node);
//    bool operator()(ast::qualified_expression const& node);
//    bool operator()(ast::range const& node);
//    bool operator()(ast::record_type_definition const& node);
//    bool operator()(ast::relation const& node);
//    bool operator()(ast::report_statement const& node);
//    bool operator()(ast::return_statement const& node);
//    bool operator()(ast::scalar_type_definition const& node);
//    bool operator()(ast::secondary_unit const& node);
//    bool operator()(ast::secondary_unit_declaration const& node);
//    bool operator()(ast::selected_name const& node);
//    bool operator()(ast::selected_signal_assignment const& node);
//    bool operator()(ast::selected_waveforms const& node);
//    bool operator()(ast::sensitivity_clause const& node);
//    bool operator()(ast::sensitivity_list const& node);
//    bool operator()(ast::sequence_of_statements const& node);
//    bool operator()(ast::sequential_statement const& node);
//    bool operator()(ast::shift_expression const& node);
//    bool operator()(ast::signal_assignment_statement const& node);
//    bool operator()(ast::signal_declaration const& node);
//    bool operator()(ast::signal_list_list const& node); // signal_list helper (not in BNF)
//    bool operator()(ast::signal_list const& node);
//    bool operator()(ast::signature const& node);
//    bool operator()(ast::simple_expression const& node);
//    bool operator()(ast::slice_name const& node);
//    bool operator()(ast::string_literal const& node);
//    bool operator()(ast::subprogram_body const& node);
//    bool operator()(ast::subprogram_declarative_item const& node);
//    bool operator()(ast::subprogram_declarative_part const& node);
//    bool operator()(ast::subprogram_specification const& node);
//    bool operator()(ast::subtype_declaration const& node);
//    bool operator()(ast::subtype_indication const& node);
//    bool operator()(ast::suffix const& node);
//    bool operator()(ast::target const& node);
//    bool operator()(ast::term const& node);
//    bool operator()(ast::timeout_clause const& node);
//    bool operator()(ast::type_conversion const& node);
//    bool operator()(ast::type_declaration const& node);
//    bool operator()(ast::type_definition const& node);
//    bool operator()(ast::unconstrained_array_definition const& node);
//    bool operator()(ast::use_clause const& node);
//    bool operator()(ast::variable_assignment_statement const& node);
//    bool operator()(ast::variable_declaration const& node);
//    bool operator()(ast::wait_statement const& node);
//    bool operator()(ast::waveform const& node);
//    bool operator()(ast::waveform_element const& node);

    bool operator()(ast::nullary const&);

    template<typename T>
    bool operator()(T const&) {
        return true;
    }

private:
    template<typename T>
    std::string symbol_name(T const&);

    void make_error_description(std::string&& rule_name, ast::position_tagged const& position_tag) const;
};


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_ */
