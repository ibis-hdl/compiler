/*
 * move_to.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TRAITS_MOVE_TO_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TRAITS_MOVE_TO_HPP_


/*
 * Note, this header is not intended to be included directly. Simply include
 * it at the end of the adapted structures to supply spirit.x3's attribute
 * movement.
 */


namespace boost { namespace spirit { namespace x3 { namespace traits {


#if 0
template <typename It>
void move_to(It b, It e, std::string_view& v)
{
    /* see [parsing from std::string into a boost::string_view using boost::spirit::x3]
     * (https://stackoverflow.com/questions/39225502/parsing-from-stdstring-into-a-booststring-view-using-boostspiritx3)
     * Note storage is contiguous, use concept check for input range */
    v = std::string_view(&*b, std::size_t(e - b));
}
#endif


using delay_mechanism = eda::vhdl93::ast::delay_mechanism;

inline void
move_to(delay_mechanism::delay_type type, delay_mechanism& dest)
{
    dest.type = type;
}


} } } } // boost.spirit.x3.traits


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TRAITS_MOVE_TO_HPP_ */
