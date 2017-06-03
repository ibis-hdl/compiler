/*
 * ast_printer.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRINTER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRINTER_HPP_


#include <eda/vhdl93/ast.hpp>
#include <eda/utils/indent_stream.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct actual_parameter_part;
struct aggregate;
struct alias_declaration;
struct allocator;
struct architecture_body;
struct architecture_declarative_part;
struct architecture_statement_part;
struct array_type_definition;
struct assertion;
struct assertion_statement;
struct attribute_declaration;
struct attribute_name;
struct attribute_specification;
struct base_unit_declaration;
struct based_integer;
struct based_literal;
struct basic_character;
struct basic_graphic_character;
struct binding_indication;
struct bit_string_literal;
struct block_configuration;
struct block_declarative_item;
struct block_declarative_part;
struct block_header;
struct block_specification;
struct block_statement;
struct block_statement_part;
struct case_statement;
struct case_statement_alternative;
struct character_literal;
struct choice;
struct choices;
struct component_configuration;
struct component_declaration;
struct component_instantiation_statement;
struct component_specification;
struct composite_type_definition;
struct concurrent_assertion_statement;
struct concurrent_procedure_call_statement;
struct concurrent_signal_assignment_statement;
struct concurrent_statement;
struct condition;
struct condition_clause;
struct conditional_signal_assignment;
struct conditional_waveforms;
struct configuration_declaration;
struct configuration_declarative_item;
struct configuration_declarative_part;
struct configuration_item;
struct configuration_specification;
struct constant_declaration;
struct constrained_array_definition;
struct constraint;
struct context_clause;
struct context_item;
struct decimal_literal;
struct declaration;
struct delay_mechanism;
struct design_file;
struct design_unit;
struct designator;
struct disconnection_specification;
struct discrete_range;
struct element_association;
struct element_declaration;
struct element_subtype_definition;
struct entity_aspect;
struct entity_class;
struct entity_class_entry;
struct entity_class_entry_list;
struct entity_declaration;
struct entity_declarative_item;
struct entity_declarative_part;
struct entity_designator;
struct entity_header;
struct entity_name_list;
struct entity_specification;
struct entity_statement;
struct entity_statement_part;
struct entity_tag;
struct enumeration_type_definition;
struct exit_statement;
struct expression;
struct factor_binary_operation;
struct factor_unary_operation;
struct file_declaration;
struct file_logical_name;
struct file_open_information;
struct file_type_definition;
struct formal_parameter_list;
struct full_type_declaration;
struct function_call;
struct generate_statement;
struct generation_scheme;
struct generic_clause;
struct generic_list;
struct generic_map_aspect;
struct graphic_character;
struct group_constituent;
struct group_constituent_list;
struct group_declaration;
struct group_template_declaration;
struct guarded_signal_specification;
struct identifier;
struct identifier_list;
struct if_statement;
struct incomplete_type_declaration;
struct index_constraint;
struct index_specification;
struct index_subtype_definition;
struct instantiated_unit;
struct instantiation_list;
struct integer;
struct integer_type_definition;
struct interface_constant_declaration;
struct interface_declaration;
struct interface_element;
struct interface_file_declaration;
struct interface_list;
struct interface_signal_declaration;
struct interface_variable_declaration;
struct iteration_scheme;
struct library_clause;
struct library_unit;
struct loop_statement;
struct mode;
struct next_statement;
struct null_statement;
struct object_declaration;
struct options;
struct package_body;
struct package_body_declarative_item;
struct package_body_declarative_part;
struct package_declaration;
struct package_declarative_item;
struct package_declarative_part;
struct parameter_specification;
struct physical_literal;
struct physical_type_definition;
struct port_clause;
struct port_list;
struct port_map_aspect;
struct primary_unit;
struct procedure_call;
struct procedure_call_statement;
struct process_declarative_item;
struct process_declarative_part;
struct process_statement;
struct process_statement_part;
struct qualified_expression;
struct range;
struct record_type_definition;
struct relation;
struct report_statement;
struct return_statement;
struct scalar_type_definition;
struct secondary_unit;
struct secondary_unit_declaration;
struct selected_signal_assignment;
struct selected_waveforms;
struct sequence_of_statements;
struct sequential_statement;
struct shift_expression;
struct signal_assignment_statement;
struct signal_declaration;
struct signature;
struct simple_expression;
struct slice_name;
struct string_literal;
struct subprogram_body;
struct subprogram_declaration;
struct subprogram_declarative_item;
struct subprogram_declarative_part;
struct subprogram_kind;
struct subprogram_specification;
struct subprogram_statement_part;
struct subtype_declaration;
struct subtype_indication;
struct target;
struct term;
struct timeout_clause;
struct type_conversion;
struct type_declaration;
struct type_definition;
struct unconstrained_array_definition;
struct use_clause;
struct variable_assignment_statement;
struct variable_declaration;
struct wait_statement;
struct waveform;


} } } // namespace eda.vhdl93.ast


namespace eda { namespace vhdl93 { namespace ast {


class printer
{
    using ostream = ::eda::utils::indent_ostream;

    ostream   os;

    struct scope_printer;

    template<typename T, typename Enable = void>
    struct symbol_scope;

    template<typename NodeT>
    void visit(NodeT const& node) { boost::apply_visitor(*this, node); }


    template<typename T>
    void ast_alias(T const &node, const char* alias_name);

public:
    bool verbose_symbol{ false };
    bool verbose_variant{ false };

public:
    /* FixMe: ugly hack to get visitors printing for BNF ast varaint members.
     * This can be avoided using lambda visitors as described at
     * [visiting variants using lambdas](https://vittorioromeo.info/index/blog/variants_lambdas_part_1.html)
     * but requires boost.hanna and C++17. */
    std::ostream& print(char const str[]) {
        os << str;
        return os;
    }

public:
    printer(std::ostream& out, uint16_t start_indent = 0);


    void operator()(abstract_literal const& node);
    void operator()(access_type_definition const& node);
    void operator()(actual_designator const& node);
    void operator()(actual_parameter_part const& node);
    void operator()(actual_part const& node);
    void operator()(aggregate const& node);
    void operator()(alias_declaration const& node);
    void operator()(alias_designator const& node);
    void operator()(allocator const& node);
    void operator()(architecture_body const& node);
    void operator()(architecture_declarative_part const& node);
    void operator()(architecture_statement_part const& node);
    void operator()(array_type_definition const& node);
    void operator()(assertion const& node);
    void operator()(assertion_statement const& node);
    void operator()(association_element const& node);
    void operator()(association_list const& node);
    void operator()(attribute_declaration const& node);
    void operator()(attribute_name const& node);
    void operator()(attribute_specification const& node);
    void operator()(base_unit_declaration const& node);
    void operator()(based_integer const& node);
    void operator()(based_literal const& node);
    void operator()(basic_character const& node);
    void operator()(basic_graphic_character const& node);
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
    void operator()(condition const& node);
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
    void operator()(declaration const& node);
    void operator()(delay_mechanism const& node);
    void operator()(design_file const& node);
    void operator()(design_unit const& node);
    void operator()(designator const& node);
    void operator()(disconnection_specification const& node);
    void operator()(discrete_range const& node);
    void operator()(element_association const& node);
    void operator()(element_declaration const& node);
    void operator()(element_subtype_definition const& node);
    void operator()(entity_aspect const& node);
    void operator()(entity_class const& node);
    void operator()(entity_class_entry const& node);
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
    void operator()(file_logical_name const& node);
    void operator()(file_open_information const& node);
    void operator()(file_type_definition const& node);
    void operator()(formal_parameter_list const& node);
    void operator()(formal_part const& node);
    void operator()(full_type_declaration const& node);
    void operator()(function_call const& node);
    void operator()(generate_statement const& node);
    void operator()(generation_scheme const& node);
    void operator()(generic_clause const& node);
    void operator()(generic_list const& node);
    void operator()(generic_map_aspect const& node);
    void operator()(graphic_character const& node);
    void operator()(group_constituent const& node);
    void operator()(group_constituent_list const& node);
    void operator()(group_declaration const& node);
    void operator()(group_template_declaration const& node);
    void operator()(guarded_signal_specification const& node);
    void operator()(identifier const& node);
    void operator()(identifier_list const& node);
    void operator()(if_statement const& node);
    void operator()(incomplete_type_declaration const& node);
    void operator()(index_constraint const& node);
    void operator()(index_specification const& node);
    void operator()(index_subtype_definition const& node);
    void operator()(indexed_name const& node);
    void operator()(instantiated_unit const& node);
    void operator()(instantiation_list const& node);
    void operator()(integer const& node);
    void operator()(integer_type_definition const& node);
    void operator()(interface_constant_declaration const& node);
    void operator()(interface_declaration const& node);
    void operator()(interface_element const& node);
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
    void operator()(object_declaration const& node);
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
    void operator()(port_list const& node);
    void operator()(port_map_aspect const& node);
    void operator()(prefix const& node);
    void operator()(primary const& node);
    void operator()(primary_unit const& node);
    void operator()(procedure_call const& node);
    void operator()(procedure_call_statement const& node);
    void operator()(process_declarative_item const& node);
    void operator()(process_declarative_part const& node);
    void operator()(process_statement const& node);
    void operator()(process_statement_part const& node);
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
    void operator()(subprogram_declaration const& node);
    void operator()(subprogram_declarative_item const& node);
    void operator()(subprogram_declarative_part const& node);
    void operator()(subprogram_kind const& node);
    void operator()(subprogram_specification const& node);
    void operator()(subprogram_statement_part const& node);
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
    void operator()(std::string_view const& node);
    void operator()(keyword_token token);

    void operator()(nullary const& node);
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRINTER_HPP_ */
