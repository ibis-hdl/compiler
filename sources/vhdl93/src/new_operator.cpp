/*
 * operator.cpp
 *
 *  Created on: 19.04.2017
 *      Author: olaf
 */

#include <eda/vhdl93/parser/operator_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>


namespace eda { namespace vhdl93 { namespace parser {

    BOOST_SPIRIT_INSTANTIATE(
        logical_operator_type,
        iterator_type,
        context_type
    );

    BOOST_SPIRIT_INSTANTIATE(
        logical_operator_option_type,
        iterator_type,
        context_type
    );

    BOOST_SPIRIT_INSTANTIATE(
        unary_miscellaneous_operator_type,
        iterator_type,
        context_type
    );

    BOOST_SPIRIT_INSTANTIATE(
        multiplying_operator_type,
        iterator_type,
        context_type
    );

    BOOST_SPIRIT_INSTANTIATE(
        shift_operator_type,
        iterator_type,
        context_type
    );

} } }  // namespace eda.vhdl93.parser



