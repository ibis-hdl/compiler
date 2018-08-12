/*
 * ast_walk_node_count.cpp
 *
 *  Created on: 12.08.2018
 *      Author: olaf
 */

#include <eda/vhdl/basic_ast_walker.hpp>

#include <string_view>
#include <iostream>


struct worker {

	worker(std::ostream& os_)
	: os{ os_ }
	{ }

    template<typename NodeT>
    void operator()(NodeT const&, std::string_view const& node_name) const {
        os << node_name << "\n";
    }

    std::ostream&									os;
};


using ast_node_counter = eda::vhdl::ast::basic_ast_walker<worker>;
