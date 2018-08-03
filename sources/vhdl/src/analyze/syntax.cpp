/*
 * syntax.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/analyze/syntax.hpp>
#include <eda/vhdl/analyze/check/label_match.hpp>
#include <eda/vhdl/ast.hpp>

#include <eda/support/boost/locale.hpp>

#include <eda/util/pretty_typename.hpp>

#include <eda/compiler/warnings_off.hpp>  // temporary -Wno-unused


namespace eda { namespace vhdl { namespace analyze {

namespace tag {
struct enabled { };
struct disabled { };
}
using verbose = tag::enabled;


/**
 * Debug Indent printer
 */
template<typename T>
struct syntax::indent_logging<T, typename std::enable_if_t<std::is_same_v<T, tag::disabled>>>
{
    indent_logging(syntax const&, const char* const)
    {  }
};

template<typename T>
struct syntax::indent_logging<T, typename std::enable_if_t<std::is_same_v<T, tag::enabled>>>
{
    util::indent_ostream&                           os;
    const char* const                               node_name;

    indent_logging(syntax const& s, const char* const node_name_)
    : os{ s.os }
    , node_name{ node_name_ }
    {
        os << util::increase_indent
           << "<" << node_name << ">\n";
    }

    ~indent_logging()
    {
        os << "</" << node_name << ">\n"
           << util::decrease_indent;
    }
};


} } } // namespace eda.vhdl.analyze


namespace eda { namespace vhdl { namespace analyze {


using boost::locale::translate;
using boost::locale::format;


template<typename ...Types>
syntax::result_type syntax::operator()(ast::variant<Types...> const& node) const {
    os << "INFO: dispatch " << util::pretty_typename<decltype(node)>{} << "\n";
    return boost::apply_visitor(*this, node);
}


template<typename T>
syntax::result_type syntax::operator()(std::vector<T> const& node) const {
    os << "INFO: iterate over vector<" << util::pretty_typename<T>{} << ", N = " << node.size() << ">\n";
    return std::all_of(node.begin(), node.end(),
                      [&](T const& x){ return (*this)(x); } );
}


//syntax::result_type syntax::operator()(ast::abstract_literal const& node) const;
//syntax::result_type syntax::operator()(ast::access_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::actual_designator const& node) const;
//syntax::result_type syntax::operator()(ast::actual_part const& node) const;
//syntax::result_type syntax::operator()(ast::aggregate const& node) const;
//syntax::result_type syntax::operator()(ast::alias_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::alias_designator const& node) const;
//syntax::result_type syntax::operator()(ast::allocator const& node) const;
//syntax::result_type syntax::operator()(ast::architecture_body const& node) const;
//syntax::result_type syntax::operator()(ast::architecture_statement_part const& node) const;
//syntax::result_type syntax::operator()(ast::array_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::assertion const& node) const;
//syntax::result_type syntax::operator()(ast::assertion_statement const& node) const;
//syntax::result_type syntax::operator()(ast::association_element const& node) const;
//syntax::result_type syntax::operator()(ast::association_list const& node) const;
//syntax::result_type syntax::operator()(ast::attribute_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::attribute_name const& node) const;
//syntax::result_type syntax::operator()(ast::attribute_specification const& node) const;
//syntax::result_type syntax::operator()(ast::based_literal const& node) const;
//syntax::result_type syntax::operator()(ast::binding_indication const& node) const;
//syntax::result_type syntax::operator()(ast::bit_string_literal const& node) const;
//syntax::result_type syntax::operator()(ast::block_configuration const& node) const;
//syntax::result_type syntax::operator()(ast::block_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::block_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::block_header const& node) const;
//syntax::result_type syntax::operator()(ast::block_specification const& node) const;

syntax::result_type syntax::operator()(ast::block_statement const& node) const
{
    static char const node_name[]{ "block_statement" };
    indent_logging<verbose> _(*this, node_name);

    if(!check_label_match(node)) {
    	error_handler(node, label_match::make_error_description(node));
    	++context.error_count;
    	return false;
    }

    // XXX continue to dispatch members

    return true;
}

//syntax::result_type syntax::operator()(ast::block_statement_part const& node) const;
//syntax::result_type syntax::operator()(ast::case_statement const& node) const;
//syntax::result_type syntax::operator()(ast::case_statement_alternative const& node) const;
//syntax::result_type syntax::operator()(ast::character_literal const& node) const;
//syntax::result_type syntax::operator()(ast::choice const& node) const;
//syntax::result_type syntax::operator()(ast::choices const& node) const;
//syntax::result_type syntax::operator()(ast::component_configuration const& node) const;
//syntax::result_type syntax::operator()(ast::component_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::component_instantiation_statement const& node) const;
//syntax::result_type syntax::operator()(ast::component_specification const& node) const;
//syntax::result_type syntax::operator()(ast::composite_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::concurrent_assertion_statement const& node) const;
//syntax::result_type syntax::operator()(ast::concurrent_procedure_call_statement const& node) const;
//syntax::result_type syntax::operator()(ast::concurrent_signal_assignment_statement const& node) const;
//syntax::result_type syntax::operator()(ast::concurrent_statement const& node) const;
//syntax::result_type syntax::operator()(ast::condition_clause const& node) const;
//syntax::result_type syntax::operator()(ast::conditional_signal_assignment const& node) const;
//syntax::result_type syntax::operator()(ast::conditional_waveforms const& node) const;
//syntax::result_type syntax::operator()(ast::configuration_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::configuration_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::configuration_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::configuration_item const& node) const;
//syntax::result_type syntax::operator()(ast::configuration_specification const& node) const;
//syntax::result_type syntax::operator()(ast::constant_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::constrained_array_definition const& node) const;
//syntax::result_type syntax::operator()(ast::constraint const& node) const;
//syntax::result_type syntax::operator()(ast::context_clause const& node) const
//syntax::result_type syntax::operator()(ast::context_item const& node) const:
//syntax::result_type syntax::operator()(ast::decimal_literal const& node) const;
//syntax::result_type syntax::operator()(ast::delay_mechanism const& node) const;


syntax::result_type syntax::operator()(ast::design_file const& node) const
{
    static char const node_name[]{ "design_file" };
    indent_logging<verbose> _(*this, node_name);

    for(auto const& design_unit : node) {

        bool const ok = (*this)(design_unit);

        if(!ok) {
            os << "check failed in design_file\n";
            return false;
        }
    }

    return true;
}


syntax::result_type syntax::operator()(ast::design_unit const& node) const
{
    static char const node_name[]{ "design_unit" };
    indent_logging<verbose> _(*this, node_name);

    error_handler(node, "testing the tagging and error handler");

    if(!(*this)(node.context_clause)) {
        os << "check failed in design_unit.context_clause\n";
        return false;
    }

    if(!(*this)(node.library_unit)) {
        os << "check failed in design_unit.library_unit\n";
        return false;
    }

    return true;
}


//syntax::result_type syntax::operator()(ast::designator const& node) const;
//syntax::result_type syntax::operator()(ast::disconnection_specification const& node) const;
//syntax::result_type syntax::operator()(ast::discrete_range const& node) const;
//syntax::result_type syntax::operator()(ast::element_association const& node) const;
//syntax::result_type syntax::operator()(ast::element_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::entity_aspect const& node) const;
//syntax::result_type syntax::operator()(ast::entity_class_entry_list const& node) const;
//syntax::result_type syntax::operator()(ast::entity_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::entity_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::entity_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::entity_designator const& node) const;
//syntax::result_type syntax::operator()(ast::entity_header const& node) const;
//syntax::result_type syntax::operator()(ast::entity_name_list const& node) const;
//syntax::result_type syntax::operator()(ast::entity_specification const& node) const;
//syntax::result_type syntax::operator()(ast::entity_statement const& node) const;
//syntax::result_type syntax::operator()(ast::entity_statement_part const& node) const;
//syntax::result_type syntax::operator()(ast::entity_tag const& node) const;
//syntax::result_type syntax::operator()(ast::enumeration_literal const& node) const;
//syntax::result_type syntax::operator()(ast::enumeration_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::exit_statement const& node) const;
//syntax::result_type syntax::operator()(ast::expression const& node) const;
//syntax::result_type syntax::operator()(ast::factor_binary_operation const& node) const;
//syntax::result_type syntax::operator()(ast::factor_unary_operation const& node) const;
//syntax::result_type syntax::operator()(ast::factor const& node) const;
//syntax::result_type syntax::operator()(ast::file_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::file_open_information const& node) const;
//syntax::result_type syntax::operator()(ast::formal_part const& node) const;
//syntax::result_type syntax::operator()(ast::function_call const& node) const;
//syntax::result_type syntax::operator()(ast::generate_statement const& node) const;
//syntax::result_type syntax::operator()(ast::generation_scheme const& node) const;
//syntax::result_type syntax::operator()(ast::generic_clause const& node) const;
//syntax::result_type syntax::operator()(ast::generic_map_aspect const& node) const;
//syntax::result_type syntax::operator()(ast::group_constituent const& node) const;
//syntax::result_type syntax::operator()(ast::group_constituent_list const& node) const;
//syntax::result_type syntax::operator()(ast::group_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::group_template_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::guarded_signal_specification const& node) const;
//syntax::result_type syntax::operator()(ast::identifier const& node) const;
//syntax::result_type syntax::operator()(ast::identifier_list const& node) const;
//syntax::result_type syntax::operator()(ast::if_statement const& node) const;
//syntax::result_type syntax::operator()(ast::index_constraint const& node) const;
//syntax::result_type syntax::operator()(ast::index_specification const& node) const;
//syntax::result_type syntax::operator()(ast::index_subtype_definition const& node) const;
//syntax::result_type syntax::operator()(ast::indexed_name const& node) const;
//syntax::result_type syntax::operator()(ast::instantiated_unit const& node) const;
//syntax::result_type syntax::operator()(ast::instantiation_list const& node) const;
//syntax::result_type syntax::operator()(ast::interface_constant_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::interface_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::interface_file_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::interface_list const& node) const;
//syntax::result_type syntax::operator()(ast::interface_signal_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::interface_variable_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::iteration_scheme const& node) const;


syntax::result_type syntax::operator()(ast::library_clause const& node) const
{
    static char const node_name[]{ "library_clause" };
    indent_logging<verbose> _(*this, node_name);

    return true;
}


//syntax::result_type syntax::operator()(ast::library_unit const& node) const;
//syntax::result_type syntax::operator()(ast::literal const& node) const;
//syntax::result_type syntax::operator()(ast::loop_statement const& node) const;
//syntax::result_type syntax::operator()(ast::name const& node) const;
//syntax::result_type syntax::operator()(ast::next_statement const& node) const;
//syntax::result_type syntax::operator()(ast::null_statement const& node) const;
//syntax::result_type syntax::operator()(ast::numeric_literal const& node) const;
//syntax::result_type syntax::operator()(ast::options const& node) const;
//syntax::result_type syntax::operator()(ast::package_body const& node) const;
//syntax::result_type syntax::operator()(ast::package_body_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::package_body_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::package_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::package_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::package_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::parameter_specification const& node) const;
//syntax::result_type syntax::operator()(ast::physical_literal const& node) const;
//syntax::result_type syntax::operator()(ast::physical_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::port_clause const& node) const;
//syntax::result_type syntax::operator()(ast::port_map_aspect const& node) const;
//syntax::result_type syntax::operator()(ast::prefix const& node) const;
//syntax::result_type syntax::operator()(ast::primary const& node) const;
//syntax::result_type syntax::operator()(ast::primary_unit const& node) const;
//syntax::result_type syntax::operator()(ast::procedure_call const& node) const;
//syntax::result_type syntax::operator()(ast::procedure_call_statement const& node) const;
//syntax::result_type syntax::operator()(ast::process_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::process_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::process_statement const& node) const;
//syntax::result_type syntax::operator()(ast::qualified_expression const& node) const;
//syntax::result_type syntax::operator()(ast::range const& node) const;
//syntax::result_type syntax::operator()(ast::record_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::relation const& node) const;
//syntax::result_type syntax::operator()(ast::report_statement const& node) const;
//syntax::result_type syntax::operator()(ast::return_statement const& node) const;
//syntax::result_type syntax::operator()(ast::scalar_type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::secondary_unit const& node) const;
//syntax::result_type syntax::operator()(ast::secondary_unit_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::selected_name const& node) const;
//syntax::result_type syntax::operator()(ast::selected_signal_assignment const& node) const;
//syntax::result_type syntax::operator()(ast::selected_waveforms const& node) const;
//syntax::result_type syntax::operator()(ast::sensitivity_clause const& node) const;
//syntax::result_type syntax::operator()(ast::sensitivity_list const& node) const;
//syntax::result_type syntax::operator()(ast::sequence_of_statements const& node) const;
//syntax::result_type syntax::operator()(ast::sequential_statement const& node) const;
//syntax::result_type syntax::operator()(ast::shift_expression const& node) const;
//syntax::result_type syntax::operator()(ast::signal_assignment_statement const& node) const;
//syntax::result_type syntax::operator()(ast::signal_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::signal_list_list const& node) const; // signal_list helper (not in BNF)
//syntax::result_type syntax::operator()(ast::signal_list const& node) const;
//syntax::result_type syntax::operator()(ast::signature const& node) const;
//syntax::result_type syntax::operator()(ast::simple_expression const& node) const;
//syntax::result_type syntax::operator()(ast::slice_name const& node) const;
//syntax::result_type syntax::operator()(ast::string_literal const& node) const;
//syntax::result_type syntax::operator()(ast::subprogram_body const& node) const;
//syntax::result_type syntax::operator()(ast::subprogram_declarative_item const& node) const;
//syntax::result_type syntax::operator()(ast::subprogram_declarative_part const& node) const;
//syntax::result_type syntax::operator()(ast::subprogram_specification const& node) const;
//syntax::result_type syntax::operator()(ast::subtype_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::subtype_indication const& node) const;
//syntax::result_type syntax::operator()(ast::suffix const& node) const;
//syntax::result_type syntax::operator()(ast::target const& node) const;
//syntax::result_type syntax::operator()(ast::term const& node) const;
//syntax::result_type syntax::operator()(ast::timeout_clause const& node) const;
//syntax::result_type syntax::operator()(ast::type_conversion const& node) const;
//syntax::result_type syntax::operator()(ast::type_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::type_definition const& node) const;
//syntax::result_type syntax::operator()(ast::unconstrained_array_definition const& node) const;


syntax::result_type syntax::operator()(ast::use_clause const& node) const
{
    static char const node_name[]{ "use_clause" };
    indent_logging<verbose> _(*this, node_name);

    return true;
}


//syntax::result_type syntax::operator()(ast::variable_assignment_statement const& node) const;
//syntax::result_type syntax::operator()(ast::variable_declaration const& node) const;
//syntax::result_type syntax::operator()(ast::wait_statement const& node) const;
//syntax::result_type syntax::operator()(ast::waveform const& node) const;
//syntax::result_type syntax::operator()(ast::waveform_element const& node) const;

// keywords and miscellaneous
//syntax::result_type syntax::operator()(ast::boost::iterator_range<parser::iterator_type> const& node) const;
//syntax::result_type syntax::operator()(ast::keyword_token token);



syntax::result_type syntax::operator()(ast::nullary const&) const
{
    static char const node_name[]{ "nullary" };
    indent_logging<verbose> _(*this, node_name);

    os << "\n***********************************************";
    os << "\n* variant default constructible node detected *";
    os << "\n***********************************************\n";

    // these is a real error
    ++context.error_count;

    return false;
}


template<typename T>
syntax::result_type syntax::operator()(T const&) const
{
    static char const node_name[]{ "unknown" };
    indent_logging<verbose> _(*this, node_name);

    os << "### caught straying node of type <"
       << util::pretty_typename<T>{}
       << ">\n";

    ++context.warning_count;

    return false;
}


} } } // namespace eda.vhdl.analyze


#include <eda/compiler/warnings_on.hpp>
