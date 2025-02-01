//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//
#pragma once

#include <boost/locale/message.hpp>
#include <boost/locale/format.hpp>

#include <string_view>
#include <iosfwd>

namespace ibis {

enum class severity : std::uint8_t {
    note,
    warning,
    error,
    failure,
};

// clang-format off
std::ostream& message(std::string_view msg, ibis::severity severity, bool newline);
std::ostream& message(boost::locale::basic_message<char> msg, ibis::severity severity, bool newline);
std::ostream& message(boost::locale::basic_format<char> const& format, ibis::severity severity, bool newline);

static inline
std::ostream& note(std::string_view msg, bool newline = true) { return message(msg, severity::note, newline); };
static inline
std::ostream& warning(std::string_view msg, bool newline = true) { return message(msg, severity::warning, newline); }
static inline
std::ostream& error(std::string_view msg, bool newline = true) { return message(msg, severity::error, newline); }
static inline
std::ostream& failure(std::string_view msg, bool newline = true) { return message(msg, severity::failure, newline); }

static inline
std::ostream& note(boost::locale::basic_message<char> msg, bool newline = true) { return message(msg, severity::note, newline); };
static inline
std::ostream& warning(boost::locale::basic_message<char> msg, bool newline = true) { return message(msg, severity::warning, newline); }
static inline
std::ostream& error(boost::locale::basic_message<char> msg, bool newline = true) { return message(msg, severity::error, newline); }
static inline
std::ostream& failure(boost::locale::basic_message<char> msg, bool newline = true) { return message(msg, severity::failure, newline); }

static inline
std::ostream& note(boost::locale::basic_format<char> const& msg, bool newline = true) { return message(msg, severity::note, newline); };
static inline
std::ostream& warning(boost::locale::basic_format<char> const& msg, bool newline = true) { return message(msg, severity::warning, newline); }
static inline
std::ostream& error(boost::locale::basic_format<char> const& msg, bool newline = true) { return message(msg, severity::error, newline); }
static inline
std::ostream& failure(boost::locale::basic_format<char> const& msg, bool newline = true) { return message(msg, severity::failure, newline); }
// clang-format on

}  // namespace ibis
