/*
 * grammar.cpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */


#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>


namespace eda { namespace vhdl { namespace parser {

    BOOST_SPIRIT_INSTANTIATE(
        expression_type,
        iterator_type,
        context_type
    );

} } }  // namespace eda.vhdl.parser

