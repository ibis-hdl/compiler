/*
 * check_label_match.cpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */



#include <eda/vhdl/analyze/check/label_match.hpp>
#include <eda/vhdl/ast.hpp>

#include <boost/range/algorithm/equal.hpp>

#include <boost/type_index.hpp>

#include <eda/support/boost/locale.hpp>


// don't pollute AST's namespace with operators required only here
namespace eda { namespace vhdl { namespace ast {


static inline
bool operator==(ast::label const& lhs, ast::label const& rhs) {
    return boost::range::equal(lhs.name, rhs.name);
}


} } } // namespace eda.vhdl.ast


namespace eda { namespace vhdl { namespace analyze {


template<typename AstNodeT>
bool label_match::test_mandatory_start(AstNodeT const& node) const
{
    if(node.end_label) {

        bool const label_ok = (node.label == node.end_label);

        if(label_ok) return true;
        return false;
    }

    return true;
}


template<typename AstNodeT>
bool label_match::test_optional_start(AstNodeT const& node) const
{
    if(node.label && node.end_label) {

        bool const label_ok = (node.label == node.end_label);

        if(label_ok) return true;
        return false;
    }

    return true;
}


bool label_match::operator()(ast::block_statement const& node) const
{
    return test_mandatory_start(node);
}


bool label_match::operator()(ast::case_statement const& node) const
{
    return test_optional_start(node);
}


bool label_match::operator()(ast::generate_statement const& node) const
{
    return test_mandatory_start(node);
}


bool label_match::operator()(ast::if_statement const& node) const
{
    return test_optional_start(node);
}


bool label_match::operator()(ast::loop_statement const& node) const
{
    return test_optional_start(node);
}


bool label_match::operator()(ast::process_statement const& node) const
{
    return test_optional_start(node);
}


template<typename T>
std::string label_match::symbol_name(T const&)
{
    std::string name{ boost::typeindex::type_id<T>().pretty_name() };
    std::size_t const npos = name.rfind(':') + 1;
    return name.erase(0, npos);
}


std::string label_match::make_error_description(std::string const& rule_name)
{
    using boost::locale::format;
    using boost::locale::translate;

    return (
    	format(translate(
        "Syntax error: Label mismatch in {1}\n"
        ))
        % rule_name
    ).str();
}


} } } // namespace eda.vhdl.ast

