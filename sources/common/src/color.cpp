/*
 * color.cpp
 *
 *  Created on: 10.08.2018
 *      Author: olaf
 */

#include <eda/color/message.hpp>

#include <eda/util/string/icompare.hpp>


namespace eda { namespace color {


// static std::locale::id for each facet
template<> std::locale::id message_facet<message::severity::failure>::id;
template<> std::locale::id message_facet<message::severity::error>::id;
template<> std::locale::id message_facet<message::severity::warning>::id;
template<> std::locale::id message_facet<message::severity::note>::id;


std::optional<color::attribute> text_attr(std::string_view const& name)
{
	using namespace std::literals::string_view_literals;

	std::initializer_list<std::pair<std::string_view, color::attribute>> const map{
		{ "bold"sv, 	color::attribute::Text_Bold }
	};

	for (auto const& [color_name, attribute] : map) {
		if (util::icompare(color_name, name)) {
			return std::optional<color::attribute>(attribute);
		}
	}

	return std::optional<color::attribute>{};
}


std::optional<color::attribute> foreground_attr(std::string_view const& name)
{
	using namespace std::literals::string_view_literals;

	static std::initializer_list<std::pair<std::string_view, color::attribute>> const map{
		{ "black"sv, 	color::attribute::Foreground_Black },
		{ "red"sv,   	color::attribute::Foreground_Red },
		{ "green"sv, 	color::attribute::Foreground_Green },
		{ "yellow"sv, 	color::attribute::Foreground_Yellow },
		{ "blue"sv,  	color::attribute::Foreground_Blue },
		{ "magenta"sv, 	color::attribute::Foreground_Magenta },
		{ "cyan"sv, 	color::attribute::Foreground_Cyan },
		{ "white"sv, 	color::attribute::Foreground_White }
	};

	for (auto const& [color_name, attribute] : map) {
		if (util::icompare(color_name, name)) {
			return std::optional<color::attribute>(attribute);
		}
	}

	return std::optional<color::attribute>{};
}


std::optional<color::attribute> background_attr(std::string_view const& name)
{
	using namespace std::literals::string_view_literals;

	static std::initializer_list<std::pair<std::string_view, color::attribute>> const map{
		{ "black"sv, 	color::attribute::Background_Black },
		{ "red"sv,   	color::attribute::Background_Red },
		{ "green"sv, 	color::attribute::Background_Green },
		{ "yellow"sv, 	color::attribute::Background_Yellow },
		{ "blue"sv,  	color::attribute::Background_Blue },
		{ "magenta"sv, 	color::attribute::Background_Magenta },
		{ "cyan"sv, 	color::attribute::Background_Cyan },
		{ "white"sv, 	color::attribute::Background_White }
	};

	for (auto const& [color_name, attribute] : map) {
		if (util::icompare(color_name, name)) {
			return std::optional<color::attribute>(attribute);
		}
	}

	return std::optional<color::attribute>{};
}


} } // namespace eda.color

