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
	explicit init(int argc, const char* argv[], eda::settings& setting);

	init(init const&) = delete;
	init& operator=(init const&) = delete;

	// FixMe: Tribute to not use optional<variant<T,...>> as option type
	std::vector<std::string> const& file_list() const {
		return sourcefile_list;
	}

private:
	void parse_env();
	void parse_cli(int argc, const char* argv[]);
	bool eval_doccpp_option(std::string const& key, docopt::value const& value);
    void register_signal_handlers();
    void user_config_message_color();

private:
	eda::settings& 									setting;
	std::vector<std::string>						sourcefile_list;
};


}


#endif /* SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_ */