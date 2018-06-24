/*
 * check_label_match.cpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */



#include <eda/vhdl/analyze/check/label_match.hpp>

#include <boost/range/algorithm/equal.hpp>

#include <boost/type_index.hpp>

#include <eda/support/boost/locale.hpp>


// don't pollute AST namespace with operators required only here
namespace eda { namespace vhdl { namespace ast {


static inline
bool operator==(ast::label const& lhs, ast::label const& rhs) {
    return boost::range::equal(lhs.name, rhs.name);
}


} } } // namespace eda.vhdl.ast


namespace eda { namespace vhdl { namespace analyze {


check_label_match::check_label_match(std::ostream& os_)
: os{ os_ }
{ }

bool check_label_match::operator()(ast::block_statement const& node)
{
    // block_statement start label is mandatory
    if(node.end_label) {

        bool const label_ok = (node.label == node.end_label);

        if(label_ok) return true;

        using boost::locale::format;
        using boost::locale::translate;

        make_error_description(symbol_name(node), node);

        return false;
    }

    return true;
}

bool check_label_match::operator()(ast::design_file const& node)
{
    os << symbol_name(node) << " here\n";

    return true;
}


bool check_label_match::operator()(ast::nullary const&)
{
    os << "\n*****************************";
    os << "\n*    SHALL NEVER BE HERE    *";
    os << "\n*****************************\n";

    return false;
}


template<typename T>
std::string check_label_match::symbol_name(T const&)
{
    std::string name{ boost::typeindex::type_id<T>().pretty_name() };
    std::size_t const npos = name.rfind(':') + 1;
    return name.erase(0, npos);
}


void check_label_match::make_error_description(
    std::string&& rule_name, ast::position_tagged const& position_tag) const
{
    using boost::locale::format;
    using boost::locale::translate;

    os << format(translate(
        "Syntax error: Label mismatch in {1}\n"
        ))
        % rule_name;

//        os << std::string(node.id_first) // XXXX how to get the source string back?

}


} } } // namespace eda.vhdl.ast

