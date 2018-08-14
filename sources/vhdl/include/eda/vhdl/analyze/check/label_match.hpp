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
#include <string_view>
#include <iosfwd>

namespace eda { namespace vhdl { namespace analyze {


/**
 * check for matching label pairs
 */
class label_match
{
public:
    bool operator()(ast::block_statement const& node) const;
    bool operator()(ast::case_statement const& node) const;
    bool operator()(ast::generate_statement const& node) const;
    bool operator()(ast::if_statement const& node) const;
    bool operator()(ast::loop_statement const& node) const;
    bool operator()(ast::process_statement const& node) const;

    template<typename T>
    bool operator()(T const&) const {
        return true;
    }

public:
    static
    std::string make_error_description(std::string_view const& rule_name);

    template<typename AstNodeT>
    static inline
	std::string make_error_description(AstNodeT const& node) {
        return make_error_description(symbol_name(node));
    }

private:
    template<typename AstNodeT>
    bool test_mandatory_start(AstNodeT const& node) const;

    template<typename AstNodeT>
    bool test_optional_start(AstNodeT const& node) const;

    template<typename T>
    static
	std::string symbol_name(T const&);
};


template<typename AstNodeT>
bool check_label_match(AstNodeT&& node) {
    return label_match{}(std::forward<AstNodeT>(node));
}

} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_ */
