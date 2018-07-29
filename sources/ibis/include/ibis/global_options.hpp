/*
 * global_options.hpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_IBIS_INCLUDE_IBIS_GLOBAL_OPTIONS_HPP_
#define SOURCES_IBIS_INCLUDE_IBIS_GLOBAL_OPTIONS_HPP_

#include <vector>
#include <string>

namespace ibis {


typedef struct {

    std::vector<std::string>                        source_files;

} global_options_type;



extern global_options_type global_options;

} // namespace ibis


#endif /* SOURCES_IBIS_INCLUDE_IBIS_GLOBAL_OPTIONS_HPP_ */
