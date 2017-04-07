/*
 * ast_printer.cpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast_printer.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <boost/exception/all.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"


namespace eda { namespace vhdl93 { namespace ast {


printer::printer(std::ostream& os, uint16_t indent)
    : os{ os }
    , indent{ indent }
    , verbose_symbol {false}
    , verbose_variant{ false }
    {}

struct printer::scope_printer
{
    scope_printer(std::ostream& os, char const name[], bool verbose, char const name_pfx[] = nullptr)
        : os{ os }
        , name{ name }
        , verbose{ verbose }
    {
        if(verbose) {
            os << prefix;
            if(name_pfx)
                os << name_pfx;
            os << name << "=";
        }
    }

    ~scope_printer()
    {
        if(verbose) {
            os << postfix;
        }
    }

    std::ostream& os;
    const char* const name{ nullptr };
    bool const verbose;
    const char prefix{ '(' };
    const char postfix{ ')' };
};

template<typename T, typename Enable>
struct printer::symbol_scope
: public scope_printer
{
    symbol_scope(printer const& root, char const name[])
    : scope_printer(root.os, name, root.verbose_symbol)
    { }
};

template<typename T>
struct printer::symbol_scope<
    T, typename std::enable_if<x3::traits::is_variant<T>::value>::type
>
: public printer::scope_printer
{
    symbol_scope(printer const& root, char const name[])
    : scope_printer(root.os, name, root.verbose_variant, "v:")
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
    symbol_scope<abstract_literal> _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(access_type_definition const &node) const
{
    static char const symbol[]{ "XXX access_type_definition" };
    symbol_scope<access_type_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(actual_designator const &node) const
{
    static char const symbol[]{ "XXX actual_designator" };
    symbol_scope<actual_designator> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(actual_parameter_part const &node) const
{
    static char const symbol[]{ "XXX actual_parameter_part" };
    symbol_scope<actual_parameter_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(actual_part const &node) const
{
    static char const symbol[]{ "XXX actual_part" };
    symbol_scope<actual_part> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(aggregate const &node) const
{
    static char const symbol[]{ "XXX aggregate" };
    symbol_scope<aggregate> _(*this, symbol);
    //os << node;
}


void printer::operator()(alias_declaration const &node) const
{
    static char const symbol[]{ "XXX alias_declaration" };
    symbol_scope<alias_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(alias_designator const &node) const
{
    static char const symbol[]{ "XXX alias_designator" };
    symbol_scope<alias_designator> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(allocator const &node) const
{
    static char const symbol[]{ "XXX allocator" };
    symbol_scope<allocator> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(architecture_body const &node) const
{
    static char const symbol[]{ "XXX architecture_body" };
    symbol_scope<architecture_body> _(*this, symbol);
    //os << node;
}


void printer::operator()(architecture_declarative_part const &node) const
{
    static char const symbol[]{ "XXX architecture_declarative_part" };
    symbol_scope<architecture_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(architecture_statement_part const &node) const
{
    static char const symbol[]{ "XXX architecture_statement_part" };
    symbol_scope<architecture_statement_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(array_type_definition const &node) const
{
    static char const symbol[]{ "XXX array_type_definition" };
    symbol_scope<array_type_definition> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(assertion const &node) const
{
    static char const symbol[]{ "XXX assertion" };
    symbol_scope<assertion> _(*this, symbol);
    //os << node;
}


void printer::operator()(assertion_statement const &node) const
{
    static char const symbol[]{ "XXX assertion_statement" };
    symbol_scope<assertion_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(association_element const &node) const
{
    static char const symbol[]{ "XXX association_element" };
    symbol_scope<association_element> _(*this, symbol);
    //os << node;
}


void printer::operator()(association_list const &node) const
{
    static char const symbol[]{ "XXX association_list" };
    symbol_scope<association_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(attribute_declaration const &node) const
{
    static char const symbol[]{ "XXX attribute_declaration" };
    symbol_scope<attribute_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(attribute_designator const &node) const
{
    static char const symbol[]{ "XXX attribute_designator" };
    symbol_scope<attribute_designator> _(*this, symbol);
    //os << node;
}


void printer::operator()(attribute_name const &node) const
{
    static char const symbol[]{ "XXX attribute_name" };
    symbol_scope<attribute_name> _(*this, symbol);
    //os << node;
}


void printer::operator()(attribute_specification const &node) const
{
    static char const symbol[]{ "XXX attribute_specification" };
    symbol_scope<attribute_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(base const &node) const
{
    static char const symbol[]{ "XXX base" };
    symbol_scope<base> _(*this, symbol);
    //os << node;
}


void printer::operator()(base_unit_declaration const &node) const
{
    static char const symbol[]{ "XXX base_unit_declaration" };
    symbol_scope<base_unit_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(based_integer const &node) const
{
    static char const symbol[]{ "XXX based_integer" };
    symbol_scope<based_integer> _(*this, symbol);
    //os << node;
}


void printer::operator()(based_literal const &node) const
{
    static char const symbol[]{ "based_literal" };
    symbol_scope<based_literal> _(*this, symbol);

    os << "{b=" << node.base << ", n=" << node.literal << "}";
}


void printer::operator()(basic_character const &node) const
{
    static char const symbol[]{ "XXX basic_character" };
    symbol_scope<basic_character> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(basic_graphic_character const &node) const
{
    static char const symbol[]{ "XXX basic_graphic_character" };
    symbol_scope<basic_graphic_character> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(binding_indication const &node) const
{
    static char const symbol[]{ "XXX binding_indication" };
    symbol_scope<binding_indication> _(*this, symbol);
    //os << node;
}


void printer::operator()(bit_string_literal const &node) const
{
    static char const symbol[]{ "bit_string_literal" };
    symbol_scope<bit_string_literal> _(*this, symbol);

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
    static char const symbol[]{ "XXX block_configuration" };
    symbol_scope<block_configuration> _(*this, symbol);
    //os << node;
}


void printer::operator()(block_declarative_item const &node) const
{
    static char const symbol[]{ "XXX block_declarative_item" };
    symbol_scope<block_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(block_declarative_part const &node) const
{
    static char const symbol[]{ "XXX block_declarative_part" };
    symbol_scope<block_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(block_header const &node) const
{
    static char const symbol[]{ "XXX block_header" };
    symbol_scope<block_header> _(*this, symbol);
    //os << node;
}


void printer::operator()(block_specification const &node) const
{
    static char const symbol[]{ "XXX block_specification" };
    symbol_scope<block_specification> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(block_statement const &node) const
{
    static char const symbol[]{ "XXX block_statement" };
    symbol_scope<block_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(block_statement_part const &node) const
{
    static char const symbol[]{ "XXX block_statement_part" };
    symbol_scope<block_statement_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(case_statement const &node) const
{
    static char const symbol[]{ "XXX case_statement" };
    symbol_scope<case_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(case_statement_alternative const &node) const
{
    static char const symbol[]{ "XXX case_statement_alternative" };
    symbol_scope<case_statement_alternative> _(*this, symbol);
    //os << node;
}


void printer::operator()(character_literal const &node) const
{
    static char const symbol[]{ "character_literal" };
    symbol_scope<character_literal> _(*this, symbol);

    os << node.literal;
}


void printer::operator()(choice const &node) const
{
    static char const symbol[]{ "XXX choice" };
    symbol_scope<choice> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(choices const &node) const
{
    static char const symbol[]{ "XXX choices" };
    symbol_scope<choices> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(component_configuration const &node) const
{
    static char const symbol[]{ "XXX component_configuration" };
    symbol_scope<component_configuration> _(*this, symbol);
    //os << node;
}


void printer::operator()(component_declaration const &node) const
{
    static char const symbol[]{ "XXX component_declaration" };
    symbol_scope<component_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(component_instantiation_statement const &node) const
{
    static char const symbol[]{ "XXX component_instantiation_statement" };
    symbol_scope<component_instantiation_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(component_specification const &node) const
{
    static char const symbol[]{ "XXX component_specification" };
    symbol_scope<component_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(composite_type_definition const &node) const
{
    static char const symbol[]{ "XXX composite_type_definition" };
    symbol_scope<composite_type_definition> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(concurrent_assertion_statement const &node) const
{
    static char const symbol[]{ "XXX concurrent_assertion_statement" };
    symbol_scope<concurrent_assertion_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(concurrent_procedure_call_statement const &node) const
{
    static char const symbol[]{ "XXX concurrent_procedure_call_statement" };
    symbol_scope<concurrent_procedure_call_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(concurrent_signal_assignment_statement const &node) const
{
    static char const symbol[]{ "XXX concurrent_signal_assignment_statement" };
    symbol_scope<concurrent_signal_assignment_statement> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(concurrent_statement const &node) const
{
    static char const symbol[]{ "XXX concurrent_statement" };
    symbol_scope<concurrent_statement> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(condition const &node) const
{
    static char const symbol[]{ "XXX condition" };
    symbol_scope<condition> _(*this, symbol);
    //os << node;
}


void printer::operator()(condition_clause const &node) const
{
    static char const symbol[]{ "XXX condition_clause" };
    symbol_scope<condition_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(conditional_signal_assignment const &node) const
{
    static char const symbol[]{ "XXX conditional_signal_assignment" };
    symbol_scope<conditional_signal_assignment> _(*this, symbol);
    //os << node;
}


void printer::operator()(conditional_waveforms const &node) const
{
    static char const symbol[]{ "XXX conditional_waveforms" };
    symbol_scope<conditional_waveforms> _(*this, symbol);
    //os << node;
}


void printer::operator()(configuration_declaration const &node) const
{
    static char const symbol[]{ "XXX configuration_declaration" };
    symbol_scope<configuration_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(configuration_declarative_item const &node) const
{
    static char const symbol[]{ "XXX configuration_declarative_item" };
    symbol_scope<configuration_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(configuration_declarative_part const &node) const
{
    static char const symbol[]{ "XXX configuration_declarative_part" };
    symbol_scope<configuration_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(configuration_item const &node) const
{
    static char const symbol[]{ "XXX configuration_item" };
    symbol_scope<configuration_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(configuration_specification const &node) const
{
    static char const symbol[]{ "XXX configuration_specification" };
    symbol_scope<configuration_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(constant_declaration const &node) const
{
    static char const symbol[]{ "XXX constant_declaration" };
    symbol_scope<constant_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(constrained_array_definition const &node) const
{
    static char const symbol[]{ "XXX constrained_array_definition" };
    symbol_scope<constrained_array_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(constraint const &node) const
{
    static char const symbol[]{ "XXX constraint" };
    symbol_scope<constraint> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(context_clause const &node) const
{
    static char const symbol[]{ "XXX context_clause" };
    symbol_scope<context_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(context_item const &node) const
{
    static char const symbol[]{ "XXX context_item" };
    symbol_scope<context_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(decimal_literal const &node) const
{
    static char const symbol[]{ "decimal_literal" };
    symbol_scope<decimal_literal> _(*this, symbol);

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
    static char const symbol[]{ "XXX declaration" };
    symbol_scope<declaration> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(delay_mechanism const &node) const
{
    static char const symbol[]{ "XXX delay_mechanism" };
    symbol_scope<delay_mechanism> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(design_file const &node) const
{
    static char const symbol[]{ "XXX design_file" };
    symbol_scope<design_file> _(*this, symbol);
    //os << node;
}


void printer::operator()(design_unit const &node) const
{
    static char const symbol[]{ "XXX design_unit" };
    symbol_scope<design_unit> _(*this, symbol);
    //os << node;
}


void printer::operator()(designator const &node) const
{
    static char const symbol[]{ "XXX designator" };
    symbol_scope<designator> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(direction const &node) const
{
    static char const symbol[]{ "direction" };
    symbol_scope<direction> _(*this, symbol);

    using dir = direction::direction_type;

    switch(node.direction) {
    case dir::to:       os << "to";     break;
    case dir::downto:   os << "downto"; break;
    default:            os << "INVALID";
    }
}


void printer::operator()(disconnection_specification const &node) const
{
    static char const symbol[]{ "XXX disconnection_specification" };
    symbol_scope<disconnection_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(discrete_range const &node) const
{
    static char const symbol[]{ "XXX discrete_range" };
    symbol_scope<discrete_range> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(element_association const &node) const
{
    static char const symbol[]{ "XXX element_association" };
    symbol_scope<element_association> _(*this, symbol);
    //os << node;
}


void printer::operator()(element_declaration const &node) const
{
    static char const symbol[]{ "XXX element_declaration" };
    symbol_scope<element_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(element_subtype_definition const &node) const
{
    static char const symbol[]{ "XXX element_subtype_definition" };
    symbol_scope<element_subtype_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_aspect const &node) const
{
    static char const symbol[]{ "XXX entity_aspect" };
    symbol_scope<entity_aspect> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_class const &node) const
{
    static char const symbol[]{ "XXX entity_class" };
    symbol_scope<entity_class> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_class_entry const &node) const
{
    static char const symbol[]{ "XXX entity_class_entry" };
    symbol_scope<entity_class_entry> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_class_entry_list const &node) const
{
    static char const symbol[]{ "XXX entity_class_entry_list" };
    symbol_scope<entity_class_entry_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_declaration const &node) const
{
    static char const symbol[]{ "XXX entity_declaration" };
    symbol_scope<entity_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_declarative_item const &node) const
{
    static char const symbol[]{ "XXX entity_declarative_item" };
    symbol_scope<entity_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_declarative_part const &node) const
{
    static char const symbol[]{ "XXX entity_declarative_part" };
    symbol_scope<entity_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_designator const &node) const
{
    static char const symbol[]{ "XXX entity_designator" };
    symbol_scope<entity_designator> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_header const &node) const
{
    static char const symbol[]{ "XXX entity_header" };
    symbol_scope<entity_header> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_name_list const &node) const
{
    static char const symbol[]{ "XXX entity_name_list" };
    symbol_scope<entity_name_list> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_specification const &node) const
{
    static char const symbol[]{ "XXX entity_specification" };
    symbol_scope<entity_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_statement const &node) const
{
    static char const symbol[]{ "XXX entity_statement" };
    symbol_scope<entity_statement> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(entity_statement_part const &node) const
{
    static char const symbol[]{ "XXX entity_statement_part" };
    symbol_scope<entity_statement_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(entity_tag const &node) const
{
    static char const symbol[]{ "XXX entity_tag" };
    symbol_scope<entity_tag> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(enumeration_literal const &node) const
{
    static char const symbol[]{ "enumeration_literal" };
    symbol_scope<enumeration_literal> _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(enumeration_type_definition const &node) const
{
    static char const symbol[]{ "enumeration_type_definition" };
    symbol_scope<enumeration_type_definition> _(*this, symbol);

    for(auto const& enumeration_literal : node.list) {
        (*this)(enumeration_literal);
    }
}


void printer::operator()(exit_statement const &node) const
{
    static char const symbol[]{ "XXX exit_statement" };
    symbol_scope<exit_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(exponent const &node) const
{
    static char const symbol[]{ "XXX exponent" };
    symbol_scope<exponent> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(expression const &node) const
{
    static char const symbol[]{ "XXX expression" };
    symbol_scope<expression> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(factor const &node) const
{
    static char const symbol[]{ "XXX factor" };
    symbol_scope<factor> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(file_declaration const &node) const
{
    static char const symbol[]{ "XXX file_declaration" };
    symbol_scope<file_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(file_logical_name const &node) const
{
    static char const symbol[]{ "XXX file_logical_name" };
    symbol_scope<file_logical_name> _(*this, symbol);
    //os << node;
}


void printer::operator()(file_open_information const &node) const
{
    static char const symbol[]{ "XXX file_open_information" };
    symbol_scope<file_open_information> _(*this, symbol);
    //os << node;
}


void printer::operator()(file_type_definition const &node) const
{
    static char const symbol[]{ "XXX file_type_definition" };
    symbol_scope<file_type_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(formal_designator const &node) const
{
    static char const symbol[]{ "XXX formal_designator" };
    symbol_scope<formal_designator> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(formal_parameter_list const &node) const
{
    static char const symbol[]{ "XXX formal_parameter_list" };
    symbol_scope<formal_parameter_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(formal_part const &node) const
{
    static char const symbol[]{ "XXX formal_part" };
    symbol_scope<formal_part> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(full_type_declaration const &node) const
{
    static char const symbol[]{ "XXX full_type_declaration" };
    symbol_scope<full_type_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(function_call const &node) const
{
    static char const symbol[]{ "XXX function_call" };
    symbol_scope<function_call> _(*this, symbol);
    //os << node;
}


void printer::operator()(generate_statement const &node) const
{
    static char const symbol[]{ "XXX generate_statement" };
    symbol_scope<generate_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(generation_scheme const &node) const
{
    static char const symbol[]{ "XXX generation_scheme" };
    symbol_scope<generation_scheme> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(generic_clause const &node) const
{
    static char const symbol[]{ "XXX generic_clause" };
    symbol_scope<generic_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(generic_list const &node) const
{
    static char const symbol[]{ "XXX generic_list" };
    symbol_scope<generic_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(generic_map_aspect const &node) const
{
    static char const symbol[]{ "XXX generic_map_aspect" };
    symbol_scope<generic_map_aspect> _(*this, symbol);
    //os << node;
}


void printer::operator()(graphic_character const &node) const
{
    static char const symbol[]{ "XXX graphic_character" };
    symbol_scope<graphic_character> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(group_constituent const &node) const
{
    static char const symbol[]{ "XXX group_constituent" };
    symbol_scope<group_constituent> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(group_constituent_list const &node) const
{
    static char const symbol[]{ "XXX group_constituent_list" };
    symbol_scope<group_constituent_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(group_declaration const &node) const
{
    static char const symbol[]{ "XXX group_declaration" };
    symbol_scope<group_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(group_template_declaration const &node) const
{
    static char const symbol[]{ "XXX group_template_declaration" };
    symbol_scope<group_template_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(guarded_signal_specification const &node) const
{
    static char const symbol[]{ "XXX guarded_signal_specification" };
    symbol_scope<guarded_signal_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(identifier const &node) const
{
    static char const symbol[]{ "identifier" };
    symbol_scope<identifier> _(*this, symbol);

    /* Note, even if identifier following the BNF is variant, it's treated as
     * as common indentifier for {basic, extended}_identifier */
    os << node.name;
}


void printer::operator()(identifier_list const &node) const
{
    static char const symbol[]{ "identifier_list" };
    symbol_scope<identifier_list> _(*this, symbol);

    for(auto const& identifier : node.list) {
        (*this)(identifier);
    }
}


void printer::operator()(if_statement const &node) const
{
    static char const symbol[]{ "XXX if_statement" };
    symbol_scope<if_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(incomplete_type_declaration const &node) const
{
    static char const symbol[]{ "XXX incomplete_type_declaration" };
    symbol_scope<incomplete_type_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(index_constraint const &node) const
{
    static char const symbol[]{ "XXX index_constraint" };
    symbol_scope<index_constraint> _(*this, symbol);
    //os << node;
}


void printer::operator()(index_specification const &node) const
{
    static char const symbol[]{ "XXX index_specification" };
    symbol_scope<index_specification> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(index_subtype_definition const &node) const
{
    static char const symbol[]{ "XXX index_subtype_definition" };
    symbol_scope<index_subtype_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(indexed_name const &node) const
{
    static char const symbol[]{ "XXX indexed_name" };
    symbol_scope<indexed_name> _(*this, symbol);
    //os << node;
}


void printer::operator()(instantiated_unit const &node) const
{
    static char const symbol[]{ "XXX instantiated_unit" };
    symbol_scope<instantiated_unit> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(instantiation_list const &node) const
{
    static char const symbol[]{ "XXX instantiation_list" };
    symbol_scope<instantiation_list> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(integer const &node) const
{
    static char const symbol[]{ "XXX integer" };
    symbol_scope<integer> _(*this, symbol);
    //os << node;
}


void printer::operator()(integer_type_definition const &node) const
{
    static char const symbol[]{ "XXX integer_type_definition" };
    symbol_scope<integer_type_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(interface_constant_declaration const &node) const
{
    static char const symbol[]{ "XXX interface_constant_declaration" };
    symbol_scope<interface_constant_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(interface_declaration const &node) const
{
    static char const symbol[]{ "XXX interface_declaration" };
    symbol_scope<interface_declaration> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(interface_element const &node) const
{
    static char const symbol[]{ "XXX interface_element" };
    symbol_scope<interface_element> _(*this, symbol);
    //os << node;
}


void printer::operator()(interface_file_declaration const &node) const
{
    static char const symbol[]{ "XXX interface_file_declaration" };
    symbol_scope<interface_file_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(interface_list const &node) const
{
    static char const symbol[]{ "XXX interface_list" };
    symbol_scope<interface_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(interface_signal_declaration const &node) const
{
    static char const symbol[]{ "XXX interface_signal_declaration" };
    symbol_scope<interface_signal_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(interface_variable_declaration const &node) const
{
    static char const symbol[]{ "XXX interface_variable_declaration" };
    symbol_scope<interface_variable_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(iteration_scheme const &node) const
{
    static char const symbol[]{ "XXX iteration_scheme" };
    symbol_scope<iteration_scheme> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(label const &node) const
{
    static char const symbol[]{ "XXX label" };
    symbol_scope<label> _(*this, symbol);
    //os << node;
}


void printer::operator()(library_clause const &node) const
{
    static char const symbol[]{ "XXX library_clause" };
    symbol_scope<library_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(library_unit const &node) const
{
    static char const symbol[]{ "XXX library_unit" };
    symbol_scope<library_unit> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(literal const &node) const
{
    static char const symbol[]{ "literal" };
    symbol_scope<literal> _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(logical_name const &node) const
{
    static char const symbol[]{ "XXX logical_name" };
    symbol_scope<logical_name> _(*this, symbol);
    //os << node;
}


void printer::operator()(logical_name_list const &node) const
{
    static char const symbol[]{ "XXX logical_name_list" };
    symbol_scope<logical_name_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(loop_statement const &node) const
{
    static char const symbol[]{ "XXX loop_statement" };
    symbol_scope<loop_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(mode const &node) const
{
    static char const symbol[]{ "XXX mode" };
    symbol_scope<mode> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(name const &node) const
{
    static char const symbol[]{ "name" };
    symbol_scope<name> _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(next_statement const &node) const
{
    static char const symbol[]{ "XXX next_statement" };
    symbol_scope<next_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(null_statement const &node) const
{
    static char const symbol[]{ "XXX null_statement" };
    symbol_scope<null_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(numeric_literal const &node) const
{
    static char const symbol[]{ "numeric_literal" };
    symbol_scope<numeric_literal> _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(object_declaration const &node) const
{
    static char const symbol[]{ "XXX object_declaration" };
    symbol_scope<object_declaration> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(operator_symbol const &node) const
{
    static char const symbol[]{ "XXX operator_symbol" };
    symbol_scope<operator_symbol> _(*this, symbol);
    //os << node;
}


void printer::operator()(options const &node) const
{
    static char const symbol[]{ "XXX options" };
    symbol_scope<options> _(*this, symbol);
    //os << node;
}


void printer::operator()(package_body const &node) const
{
    static char const symbol[]{ "XXX package_body" };
    symbol_scope<package_body> _(*this, symbol);
    //os << node;
}


void printer::operator()(package_body_declarative_item const &node) const
{
    static char const symbol[]{ "XXX package_body_declarative_item" };
    symbol_scope<package_body_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(package_body_declarative_part const &node) const
{
    static char const symbol[]{ "XXX package_body_declarative_part" };
    symbol_scope<package_body_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(package_declaration const &node) const
{
    static char const symbol[]{ "XXX package_declaration" };
    symbol_scope<package_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(package_declarative_item const &node) const
{
    static char const symbol[]{ "XXX package_declarative_item" };
    symbol_scope<package_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(package_declarative_part const &node) const
{
    static char const symbol[]{ "XXX package_declarative_part" };
    symbol_scope<package_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(parameter_specification const &node) const
{
    static char const symbol[]{ "XXX parameter_specification" };
    symbol_scope<parameter_specification> _(*this, symbol);
    //os << node;
}


void printer::operator()(physical_literal const &node) const
{
    static char const symbol[]{ "physical_literal" };
    symbol_scope<physical_literal> _(*this, symbol);

    os << "{l=";
    (*this)(node.literal);
    os << ", u=" << node.unit_name;
    os << "}";
}


void printer::operator()(physical_type_definition const &node) const
{
    static char const symbol[]{ "XXX physical_type_definition" };
    symbol_scope<physical_type_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(port_clause const &node) const
{
    static char const symbol[]{ "XXX port_clause" };
    symbol_scope<port_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(port_list const &node) const
{
    static char const symbol[]{ "XXX port_list" };
    symbol_scope<port_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(port_map_aspect const &node) const
{
    static char const symbol[]{ "XXX port_map_aspect" };
    symbol_scope<port_map_aspect> _(*this, symbol);
    //os << node;
}


void printer::operator()(prefix const &node) const
{
    static char const symbol[]{ "XXX prefix" };
    symbol_scope<prefix> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(primary const &node) const
{
    static char const symbol[]{ "XXX primary" };
    symbol_scope<primary> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(primary_unit const &node) const
{
    static char const symbol[]{ "XXX primary_unit" };
    symbol_scope<primary_unit> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(procedure_call const &node) const
{
    static char const symbol[]{ "XXX procedure_call" };
    symbol_scope<procedure_call> _(*this, symbol);
    //os << node;
}


void printer::operator()(procedure_call_statement const &node) const
{
    static char const symbol[]{ "XXX procedure_call_statement" };
    symbol_scope<procedure_call_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(process_declarative_item const &node) const
{
    static char const symbol[]{ "XXX process_declarative_item" };
    symbol_scope<process_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(process_declarative_part const &node) const
{
    static char const symbol[]{ "XXX process_declarative_part" };
    symbol_scope<process_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(process_statement const &node) const
{
    static char const symbol[]{ "XXX process_statement" };
    symbol_scope<process_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(process_statement_part const &node) const
{
    static char const symbol[]{ "XXX process_statement_part" };
    symbol_scope<process_statement_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(qualified_expression const &node) const
{
    static char const symbol[]{ "XXX qualified_expression" };
    symbol_scope<qualified_expression> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(range const &node) const
{
    static char const symbol[]{ "XXX range" };
    symbol_scope<range> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(range_constraint const &node) const
{
    static char const symbol[]{ "XXX range_constraint" };
    symbol_scope<range_constraint> _(*this, symbol);
    //os << node;
}


void printer::operator()(record_type_definition const &node) const
{
    static char const symbol[]{ "XXX record_type_definition" };
    symbol_scope<record_type_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(relation const &node) const
{
    static char const symbol[]{ "XXX relation" };
    symbol_scope<relation> _(*this, symbol);
    //os << node;
}


void printer::operator()(report_statement const &node) const
{
    static char const symbol[]{ "XXX report_statement" };
    symbol_scope<report_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(return_statement const &node) const
{
    static char const symbol[]{ "XXX return_statement" };
    symbol_scope<return_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(scalar_type_definition const &node) const
{
    static char const symbol[]{ "XXX scalar_type_definition" };
    symbol_scope<scalar_type_definition> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(secondary_unit const &node) const
{
    static char const symbol[]{ "XXX secondary_unit" };
    symbol_scope<secondary_unit> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(secondary_unit_declaration const &node) const
{
    static char const symbol[]{ "XXX secondary_unit_declaration" };
    symbol_scope<secondary_unit_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(selected_name const &node) const
{
    static char const symbol[]{ "XXX selected_name" };
    symbol_scope<selected_name> _(*this, symbol);
    //os << node;
}


void printer::operator()(selected_signal_assignment const &node) const
{
    static char const symbol[]{ "XXX selected_signal_assignment" };
    symbol_scope<selected_signal_assignment> _(*this, symbol);
    //os << node;
}


void printer::operator()(selected_waveforms const &node) const
{
    static char const symbol[]{ "XXX selected_waveforms" };
    symbol_scope<selected_waveforms> _(*this, symbol);
    //os << node;
}


void printer::operator()(sensitivity_clause const &node) const
{
    static char const symbol[]{ "XXX sensitivity_clause" };
    symbol_scope<sensitivity_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(sensitivity_list const &node) const
{
    static char const symbol[]{ "XXX sensitivity_list" };
    symbol_scope<sensitivity_list> _(*this, symbol);
    //os << node;
}


void printer::operator()(sequence_of_statements const &node) const
{
    static char const symbol[]{ "XXX sequence_of_statements" };
    symbol_scope<sequence_of_statements> _(*this, symbol);
    //os << node;
}


void printer::operator()(sequential_statement const &node) const
{
    static char const symbol[]{ "XXX sequential_statement" };
    symbol_scope<sequential_statement> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(shift_expression const &node) const
{
    static char const symbol[]{ "XXX shift_expression" };
    symbol_scope<shift_expression> _(*this, symbol);
    //os << node;
}


void printer::operator()(sign const &node) const
{
    static char const symbol[]{ "XXX sign" };
    symbol_scope<sign> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(signal_assignment_statement const &node) const
{
    static char const symbol[]{ "XXX signal_assignment_statement" };
    symbol_scope<signal_assignment_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(signal_declaration const &node) const
{
    static char const symbol[]{ "XXX signal_declaration" };
    symbol_scope<signal_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(signal_kind const &node) const
{
    static char const symbol[]{ "XXX signal_kind" };
    symbol_scope<signal_kind> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(signal_list const &node) const
{
    static char const symbol[]{ "XXX signal_list" };
    symbol_scope<signal_list> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(signature const &node) const
{
    static char const symbol[]{ "XXX signature" };
    symbol_scope<signature> _(*this, symbol);
    //os << node;
}


void printer::operator()(simple_expression const &node) const
{
    static char const symbol[]{ "XXX simple_expression" };
    symbol_scope<simple_expression> _(*this, symbol);
    //os << node;
}


void printer::operator()(simple_name const &node) const
{
    static char const symbol[]{ "simple_name" };
    symbol_scope<simple_name> _(*this, symbol);

    os << node.name;
}


void printer::operator()(slice_name const &node) const
{
    static char const symbol[]{ "XXX slice_name" };
    symbol_scope<slice_name> _(*this, symbol);
    //os << node;
}


void printer::operator()(string_literal const &node) const
{
    static char const symbol[]{ "string_literal" };
    symbol_scope<string_literal> _(*this, symbol);

    os << node;
}


void printer::operator()(subprogram_body const &node) const
{
    static char const symbol[]{ "XXX subprogram_body" };
    symbol_scope<subprogram_body> _(*this, symbol);
    //os << node;
}


void printer::operator()(subprogram_declaration const &node) const
{
    static char const symbol[]{ "XXX subprogram_declaration" };
    symbol_scope<subprogram_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(subprogram_declarative_item const &node) const
{
    static char const symbol[]{ "XXX subprogram_declarative_item" };
    symbol_scope<subprogram_declarative_item> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(subprogram_declarative_part const &node) const
{
    static char const symbol[]{ "XXX subprogram_declarative_part" };
    symbol_scope<subprogram_declarative_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(subprogram_kind const &node) const
{
    static char const symbol[]{ "XXX subprogram_kind" };
    symbol_scope<subprogram_kind> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(subprogram_specification const &node) const
{
    static char const symbol[]{ "XXX subprogram_specification" };
    symbol_scope<subprogram_specification> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(subprogram_statement_part const &node) const
{
    static char const symbol[]{ "XXX subprogram_statement_part" };
    symbol_scope<subprogram_statement_part> _(*this, symbol);
    //os << node;
}


void printer::operator()(subtype_declaration const &node) const
{
    static char const symbol[]{ "XXX subtype_declaration" };
    symbol_scope<subtype_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(subtype_indication const &node) const
{
    static char const symbol[]{ "XXX subtype_indication" };
    symbol_scope<subtype_indication> _(*this, symbol);
    //os << node;
}


void printer::operator()(suffix const &node) const
{
    static char const symbol[]{ "suffix" };
    symbol_scope<suffix> _(*this, symbol);
    boost::apply_visitor(*this, node);
}


void printer::operator()(target const &node) const
{
    static char const symbol[]{ "XXX target" };
    symbol_scope<target> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(term const &node) const
{
    static char const symbol[]{ "XXX term" };
    symbol_scope<term> _(*this, symbol);
    //os << node;
}


void printer::operator()(timeout_clause const &node) const
{
    static char const symbol[]{ "XXX timeout_clause" };
    symbol_scope<timeout_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(type_conversion const &node) const
{
    static char const symbol[]{ "XXX type_conversion" };
    symbol_scope<type_conversion> _(*this, symbol);
    //os << node;
}


void printer::operator()(type_declaration const &node) const
{
    static char const symbol[]{ "XXX type_declaration" };
    symbol_scope<type_declaration> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(type_definition const &node) const
{
    static char const symbol[]{ "XXX type_definition" };
    symbol_scope<type_definition> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(unconstrained_array_definition const &node) const
{
    static char const symbol[]{ "XXX unconstrained_array_definition" };
    symbol_scope<unconstrained_array_definition> _(*this, symbol);
    //os << node;
}


void printer::operator()(use_clause const &node) const
{
    static char const symbol[]{ "XXX use_clause" };
    symbol_scope<use_clause> _(*this, symbol);
    //os << node;
}


void printer::operator()(variable_assignment_statement const &node) const
{
    static char const symbol[]{ "XXX variable_assignment_statement" };
    symbol_scope<variable_assignment_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(variable_declaration const &node) const
{
    static char const symbol[]{ "XXX variable_declaration" };
    symbol_scope<variable_declaration> _(*this, symbol);
    //os << node;
}


void printer::operator()(wait_statement const &node) const
{
    static char const symbol[]{ "XXX wait_statement" };
    symbol_scope<wait_statement> _(*this, symbol);
    //os << node;
}


void printer::operator()(waveform const &node) const
{
    static char const symbol[]{ "XXX waveform" };
    symbol_scope<waveform> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}


void printer::operator()(waveform_element const &node) const
{
    static char const symbol[]{ "XXX waveform_element" };
    symbol_scope<waveform_element> _(*this, symbol);
    //boost::apply_visitor(*this, node);
}

/*
 * Non AST members, used e.g. for unit tests (namely ast::integer)
 */
void printer::operator()(std::string const &node) const
{
    static char const symbol[]{ "std::string" };
    symbol_scope<std::string> _(*this, symbol);

    os << node;
}


void printer::operator()(keyword_token token) const
{
    static char const symbol[]{ "keyword" };
    symbol_scope<keyword_token> _(*this, symbol);

    os << token;
}


void printer::operator()(unary_expression const& node) const
{
    static char const symbol[]{ "unary_expression" };
    symbol_scope<unary_expression> _(*this, symbol);

    os << "XXX";
}


void printer::operator()(binary_expression const& node) const
{
    static char const symbol[]{ "binary_expression" };
    symbol_scope<binary_expression> _(*this, symbol);

    os << "XXX";
}




} } } // namespace eda.vhdl93.ast


#pragma GCC diagnostic pop
