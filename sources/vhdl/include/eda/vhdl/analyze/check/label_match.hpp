/*
 * check_label_match.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_

#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

#include <eda/vhdl/ast/node/label.hpp>

#include <type_traits>


namespace eda { namespace vhdl { namespace analyze {


/**
 * check for matching label pairs
 */
class label_match
{
public:
    enum class result {
		OK,
		MISMATCH,
		ILLFORMED
    };

public:
    result operator()(ast::block_statement const& node) const;
    result operator()(ast::case_statement const& node) const;
    result operator()(ast::generate_statement const& node) const;
    result operator()(ast::if_statement const& node) const;
    result operator()(ast::loop_statement const& node) const;
    result operator()(ast::process_statement const& node) const;

    template<typename T>
    result operator()(T const&) const {
        return result::OK;
    }

private:
    result compare(ast::identifier const& start_label, ast::optional<ast::identifier> const& end_label) const;
    result compare(ast::optional<ast::identifier> const& start_label, ast::optional<ast::identifier> const& end_label) const;
};


/**
 * Helper functions to extract {start, end}_label of nodes for use with the error
 * handler
 */
template<typename NodeT>
std::tuple<ast::identifier const&, ast::identifier const&>
labels_of(NodeT const& node)
{
	using tuple_type = std::tuple<ast::identifier const&, ast::identifier const&>;

	if constexpr (std::is_same_v<std::decay_t<decltype(node.label)>, ast::optional<ast::identifier>>) {
		return tuple_type(*node.label, *node.end_label);
	}
	else {
		// mandatory start label
		return tuple_type(node.label, *node.end_label);
	}

}


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_ */
