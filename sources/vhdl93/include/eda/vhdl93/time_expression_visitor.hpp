/*
 * time_expression_visitor.hpp
 *
 *  Created on: 19.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_TIME_EXPRESSION_VISITOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_TIME_EXPRESSION_VISITOR_HPP_


#include <eda/vhdl93/ast_adapted.hpp>


namespace eda { namespace vhdl93 { namespace ast {


/*
 * Skeleton for time_expression evaluator
 *
 * Note: - This contains the full expression nodes, even not all are written
 *       - The whole ast must be traversed to get the lower nodes be called
 *       - e.g. time expressions like 5ns + 5ms must be evaluated to
 */
struct time_expression_visitor: public boost::static_visitor<bool>
{
    time_expression_visitor() { }

    template <typename... T>
    bool operator()(boost::variant<T...> const& variant) {
        return boost::apply_visitor(*this, variant);
    }

    bool operator()(aggregate const& node) {
        return false;
    }

    bool operator()(attribute_designator const& node) {
        return false;
    }

    bool operator()(attribute_name const& node) {
        return false;
    }

    bool operator()(based_literal const& node) {
        return false;
    }

    bool operator()(bit_string_literal const& node) {
        return false;
    }

    bool operator()(character_literal const& node) {
        return false;
    }

    bool operator()(choices const& node) {
        return false;
    }

    bool operator()(decimal_literal const& node) {
        return false;
    }

    bool operator()(element_association const& node) {
        return false;
    }

    bool operator()(expression const& node) {
        return false;
    }

    bool operator()(factor const& node) {
        return false;
    }

    bool operator()(function_call const& node) {
        return false;
    }

    bool operator()(identifier const& node) {
        return false;
    }

    bool operator()(index_constraint const& node) {
        return false;
    }

    bool operator()(indexed_name const& node) {
        return false;
    }

    bool operator()(operator_symbol const& node) {
        return false;
    }

    bool operator()(physical_literal const& node) {
        return false;
    }

    bool operator()(qualified_expression const& node) {
        return false;
    }

    bool operator()(range_constraint const& node) {
        return false;
    }

    bool operator()(relation const& node) {
        return false;
    }

    bool operator()(selected_name const& node) {
        return false;
    }

    bool operator()(shift_expression const& node) {
        return false;
    }

    bool operator()(signature const& node) {
        return false;
    }

    bool operator()(simple_expression const& node) {
        return false;
    }

    bool operator()(simple_name const& node) {
        return false;
    }

    bool operator()(slice_name const& node) {
        return false;
    }

    bool operator()(string_literal const& node) {
        return false;
    }

    bool operator()(subtype_indication const& node) {
        return false;
    }

    bool operator()(term const& node) {
        return false;
    }

    bool operator()(type_conversion const& node) {
        return false;
    }

    bool operator()(type_mark const& node) {
        return false;
    }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_TIME_EXPRESSION_VISITOR_HPP_ */
