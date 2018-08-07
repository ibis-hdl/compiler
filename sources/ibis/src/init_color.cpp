/*
 * init_color.cpp
 *
 *  Created on: 07.08.2018
 *      Author: olpetzol
 */

#include <eda/configuration.hpp>

#include <eda/color/message.hpp>

#include <memory>


void init_color(eda::configuration const& setting)
{
    bool const force_color = [&] {
        if (setting("force-color")) return true;
        return false;
    }();

    if (setting("no-color") && !force_color) {
        // no color wanted
        return;
    }

    auto const imbue = [](auto& stream, auto&& facet_ptr) {
        std::locale locale(std::locale(), facet_ptr.release());
        stream.imbue(locale);
    };

    using namespace eda::color;
    using namespace eda::color::message;

    /* black, red, green, yellow, blue, magenta,_cyan, white */
    // prototypes
    auto const note_format    = fg::green;
    auto const warning_format = fg::yellow;
    auto const error_format   = fg::magenta | text::bold;
    auto const failure_format = fg::red     | text::bold | bg::white;

    imbue(std::cerr, std::make_unique<note_facet>(
        note_format, color_off, force_color)
    );
    imbue(std::cerr, std::make_unique<warning_facet>(
        warning_format, color_off, force_color)
    );
    imbue(std::cerr, std::make_unique<error_facet>(
        error_format, color_off, force_color)
    );
    imbue(std::cerr, std::make_unique<failure_facet>(
        failure_format, color_off, force_color)
    );
}

