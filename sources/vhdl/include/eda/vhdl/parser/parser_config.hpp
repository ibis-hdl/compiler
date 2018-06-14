/*
 * parser_config.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL_PARSER_CONFIG_HPP_
#define INCLUDE_EDA_VHDL_PARSER_CONFIG_HPP_

#include <eda/vhdl/parser/common_types.hpp>     // iterator_type
#include <eda/vhdl/parser/skipper.hpp>
#include <eda/vhdl/parser/namespace_alias.hpp>

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>


namespace eda { namespace vhdl { namespace parser {


typedef x3::error_handler<iterator_type>                error_handler_type;

typedef x3::phrase_parse_context<skipper_type>::type    phrase_context_type;

// used for external linkage
typedef x3::context<
      x3::error_handler_tag
    , std::reference_wrapper<error_handler_type> /* const */
    , phrase_context_type
>                                                       context_type;


}}}  // namespace eda.vhdl.parser



#endif /* INCLUDE_EDA_VHDL_PARSER_CONFIG_HPP_ */
