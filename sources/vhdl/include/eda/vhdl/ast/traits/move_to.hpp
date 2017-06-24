/*
 * move_to.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TRAITS_MOVE_TO_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TRAITS_MOVE_TO_HPP_


/*
 * Note, this header is not intended to be included directly. Simply include
 * it at the end of the adapted structures to supply spirit.x3's attribute
 * movement.
 */


namespace boost { namespace spirit { namespace x3 { namespace traits {


template <typename Source, typename Dest>
inline void move_to(Source&& src, Dest& dest);



template <typename Iterator>
inline
void move_to(Iterator first, Iterator last, std::string_view& str_v)
{
    /* see [parsing from std::string into a boost::string_view using boost::spirit::x3]
     * (https://stackoverflow.com/questions/39225502/parsing-from-stdstring-into-a-booststring-view-using-boostspiritx3)
     * Note storage is contiguous, use concept check for input range */
    str_v = std::string_view(&*first, std::size_t(last - first));
}


using delay_mechanism = eda::vhdl::ast::delay_mechanism;

inline void
move_to(delay_mechanism::delay_type type, delay_mechanism& dest)
{
    dest.type = type;
}



using keyword_token = ::eda::vhdl::ast::keyword_token;
//FixMe: Doesn't work as expected, always true??
template <>
inline void
move_to(keyword_token&& src, bool& dest)
{
    dest = static_cast<bool>(src);
}


} } } } // boost.spirit.x3.traits


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TRAITS_MOVE_TO_HPP_ */
