/*
 * parser_config.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL93_PARSER_CONFIG_HPP_
#define INCLUDE_EDA_VHDL93_PARSER_CONFIG_HPP_


//#include <eda/vhdl93/error_handler.hpp>

#include <boost/spirit/home/x3.hpp>

#include <string>


namespace eda { namespace vhdl93 { namespace parser {

	namespace x3 = boost::spirit::x3;

	typedef std::string::const_iterator iterator_type;
#if 0
	typedef error_handler<iterator_type> error_handler_type;

	typedef x3::phrase_parse_context<
		x3::ascii::space_type>::type
	phrase_context_type;

	typedef x3::with_context<
		error_handler_tag
		, std::reference_wrapper<error_handler_type> const
		, phrase_context_type>::type
	context_type;
#else
	typedef x3::unused_type context_type;
#endif

} } }  // namespace eda.vhdl93.parser



#endif /* INCLUDE_EDA_VHDL93_PARSER_CONFIG_HPP_ */
