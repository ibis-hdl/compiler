/*
 * namespace_alias.hpp
 *
 *  Created on: 26.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_NAMESPACE_ALIAS_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_NAMESPACE_ALIAS_HPP_


// forward Boost.Orgs's namespace used
namespace boost {

    namespace spirit { namespace x3 {

         namespace iso8859_1 { }

    } }  // namespace spirit.x3

    namespace filesystem {

    } // namespace filesystem

} // namespace boost


// namespace forward and alias
namespace eda {

	namespace x3 = boost::spirit::x3;

	namespace vhdl {

		namespace ast { }

		namespace parser {
			// VHDL char set is iso8859:1
			namespace iso8859_1 = boost::spirit::x3::iso8859_1;
		}

		namespace analyze { }
	} // namespace vhdl

	namespace fs = boost::filesystem;

} // namespace eda



#endif /* SOURCES_COMMON_INCLUDE_EDA_NAMESPACE_ALIAS_HPP_ */
