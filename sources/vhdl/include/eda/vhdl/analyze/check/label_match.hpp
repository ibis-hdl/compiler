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


namespace eda { namespace vhdl { namespace analyze {


/**
 * check for matching label pairs
 */
class label_match
{
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
    result compare(ast::identifier const& entry, ast::optional<ast::identifier> const& exit) const;
    result compare(ast::optional<ast::identifier> const& entry, ast::optional<ast::identifier> const& exit) const;
};


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_ */
