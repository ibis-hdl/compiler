/*
 * literal.cpp
 *
 *  Created on: 21.04.2017
 *      Author: olaf
 */

#include <eda/vhdl93/parser/literal_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>


namespace eda { namespace vhdl93 { namespace parser {

    BOOST_SPIRIT_INSTANTIATE(
        string_literal_type,
        iterator_type,
        context_type
    );

} } }  // namespace eda.vhdl93.parser






