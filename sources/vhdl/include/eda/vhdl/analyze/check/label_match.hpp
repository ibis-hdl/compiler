/*
 * check_label_match.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_


#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <string>
#include <iosfwd>


namespace eda { namespace vhdl { namespace analyze {


class check_label_match
{
    std::ostream&                                   os;

public:
    // check for matching label pairs
    check_label_match(std::ostream& os_);

    bool operator()(ast::block_statement const& node);
    bool operator()(ast::case_statement const& node);
    bool operator()(ast::generate_statement const& node);
    bool operator()(ast::if_statement const& node);
    bool operator()(ast::loop_statement const& node);
    bool operator()(ast::process_statement const& node);

    template<typename T>
    bool operator()(T const&) {
        return true;
    }

private:
    template<typename AstNodeT>
    bool test_mandatory_start(AstNodeT const& node);

    template<typename AstNodeT>
    bool test_optional_start(AstNodeT const& node);

    template<typename T>
    std::string symbol_name(T const&);

    template<typename AstNodeT>
    void make_error_description(AstNodeT const& node) {
        make_error_description(symbol_name(node), node);
    }

    void make_error_description(std::string const& rule_name, ast::position_tagged const& position_tag) const;
};


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_ */
