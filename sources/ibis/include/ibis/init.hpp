/*
 * init.hpp
 *
 *  Created on: 07.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_
#define SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_


#include <string>
#include <vector>


namespace eda {
	class settings;
}
namespace docopt {
	struct value;
}


namespace ibis {


class init
{
public:
	init(int argc, const char* argv[], eda::settings& settings);

	// FixMe: Tribute to not use optional<variant<T,...>>
	std::vector<std::string> const& file_list() const {
		return sourcefile_list;
	}

private:
	void parse_env();
	void parse_cli(int argc, const char* argv[]);
	bool eval_doccpp_option(std::string const& key, docopt::value const& value);
	void set_color_messages();
    void register_signal_handlers();

private:
	eda::settings& 									settings;
	std::vector<std::string>						sourcefile_list;
};


}


#endif /* SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_ */
