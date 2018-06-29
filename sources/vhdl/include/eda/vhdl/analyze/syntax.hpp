/*
 * syntax.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_


#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast/util/variant.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/context.hpp>
#include <eda/utils/indent_stream.hpp>

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <functional>
#include <algorithm>
#include <iostream>


namespace eda { namespace vhdl { namespace analyze {


class syntax : boost::static_visitor<bool>
{
    using error_handler_type = std::function<
        void(x3::position_tagged, std::string const&)>;

    utils::indent_ostream mutable                   dbg;
    std::ostream&                                   os;
    vhdl::context&                                  context;
    error_handler_type                              error_handler;

    struct indent_printer;

public:
    template <typename ErrorHandler>
    syntax(std::ostream& os_,
           vhdl::context& context_, ErrorHandler const& error_handler)
      : dbg{ os_, 0 }
      , os{ os_ }
      , context{ context_ }
      , error_handler{
            [&](x3::position_tagged error_position, std::string const& message)
            { error_handler(error_position, message); }
      }
    { }

//    result_type operator()(ast::abstract_literal const& node) const;
//    result_type operator()(ast::access_type_definition const& node) const;
//    result_type operator()(ast::actual_designator const& node) const;
//    result_type operator()(ast::actual_part const& node) const;
//    result_type operator()(ast::aggregate const& node) const;
//    result_type operator()(ast::alias_declaration const& node) const;
//    result_type operator()(ast::alias_designator const& node) const;
//    result_type operator()(ast::allocator const& node) const;
//    result_type operator()(ast::architecture_body const& node) const;
//    result_type operator()(ast::architecture_statement_part const& node) const;
//    result_type operator()(ast::array_type_definition const& node) const;
//    result_type operator()(ast::assertion const& node) const;
//    result_type operator()(ast::assertion_statement const& node) const;
//    result_type operator()(ast::association_element const& node) const;
//    result_type operator()(ast::association_list const& node) const;
//    result_type operator()(ast::attribute_declaration const& node) const;
//    result_type operator()(ast::attribute_name const& node) const;
//    result_type operator()(ast::attribute_specification const& node) const;
//    result_type operator()(ast::based_literal const& node) const;
//    result_type operator()(ast::binding_indication const& node) const;
//    result_type operator()(ast::bit_string_literal const& node) const;
//    result_type operator()(ast::block_configuration const& node) const;
//    result_type operator()(ast::block_declarative_item const& node) const;
//    result_type operator()(ast::block_declarative_part const& node) const;
//    result_type operator()(ast::block_header const& node) const;
//    result_type operator()(ast::block_specification const& node) const;
    result_type operator()(ast::block_statement const& node) const;
//    result_type operator()(ast::block_statement_part const& node) const;
//    result_type operator()(ast::case_statement const& node) const;
//    result_type operator()(ast::case_statement_alternative const& node) const;
//    result_type operator()(ast::character_literal const& node) const;
//    result_type operator()(ast::choice const& node) const;
//    result_type operator()(ast::choices const& node) const;
//    result_type operator()(ast::component_configuration const& node) const;
//    result_type operator()(ast::component_declaration const& node) const;
//    result_type operator()(ast::component_instantiation_statement const& node) const;
//    result_type operator()(ast::component_specification const& node) const;
//    result_type operator()(ast::composite_type_definition const& node) const;
//    result_type operator()(ast::concurrent_assertion_statement const& node) const;
//    result_type operator()(ast::concurrent_procedure_call_statement const& node) const;
//    result_type operator()(ast::concurrent_signal_assignment_statement const& node) const;
//    result_type operator()(ast::concurrent_statement const& node) const;
//    result_type operator()(ast::condition_clause const& node) const;
//    result_type operator()(ast::conditional_signal_assignment const& node) const;
//    result_type operator()(ast::conditional_waveforms const& node) const;
//    result_type operator()(ast::configuration_declaration const& node) const;
//    result_type operator()(ast::configuration_declarative_item const& node) const;
//    result_type operator()(ast::configuration_declarative_part const& node) const;
//    result_type operator()(ast::configuration_item const& node) const;
//    result_type operator()(ast::configuration_specification const& node) const;
//    result_type operator()(ast::constant_declaration const& node) const;
//    result_type operator()(ast::constrained_array_definition const& node) const;
//    result_type operator()(ast::constraint const& node) const;
//    result_type operator()(ast::context_clause const& node) const;
//    result_type operator()(ast::context_item const& node) const;
//    result_type operator()(ast::decimal_literal const& node) const;
//    result_type operator()(ast::delay_mechanism const& node) const;
    result_type operator()(ast::design_file const& node) const;
    result_type operator()(ast::design_unit const& node) const;
//    result_type operator()(ast::designator const& node) const;
//    result_type operator()(ast::disconnection_specification const& node) const;
//    result_type operator()(ast::discrete_range const& node) const;
//    result_type operator()(ast::element_association const& node) const;
//    result_type operator()(ast::element_declaration const& node) const;
//    result_type operator()(ast::entity_aspect const& node) const;
//    result_type operator()(ast::entity_class_entry_list const& node) const;
//    result_type operator()(ast::entity_declaration const& node) const;
//    result_type operator()(ast::entity_declarative_item const& node) const;
//    result_type operator()(ast::entity_declarative_part const& node) const;
//    result_type operator()(ast::entity_designator const& node) const;
//    result_type operator()(ast::entity_header const& node) const;
//    result_type operator()(ast::entity_name_list const& node) const;
//    result_type operator()(ast::entity_specification const& node) const;
//    result_type operator()(ast::entity_statement const& node) const;
//    result_type operator()(ast::entity_statement_part const& node) const;
//    result_type operator()(ast::entity_tag const& node) const;
//    result_type operator()(ast::enumeration_literal const& node) const;
//    result_type operator()(ast::enumeration_type_definition const& node) const;
//    result_type operator()(ast::exit_statement const& node) const;
//    result_type operator()(ast::expression const& node) const;
//    result_type operator()(ast::factor_binary_operation const& node) const;
//    result_type operator()(ast::factor_unary_operation const& node) const;
//    result_type operator()(ast::factor const& node) const;
//    result_type operator()(ast::file_declaration const& node) const;
//    result_type operator()(ast::file_open_information const& node) const;
//    result_type operator()(ast::formal_part const& node) const;
//    result_type operator()(ast::function_call const& node) const;
//    result_type operator()(ast::generate_statement const& node) const;
//    result_type operator()(ast::generation_scheme const& node) const;
//    result_type operator()(ast::generic_clause const& node) const;
//    result_type operator()(ast::generic_map_aspect const& node) const;
//    result_type operator()(ast::group_constituent const& node) const;
//    result_type operator()(ast::group_constituent_list const& node) const;
//    result_type operator()(ast::group_declaration const& node) const;
//    result_type operator()(ast::group_template_declaration const& node) const;
//    result_type operator()(ast::guarded_signal_specification const& node) const;
//    result_type operator()(ast::identifier const& node) const;
//    result_type operator()(ast::identifier_list const& node) const;
//    result_type operator()(ast::if_statement const& node) const;
//    result_type operator()(ast::index_constraint const& node) const;
//    result_type operator()(ast::index_specification const& node) const;
//    result_type operator()(ast::index_subtype_definition const& node) const;
//    result_type operator()(ast::indexed_name const& node) const;
//    result_type operator()(ast::instantiated_unit const& node) const;
//    result_type operator()(ast::instantiation_list const& node) const;
//    result_type operator()(ast::interface_constant_declaration const& node) const;
//    result_type operator()(ast::interface_declaration const& node) const;
//    result_type operator()(ast::interface_file_declaration const& node) const;
//    result_type operator()(ast::interface_list const& node) const;
//    result_type operator()(ast::interface_signal_declaration const& node) const;
//    result_type operator()(ast::interface_variable_declaration const& node) const;
//    result_type operator()(ast::iteration_scheme const& node) const;
    result_type operator()(ast::library_clause const& node) const;
//    result_type operator()(ast::library_unit const& node) const;
//    result_type operator()(ast::literal const& node) const;
//    result_type operator()(ast::loop_statement const& node) const;
//    result_type operator()(ast::name const& node) const;
//    result_type operator()(ast::next_statement const& node) const;
//    result_type operator()(ast::null_statement const& node) const;
//    result_type operator()(ast::numeric_literal const& node) const;
//    result_type operator()(ast::options const& node) const;
//    result_type operator()(ast::package_body const& node) const;
//    result_type operator()(ast::package_body_declarative_item const& node) const;
//    result_type operator()(ast::package_body_declarative_part const& node) const;
//    result_type operator()(ast::package_declaration const& node) const;
//    result_type operator()(ast::package_declarative_item const& node) const;
//    result_type operator()(ast::package_declarative_part const& node) const;
//    result_type operator()(ast::parameter_specification const& node) const;
//    result_type operator()(ast::physical_literal const& node) const;
//    result_type operator()(ast::physical_type_definition const& node) const;
//    result_type operator()(ast::port_clause const& node) const;
//    result_type operator()(ast::port_map_aspect const& node) const;
//    result_type operator()(ast::prefix const& node) const;
//    result_type operator()(ast::primary const& node) const;
//    result_type operator()(ast::primary_unit const& node) const;
//    result_type operator()(ast::procedure_call const& node) const;
//    result_type operator()(ast::procedure_call_statement const& node) const;
//    result_type operator()(ast::process_declarative_item const& node) const;
//    result_type operator()(ast::process_declarative_part const& node) const;
//    result_type operator()(ast::process_statement const& node) const;
//    result_type operator()(ast::qualified_expression const& node) const;
//    result_type operator()(ast::range const& node) const;
//    result_type operator()(ast::record_type_definition const& node) const;
//    result_type operator()(ast::relation const& node) const;
//    result_type operator()(ast::report_statement const& node) const;
//    result_type operator()(ast::return_statement const& node) const;
//    result_type operator()(ast::scalar_type_definition const& node) const;
//    result_type operator()(ast::secondary_unit const& node) const;
//    result_type operator()(ast::secondary_unit_declaration const& node) const;
//    result_type operator()(ast::selected_name const& node) const;
//    result_type operator()(ast::selected_signal_assignment const& node) const;
//    result_type operator()(ast::selected_waveforms const& node) const;
//    result_type operator()(ast::sensitivity_clause const& node) const;
//    result_type operator()(ast::sensitivity_list const& node) const;
//    result_type operator()(ast::sequence_of_statements const& node) const;
//    result_type operator()(ast::sequential_statement const& node) const;
//    result_type operator()(ast::shift_expression const& node) const;
//    result_type operator()(ast::signal_assignment_statement const& node) const;
//    result_type operator()(ast::signal_declaration const& node) const;
//    result_type operator()(ast::signal_list_list const& node) const; // signal_list helper (not in BNF)
//    result_type operator()(ast::signal_list const& node) const;
//    result_type operator()(ast::signature const& node) const;
//    result_type operator()(ast::simple_expression const& node) const;
//    result_type operator()(ast::slice_name const& node) const;
//    result_type operator()(ast::string_literal const& node) const;
//    result_type operator()(ast::subprogram_body const& node) const;
//    result_type operator()(ast::subprogram_declarative_item const& node) const;
//    result_type operator()(ast::subprogram_declarative_part const& node) const;
//    result_type operator()(ast::subprogram_specification const& node) const;
//    result_type operator()(ast::subtype_declaration const& node) const;
//    result_type operator()(ast::subtype_indication const& node) const;
//    result_type operator()(ast::suffix const& node) const;
//    result_type operator()(ast::target const& node) const;
//    result_type operator()(ast::term const& node) const;
//    result_type operator()(ast::timeout_clause const& node) const;
//    result_type operator()(ast::type_conversion const& node) const;
//    result_type operator()(ast::type_declaration const& node) const;
//    result_type operator()(ast::type_definition const& node) const;
//    result_type operator()(ast::unconstrained_array_definition const& node) const;
    result_type operator()(ast::use_clause const& node) const;
//    result_type operator()(ast::variable_assignment_statement const& node) const;
//    result_type operator()(ast::variable_declaration const& node) const;
//    result_type operator()(ast::wait_statement const& node) const;
//    result_type operator()(ast::waveform const& node) const;
//    result_type operator()(ast::waveform_element const& node) const;
//
//    // keywords and miscellaneous
//    result_type operator()(ast::boost::iterator_range<parser::iterator_type> const& node) const;
//    result_type operator()(ast::keyword_token token);
//
    result_type operator()(ast::nullary const& node) const;

public:
    template<typename ...Types>
    result_type operator()(ast::variant<Types...> const& node) const {
        return boost::apply_visitor(*this, node);
    }

    template<typename T>
    result_type operator()(std::vector<T> const& node) const {
        return std::all_of(node.begin(), node.end(),
                          [&](T const& x){ return (*this)(x); } );
    }

    template<typename T>
    result_type operator()(T const& stray_sink) const;

};


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_ */
