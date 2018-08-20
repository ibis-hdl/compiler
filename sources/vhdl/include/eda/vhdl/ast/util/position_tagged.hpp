/*
 * position_tagged.hpp
 *
 *  Created on: 23.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_

#include <limits>


namespace eda { namespace vhdl { namespace ast {

// ToDo/FixMe: Documentation
// Use this to annotate an AST with the iterator position.
// These ids are used as a key to the position_cache (below)
// and marks the start and end of an AST node.
struct position_tagged
{
    typedef std::size_t                             tag_type;

    static constexpr tag_type MAX_ID = std::numeric_limits<tag_type>::max();

    bool is_tagged() const {
    	return pos_id < MAX_ID;
    }


    tag_type 										pos_id{ MAX_ID };
};


}}} // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_ */
