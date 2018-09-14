/*
 * signal_handler.hpp
 *
 *  Created on: 14.09.2018
 *      Author: olaf
 */

#ifndef SOURCES_IBIS_INCLUDE_IBIS_SIGNAL_HANDLER_HPP_
#define SOURCES_IBIS_INCLUDE_IBIS_SIGNAL_HANDLER_HPP_

namespace ibis {

void register_signal_handlers();

const char* signal_name(int sig_num);

} // namespace ibis

#endif /* SOURCES_IBIS_INCLUDE_IBIS_SIGNAL_HANDLER_HPP_ */
