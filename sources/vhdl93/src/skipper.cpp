/*
 * skipper.cpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#include <eda/vhdl93/parser/skipper_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>


namespace eda { namespace vhdl93 { namespace parser {

    BOOST_SPIRIT_INSTANTIATE(
        skipper_type,
        iterator_type,
        context_type
    );

} } }  // namespace eda.vhdl93.parser



