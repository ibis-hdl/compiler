/*
 * ast_printer.cpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast_printer.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>
#include <eda/exception.hpp>

#include <boost/exception/all.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"




namespace eda { namespace vhdl93 { namespace ast {


struct printer::scope_printer
{
    scope_printer(printer const& parent, bool verbose, char const name[], char const name_pfx[] = nullptr)
    : parent{ parent }
    , verbose{ verbose }
    , name{ name }
    {
        if(verbose) {
            parent.os << parent.prefix_;
            if(name_pfx)
                parent.os << name_pfx;
            parent.os << name << "=";
        }
    }

    ~scope_printer()
    {
        if(verbose) {
            parent.os << parent.postfix_;
        }
    }

    printer const& parent;
    bool const verbose;
    const char* const name{ nullptr };
};


struct printer::symbol_scope
: public scope_printer
{
    symbol_scope(printer const& parent, char const name[])
    : scope_printer(parent, parent.verbose_symbol, name)
    { }
};


struct printer::variant_scope
: public scope_printer
{
    variant_scope(printer const& parent, char const name[])
    : scope_printer(parent, parent.verbose_variant, name, "v:")
    { }
};


void printer::tab(uint16_t spaces)
{
    for (unsigned i=0; i != spaces; ++i)
        os << ' ';
}


} } } // namespace eda.vhdl93.ast


namespace eda { namespace vhdl93 { namespace ast {



void printer::operator()(abstract_literal const &node) const 
{
    static char const symbol[]{ "abstract_literal" };
    variant_scope _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(access_type_definition const &node) const 
{
    static char const symbol[]{ "XXX access_type_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(actual_designator const &node) const 
{
    static char const symbol[]{ "XXX actual_designator" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(actual_parameter_part const &node) const 
{
    static char const symbol[]{ "XXX actual_parameter_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(actual_part const &node) const 
{
    static char const symbol[]{ "XXX actual_part" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(aggregate const &node) const 
{
    static char const symbol[]{ "XXX aggregate" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(alias_declaration const &node) const 
{
    static char const symbol[]{ "XXX alias_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(alias_designator const &node) const 
{
    static char const symbol[]{ "XXX alias_designator" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(allocator const &node) const 
{
    static char const symbol[]{ "XXX allocator" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(architecture_body const &node) const 
{
    static char const symbol[]{ "XXX architecture_body" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(architecture_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX architecture_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(architecture_statement_part const &node) const 
{
    static char const symbol[]{ "XXX architecture_statement_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(array_type_definition const &node) const 
{
    static char const symbol[]{ "XXX array_type_definition" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(assertion const &node) const 
{
    static char const symbol[]{ "XXX assertion" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(assertion_statement const &node) const 
{
    static char const symbol[]{ "XXX assertion_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(association_element const &node) const 
{
    static char const symbol[]{ "XXX association_element" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(association_list const &node) const 
{
    static char const symbol[]{ "XXX association_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(attribute_declaration const &node) const 
{
    static char const symbol[]{ "XXX attribute_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(attribute_designator const &node) const 
{
    static char const symbol[]{ "XXX attribute_designator" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(attribute_name const &node) const 
{
    static char const symbol[]{ "XXX attribute_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(attribute_specification const &node) const 
{
    static char const symbol[]{ "XXX attribute_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(base const &node) const 
{
    static char const symbol[]{ "XXX base" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(base_unit_declaration const &node) const 
{
    static char const symbol[]{ "XXX base_unit_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(based_integer const &node) const 
{
    static char const symbol[]{ "XXX based_integer" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(based_literal const &node) const 
{
    static char const symbol[]{ "based_literal" };
    symbol_scope _(*this, symbol);

    os << "{b=" << node.base << ", n=" << node.literal << "}";
}


void printer::operator()(basic_character const &node) const 
{
    static char const symbol[]{ "XXX basic_character" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(basic_graphic_character const &node) const 
{
    static char const symbol[]{ "XXX basic_graphic_character" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(binding_indication const &node) const 
{
    static char const symbol[]{ "XXX binding_indication" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(bit_string_literal const &node) const 
{
    static char const symbol[]{ "bit_string_literal" };
    symbol_scope _(*this, symbol);

	using tag = bit_string_literal::tag;

    os << "{l=" << node.literal << ", tag=";

    switch(node.hint) {
        case tag::bin: os << "bin"; break;
        case tag::oct: os << "oct"; break;
        case tag::hex: os << "hex"; break;
        default:       os << "INVALID";
    }

    os << "}";
}


void printer::operator()(block_configuration const &node) const 
{
    static char const symbol[]{ "XXX block_configuration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(block_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX block_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(block_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX block_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(block_header const &node) const 
{
    static char const symbol[]{ "XXX block_header" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(block_specification const &node) const 
{
    static char const symbol[]{ "XXX block_specification" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(block_statement const &node) const 
{
    static char const symbol[]{ "XXX block_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(block_statement_part const &node) const 
{
    static char const symbol[]{ "XXX block_statement_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(case_statement const &node) const 
{
    static char const symbol[]{ "XXX case_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(case_statement_alternative const &node) const 
{
    static char const symbol[]{ "XXX case_statement_alternative" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(character_literal const &node) const 
{
    static char const symbol[]{ "character_literal" };
    symbol_scope _(*this, symbol);

    os << node.literal;
}


void printer::operator()(choice const &node) const 
{
    static char const symbol[]{ "XXX choice" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(choices const &node) const 
{
    static char const symbol[]{ "XXX choices" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(component_configuration const &node) const 
{
    static char const symbol[]{ "XXX component_configuration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(component_declaration const &node) const 
{
    static char const symbol[]{ "XXX component_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(component_instantiation_statement const &node) const 
{
    static char const symbol[]{ "XXX component_instantiation_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(component_specification const &node) const 
{
    static char const symbol[]{ "XXX component_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(composite_type_definition const &node) const 
{
    static char const symbol[]{ "XXX composite_type_definition" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(concurrent_assertion_statement const &node) const 
{
    static char const symbol[]{ "XXX concurrent_assertion_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(concurrent_procedure_call_statement const &node) const 
{
    static char const symbol[]{ "XXX concurrent_procedure_call_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(concurrent_signal_assignment_statement const &node) const 
{
    static char const symbol[]{ "XXX concurrent_signal_assignment_statement" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(concurrent_statement const &node) const 
{
    static char const symbol[]{ "XXX concurrent_statement" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(condition const &node) const 
{
    static char const symbol[]{ "XXX condition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(condition_clause const &node) const 
{
    static char const symbol[]{ "XXX condition_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(conditional_signal_assignment const &node) const 
{
    static char const symbol[]{ "XXX conditional_signal_assignment" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(conditional_waveforms const &node) const 
{
    static char const symbol[]{ "XXX conditional_waveforms" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(configuration_declaration const &node) const 
{
    static char const symbol[]{ "XXX configuration_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(configuration_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX configuration_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(configuration_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX configuration_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(configuration_item const &node) const 
{
    static char const symbol[]{ "XXX configuration_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(configuration_specification const &node) const 
{
    static char const symbol[]{ "XXX configuration_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(constant_declaration const &node) const 
{
    static char const symbol[]{ "XXX constant_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(constrained_array_definition const &node) const 
{
    static char const symbol[]{ "XXX constrained_array_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(constraint const &node) const 
{
    static char const symbol[]{ "XXX constraint" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(context_clause const &node) const 
{
    static char const symbol[]{ "XXX context_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(context_item const &node) const 
{
    static char const symbol[]{ "XXX context_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(decimal_literal const &node) const 
{
    static char const symbol[]{ "decimal_literal" };
    symbol_scope _(*this, symbol);

	using tag = decimal_literal::tag;

    os << "{l=" << node.literal << ", tag=";

    switch(node.hint) {
        case tag::integer: os << "int";    break;
        case tag::real:    os << "double"; break;
        default:           os << "INVALID";
    }

    os << "}";
}


void printer::operator()(declaration const &node) const 
{
    static char const symbol[]{ "XXX declaration" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(delay_mechanism const &node) const 
{
    static char const symbol[]{ "XXX delay_mechanism" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(design_file const &node) const 
{
    static char const symbol[]{ "XXX design_file" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(design_unit const &node) const 
{
    static char const symbol[]{ "XXX design_unit" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(designator const &node) const 
{
    static char const symbol[]{ "XXX designator" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(direction const &node) const 
{
    static char const symbol[]{ "XXX direction" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(disconnection_specification const &node) const 
{
    static char const symbol[]{ "XXX disconnection_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(discrete_range const &node) const 
{
    static char const symbol[]{ "XXX discrete_range" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(element_association const &node) const 
{
    static char const symbol[]{ "XXX element_association" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(element_declaration const &node) const 
{
    static char const symbol[]{ "XXX element_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(element_subtype_definition const &node) const 
{
    static char const symbol[]{ "XXX element_subtype_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_aspect const &node) const 
{
    static char const symbol[]{ "XXX entity_aspect" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_class const &node) const 
{
    static char const symbol[]{ "XXX entity_class" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_class_entry const &node) const 
{
    static char const symbol[]{ "XXX entity_class_entry" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_class_entry_list const &node) const 
{
    static char const symbol[]{ "XXX entity_class_entry_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_declaration const &node) const 
{
    static char const symbol[]{ "XXX entity_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX entity_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX entity_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_designator const &node) const 
{
    static char const symbol[]{ "XXX entity_designator" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_header const &node) const 
{
    static char const symbol[]{ "XXX entity_header" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_name_list const &node) const 
{
    static char const symbol[]{ "XXX entity_name_list" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_specification const &node) const 
{
    static char const symbol[]{ "XXX entity_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_statement const &node) const 
{
    static char const symbol[]{ "XXX entity_statement" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_statement_part const &node) const 
{
    static char const symbol[]{ "XXX entity_statement_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(entity_tag const &node) const 
{
    static char const symbol[]{ "XXX entity_tag" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(enumeration_literal const &node) const 
{
    static char const symbol[]{ "enumeration_literal" };
    variant_scope _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(enumeration_type_definition const &node) const 
{
    static char const symbol[]{ "XXX enumeration_type_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(exit_statement const &node) const 
{
    static char const symbol[]{ "XXX exit_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(exponent const &node) const 
{
    static char const symbol[]{ "XXX exponent" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(expression const &node) const 
{
    static char const symbol[]{ "XXX expression" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(factor const &node) const 
{
    static char const symbol[]{ "XXX factor" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(file_declaration const &node) const 
{
    static char const symbol[]{ "XXX file_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(file_logical_name const &node) const 
{
    static char const symbol[]{ "XXX file_logical_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(file_open_information const &node) const 
{
    static char const symbol[]{ "XXX file_open_information" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(file_type_definition const &node) const 
{
    static char const symbol[]{ "XXX file_type_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(formal_designator const &node) const 
{
    static char const symbol[]{ "XXX formal_designator" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(formal_parameter_list const &node) const 
{
    static char const symbol[]{ "XXX formal_parameter_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(formal_part const &node) const 
{
    static char const symbol[]{ "XXX formal_part" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(full_type_declaration const &node) const 
{
    static char const symbol[]{ "XXX full_type_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(function_call const &node) const 
{
    static char const symbol[]{ "XXX function_call" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(generate_statement const &node) const 
{
    static char const symbol[]{ "XXX generate_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(generation_scheme const &node) const 
{
    static char const symbol[]{ "XXX generation_scheme" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(generic_clause const &node) const 
{
    static char const symbol[]{ "XXX generic_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(generic_list const &node) const 
{
    static char const symbol[]{ "XXX generic_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(generic_map_aspect const &node) const 
{
    static char const symbol[]{ "XXX generic_map_aspect" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(graphic_character const &node) const 
{
    static char const symbol[]{ "XXX graphic_character" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(group_constituent const &node) const 
{
    static char const symbol[]{ "XXX group_constituent" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(group_constituent_list const &node) const 
{
    static char const symbol[]{ "XXX group_constituent_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(group_declaration const &node) const 
{
    static char const symbol[]{ "XXX group_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(group_template_declaration const &node) const 
{
    static char const symbol[]{ "XXX group_template_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(guarded_signal_specification const &node) const 
{
    static char const symbol[]{ "XXX guarded_signal_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(identifier const &node) const 
{
    static char const symbol[]{ "identifier" };
    symbol_scope _(*this, symbol);
    os << node.name;
}


void printer::operator()(identifier_list const &node) const 
{
    static char const symbol[]{ "XXX identifier_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(if_statement const &node) const 
{
    static char const symbol[]{ "XXX if_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(incomplete_type_declaration const &node) const 
{
    static char const symbol[]{ "XXX incomplete_type_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(index_constraint const &node) const 
{
    static char const symbol[]{ "XXX index_constraint" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(index_specification const &node) const 
{
    static char const symbol[]{ "XXX index_specification" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(index_subtype_definition const &node) const 
{
    static char const symbol[]{ "XXX index_subtype_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(indexed_name const &node) const 
{
    static char const symbol[]{ "XXX indexed_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(instantiated_unit const &node) const 
{
    static char const symbol[]{ "XXX instantiated_unit" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(instantiation_list const &node) const 
{
    static char const symbol[]{ "XXX instantiation_list" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(integer const &node) const 
{
    static char const symbol[]{ "XXX integer" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(integer_type_definition const &node) const 
{
    static char const symbol[]{ "XXX integer_type_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(interface_constant_declaration const &node) const 
{
    static char const symbol[]{ "XXX interface_constant_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(interface_declaration const &node) const 
{
    static char const symbol[]{ "XXX interface_declaration" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(interface_element const &node) const 
{
    static char const symbol[]{ "XXX interface_element" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(interface_file_declaration const &node) const 
{
    static char const symbol[]{ "XXX interface_file_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(interface_list const &node) const 
{
    static char const symbol[]{ "XXX interface_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(interface_signal_declaration const &node) const 
{
    static char const symbol[]{ "XXX interface_signal_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(interface_variable_declaration const &node) const 
{
    static char const symbol[]{ "XXX interface_variable_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(iteration_scheme const &node) const 
{
    static char const symbol[]{ "XXX iteration_scheme" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(label const &node) const 
{
    static char const symbol[]{ "XXX label" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(library_clause const &node) const 
{
    static char const symbol[]{ "XXX library_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(library_unit const &node) const 
{
    static char const symbol[]{ "XXX library_unit" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(literal const &node) const 
{
    static char const symbol[]{ "literal" };
    variant_scope _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(logical_name const &node) const 
{
    static char const symbol[]{ "XXX logical_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(logical_name_list const &node) const 
{
    static char const symbol[]{ "XXX logical_name_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(loop_statement const &node) const 
{
    static char const symbol[]{ "XXX loop_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(mode const &node) const 
{
    static char const symbol[]{ "XXX mode" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(name const &node) const 
{
    static char const symbol[]{ "XXX name" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(next_statement const &node) const 
{
    static char const symbol[]{ "XXX next_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(null_statement const &node) const 
{
    static char const symbol[]{ "XXX null_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(numeric_literal const &node) const 
{
    static char const symbol[]{ "numeric_literal" };
    variant_scope _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(object_declaration const &node) const 
{
    static char const symbol[]{ "XXX object_declaration" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(operator_symbol const &node) const 
{
    static char const symbol[]{ "XXX operator_symbol" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(options const &node) const 
{
    static char const symbol[]{ "XXX options" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(package_body const &node) const 
{
    static char const symbol[]{ "XXX package_body" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(package_body_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX package_body_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(package_body_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX package_body_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(package_declaration const &node) const 
{
    static char const symbol[]{ "XXX package_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(package_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX package_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(package_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX package_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(parameter_specification const &node) const 
{
    static char const symbol[]{ "XXX parameter_specification" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(physical_literal const &node) const 
{
    static char const symbol[]{ "physical_literal" };
    symbol_scope _(*this, symbol);

    os << "{l=";
    (*this)(node.literal);
    os << ", u=" << node.unit_name;
    os << "}";
}


void printer::operator()(physical_type_definition const &node) const 
{
    static char const symbol[]{ "XXX physical_type_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(port_clause const &node) const 
{
    static char const symbol[]{ "XXX port_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(port_list const &node) const 
{
    static char const symbol[]{ "XXX port_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(port_map_aspect const &node) const 
{
    static char const symbol[]{ "XXX port_map_aspect" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(prefix const &node) const 
{
    static char const symbol[]{ "XXX prefix" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(primary const &node) const 
{
    static char const symbol[]{ "XXX primary" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(primary_unit const &node) const 
{
    static char const symbol[]{ "XXX primary_unit" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(procedure_call const &node) const 
{
    static char const symbol[]{ "XXX procedure_call" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(procedure_call_statement const &node) const 
{
    static char const symbol[]{ "XXX procedure_call_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(process_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX process_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(process_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX process_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(process_statement const &node) const 
{
    static char const symbol[]{ "XXX process_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(process_statement_part const &node) const 
{
    static char const symbol[]{ "XXX process_statement_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(qualified_expression const &node) const 
{
    static char const symbol[]{ "XXX qualified_expression" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(range const &node) const 
{
    static char const symbol[]{ "XXX range" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(range_constraint const &node) const 
{
    static char const symbol[]{ "XXX range_constraint" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(record_type_definition const &node) const 
{
    static char const symbol[]{ "XXX record_type_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(relation const &node) const 
{
    static char const symbol[]{ "XXX relation" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(report_statement const &node) const 
{
    static char const symbol[]{ "XXX report_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(return_statement const &node) const 
{
    static char const symbol[]{ "XXX return_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(scalar_type_definition const &node) const 
{
    static char const symbol[]{ "XXX scalar_type_definition" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(secondary_unit const &node) const 
{
    static char const symbol[]{ "XXX secondary_unit" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(secondary_unit_declaration const &node) const 
{
    static char const symbol[]{ "XXX secondary_unit_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(selected_name const &node) const 
{
    static char const symbol[]{ "XXX selected_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(selected_signal_assignment const &node) const 
{
    static char const symbol[]{ "XXX selected_signal_assignment" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(selected_waveforms const &node) const 
{
    static char const symbol[]{ "XXX selected_waveforms" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(sensitivity_clause const &node) const 
{
    static char const symbol[]{ "XXX sensitivity_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(sensitivity_list const &node) const 
{
    static char const symbol[]{ "XXX sensitivity_list" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(sequence_of_statements const &node) const 
{
    static char const symbol[]{ "XXX sequence_of_statements" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(sequential_statement const &node) const 
{
    static char const symbol[]{ "XXX sequential_statement" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(shift_expression const &node) const 
{
    static char const symbol[]{ "XXX shift_expression" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(sign const &node) const 
{
    static char const symbol[]{ "XXX sign" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(signal_assignment_statement const &node) const 
{
    static char const symbol[]{ "XXX signal_assignment_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(signal_declaration const &node) const 
{
    static char const symbol[]{ "XXX signal_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(signal_kind const &node) const 
{
    static char const symbol[]{ "XXX signal_kind" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(signal_list const &node) const 
{
    static char const symbol[]{ "XXX signal_list" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(signature const &node) const 
{
    static char const symbol[]{ "XXX signature" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(simple_expression const &node) const 
{
    static char const symbol[]{ "XXX simple_expression" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(simple_name const &node) const 
{
    static char const symbol[]{ "XXX simple_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(slice_name const &node) const 
{
    static char const symbol[]{ "XXX slice_name" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(string_literal const &node) const 
{
    static char const symbol[]{ "string_literal" };
    symbol_scope _(*this, symbol);

    os << node;
}


void printer::operator()(subprogram_body const &node) const 
{
    static char const symbol[]{ "XXX subprogram_body" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(subprogram_declaration const &node) const 
{
    static char const symbol[]{ "XXX subprogram_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(subprogram_declarative_item const &node) const 
{
    static char const symbol[]{ "XXX subprogram_declarative_item" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(subprogram_declarative_part const &node) const 
{
    static char const symbol[]{ "XXX subprogram_declarative_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(subprogram_kind const &node) const 
{
    static char const symbol[]{ "XXX subprogram_kind" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(subprogram_specification const &node) const 
{
    static char const symbol[]{ "XXX subprogram_specification" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(subprogram_statement_part const &node) const 
{
    static char const symbol[]{ "XXX subprogram_statement_part" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(subtype_declaration const &node) const 
{
    static char const symbol[]{ "XXX subtype_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(subtype_indication const &node) const 
{
    static char const symbol[]{ "XXX subtype_indication" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(suffix const &node) const 
{
    static char const symbol[]{ "XXX suffix" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(target const &node) const 
{
    static char const symbol[]{ "XXX target" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(term const &node) const 
{
    static char const symbol[]{ "XXX term" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(timeout_clause const &node) const 
{
    static char const symbol[]{ "XXX timeout_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(type_conversion const &node) const 
{
    static char const symbol[]{ "XXX type_conversion" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(type_declaration const &node) const 
{
    static char const symbol[]{ "XXX type_declaration" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(type_definition const &node) const 
{
    static char const symbol[]{ "XXX type_definition" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(type_mark const &node) const 
{
    static char const symbol[]{ "XXX type_mark" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(unconstrained_array_definition const &node) const 
{
    static char const symbol[]{ "XXX unconstrained_array_definition" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(use_clause const &node) const 
{
    static char const symbol[]{ "XXX use_clause" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(variable_assignment_statement const &node) const 
{
    static char const symbol[]{ "XXX variable_assignment_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(variable_declaration const &node) const 
{
    static char const symbol[]{ "XXX variable_declaration" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(wait_statement const &node) const 
{
    static char const symbol[]{ "XXX wait_statement" }; // FixMe: Review and Implement
    symbol_scope _(*this, symbol);
    //os << node; 
}


void printer::operator()(waveform const &node) const 
{
    static char const symbol[]{ "XXX waveform" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(waveform_element const &node) const 
{
    static char const symbol[]{ "XXX waveform_element" }; // FixMe: Review and Implement
    variant_scope _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


} } } // namespace eda.vhdl93.ast


#pragma GCC diagnostic pop
