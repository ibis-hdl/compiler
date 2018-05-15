/*
 * support.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_X3_SUPPORT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_X3_SUPPORT_HPP_


/*
 * Support Spirit.X3's attribute handling.
 * Note, this header is not intended to be included directly.
 */

/*
 * Spirit.X3 Traits
 */
namespace boost { namespace spirit { namespace x3 { namespace traits {


using delay_mechanism = eda::vhdl::ast::delay_mechanism;

static inline void
move_to(delay_mechanism::delay_type type_, delay_mechanism& mechanism)
{
    mechanism.type = type_;
}



using keyword_token = eda::vhdl::ast::keyword_token;

static inline void
move_to(keyword_token token, bool& dest)
{
    dest = static_cast<bool>(token);
}


} } } } // boost.spirit.x3.traits


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_X3_SUPPORT_HPP_ */
