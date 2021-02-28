/*
 * ast_printer.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRINTER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRINTER_HPP_

#include <eda/vhdl/ast.hpp>

#include <eda/util/indent_stream.hpp>

namespace eda {
namespace vhdl {
namespace ast {

class printer 
{
public:
    bool verbose_symbol{ false };
    bool verbose_variant{ false };

public:
    printer(std::ostream& os_, uint16_t start_indent = 0);

    void operator()(abstract_literal const& node);
    void operator()(access_type_definition const& node);
    void operator()(actual_designator const& node);
    void operator()(actual_part const& node);
    void operator()(aggregate const& node);
    void operator()(alias_declaration const& node);
    void operator()(alias_designator const& node);
    void operator()(allocator const& node);
    void operator()(architecture_body const& node);
    void operator()(architecture_statement_part const& node);
    void operator()(array_type_definition const& node);
    void operator()(assertion const& node);
    void operator()(assertion_statement const& node);
    void operator()(association_element const& node);
    void operator()(association_list const& node);
    void operator()(attribute_declaration const& node);
    void operator()(attribute_name const& node);
    void operator()(attribute_specification const& node);
    void operator()(based_literal const& node);
    void operator()(binding_indication const& node);
    void operator()(bit_string_literal const& node);
    void operator()(block_configuration const& node);
    void operator()(block_declarative_item const& node);
    void operator()(block_declarative_part const& node);
    void operator()(block_header const& node);
    void operator()(block_specification const& node);
    void operator()(block_statement const& node);
    void operator()(block_statement_part const& node);
    void operator()(case_statement const& node);
    void operator()(case_statement_alternative const& node);
    void operator()(character_literal const& node);
    void operator()(choice const& node);
    void operator()(choices const& node);
    void operator()(component_configuration const& node);
    void operator()(component_declaration const& node);
    void operator()(component_instantiation_statement const& node);
    void operator()(component_specification const& node);
    void operator()(composite_type_definition const& node);
    void operator()(concurrent_assertion_statement const& node);
    void operator()(concurrent_procedure_call_statement const& node);
    void operator()(concurrent_signal_assignment_statement const& node);
    void operator()(concurrent_statement const& node);
    void operator()(condition_clause const& node);
    void operator()(conditional_signal_assignment const& node);
    void operator()(conditional_waveforms const& node);
    void operator()(configuration_declaration const& node);
    void operator()(configuration_declarative_item const& node);
    void operator()(configuration_declarative_part const& node);
    void operator()(configuration_item const& node);
    void operator()(configuration_specification const& node);
    void operator()(constant_declaration const& node);
    void operator()(constrained_array_definition const& node);
    void operator()(constraint const& node);
    void operator()(context_clause const& node);
    void operator()(context_item const& node);
    void operator()(decimal_literal const& node);
    void operator()(delay_mechanism const& node);
    void operator()(design_file const& node);
    void operator()(design_unit const& node);
    void operator()(designator const& node);
    void operator()(disconnection_specification const& node);
    void operator()(discrete_range const& node);
    void operator()(element_association const& node);
    void operator()(element_declaration const& node);
    void operator()(entity_aspect const& node);
    void operator()(entity_class_entry_list const& node);
    void operator()(entity_declaration const& node);
    void operator()(entity_declarative_item const& node);
    void operator()(entity_declarative_part const& node);
    void operator()(entity_designator const& node);
    void operator()(entity_header const& node);
    void operator()(entity_name_list const& node);
    void operator()(entity_specification const& node);
    void operator()(entity_statement const& node);
    void operator()(entity_statement_part const& node);
    void operator()(entity_tag const& node);
    void operator()(enumeration_literal const& node);
    void operator()(enumeration_type_definition const& node);
    void operator()(exit_statement const& node);
    void operator()(expression const& node);
    void operator()(factor_binary_operation const& node);
    void operator()(factor_unary_operation const& node);
    void operator()(factor const& node);
    void operator()(file_declaration const& node);
    void operator()(file_open_information const& node);
    void operator()(formal_part const& node);
    void operator()(function_call const& node);
    void operator()(generate_statement const& node);
    void operator()(generation_scheme const& node);
    void operator()(generic_clause const& node);
    void operator()(generic_map_aspect const& node);
    void operator()(group_constituent const& node);
    void operator()(group_constituent_list const& node);
    void operator()(group_declaration const& node);
    void operator()(group_template_declaration const& node);
    void operator()(guarded_signal_specification const& node);
    void operator()(identifier const& node);
    void operator()(identifier_list const& node);
    void operator()(if_statement const& node);
    void operator()(index_constraint const& node);
    void operator()(index_specification const& node);
    void operator()(index_subtype_definition const& node);
    void operator()(indexed_name const& node);
    void operator()(instantiated_unit const& node);
    void operator()(instantiation_list const& node);
    void operator()(interface_constant_declaration const& node);
    void operator()(interface_declaration const& node);
    void operator()(interface_file_declaration const& node);
    void operator()(interface_list const& node);
    void operator()(interface_signal_declaration const& node);
    void operator()(interface_variable_declaration const& node);
    void operator()(iteration_scheme const& node);
    void operator()(library_clause const& node);
    void operator()(library_unit const& node);
    void operator()(literal const& node);
    void operator()(loop_statement const& node);
    void operator()(name const& node);
    void operator()(next_statement const& node);
    void operator()(null_statement const& node);
    void operator()(numeric_literal const& node);
    void operator()(options const& node);
    void operator()(package_body const& node);
    void operator()(package_body_declarative_item const& node);
    void operator()(package_body_declarative_part const& node);
    void operator()(package_declaration const& node);
    void operator()(package_declarative_item const& node);
    void operator()(package_declarative_part const& node);
    void operator()(parameter_specification const& node);
    void operator()(physical_literal const& node);
    void operator()(physical_type_definition const& node);
    void operator()(port_clause const& node);
    void operator()(port_map_aspect const& node);
    void operator()(prefix const& node);
    void operator()(primary const& node);
    void operator()(primary_unit const& node);
    void operator()(procedure_call const& node);
    void operator()(procedure_call_statement const& node);
    void operator()(process_declarative_item const& node);
    void operator()(process_declarative_part const& node);
    void operator()(process_statement const& node);
    void operator()(qualified_expression const& node);
    void operator()(range const& node);
    void operator()(record_type_definition const& node);
    void operator()(relation const& node);
    void operator()(report_statement const& node);
    void operator()(return_statement const& node);
    void operator()(scalar_type_definition const& node);
    void operator()(secondary_unit const& node);
    void operator()(secondary_unit_declaration const& node);
    void operator()(selected_name const& node);
    void operator()(selected_signal_assignment const& node);
    void operator()(selected_waveforms const& node);
    void operator()(sensitivity_clause const& node);
    void operator()(sensitivity_list const& node);
    void operator()(sequence_of_statements const& node);
    void operator()(sequential_statement const& node);
    void operator()(shift_expression const& node);
    void operator()(signal_assignment_statement const& node);
    void operator()(signal_declaration const& node);
    void operator()(signal_list_list const& node); // signal_list helper (not in BNF)
    void operator()(signal_list const& node);
    void operator()(signature const& node);
    void operator()(simple_expression const& node);
    void operator()(slice_name const& node);
    void operator()(string_literal const& node);
    void operator()(subprogram_body const& node);
    void operator()(subprogram_declarative_item const& node);
    void operator()(subprogram_declarative_part const& node);
    void operator()(subprogram_specification const& node);
    void operator()(subtype_declaration const& node);
    void operator()(subtype_indication const& node);
    void operator()(suffix const& node);
    void operator()(target const& node);
    void operator()(term const& node);
    void operator()(timeout_clause const& node);
    void operator()(type_conversion const& node);
    void operator()(type_declaration const& node);
    void operator()(type_definition const& node);
    void operator()(unconstrained_array_definition const& node);
    void operator()(use_clause const& node);
    void operator()(variable_assignment_statement const& node);
    void operator()(variable_declaration const& node);
    void operator()(wait_statement const& node);
    void operator()(waveform const& node);
    void operator()(waveform_element const& node);

    // keywords and miscellaneous
    void operator()(ast::string_span const& node);
    void operator()(keyword_token token);

    void operator()(nullary const& node);

    //    template<typename T>
    //    void operator()(T const& node);

private:
    // internal helper
    class scope_printer;

    // yet another internal helper
    template <typename T, typename Enable = void> struct symbol_scope;

    template <typename... Ts> void visit(variant<Ts...> const& node)
    {
        boost::apply_visitor(*this, node);
    }

    template <typename T> void visit(std::vector<T> const& vector);

private:
    // clang-format off
    util::indent_ostream                            os;
    // clang-format on
};

} // namespace ast
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRINTER_HPP_ */
