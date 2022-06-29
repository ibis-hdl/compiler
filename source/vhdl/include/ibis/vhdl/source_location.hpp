//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string_view>
#include <cstdint>

namespace ibis::vhdl {

///
/// Class which mimics `std::source_location` to be used for VHDL's issue location.
///
class source_location {
public:
    ///
    /// Construct a new source location object
    ///
    /// @param file_name Name of the file proceeded
    /// @param line      Line number of issue
    /// @param column    Column number of issue
    ///
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    source_location(std::string_view file_name, std::size_t line, std::size_t column)
        : file_name_{ file_name }
        , line_{ line }
        , column_{ column }
    {
    }

    source_location() = default;
    source_location(source_location const&) = default;
    source_location& operator=(source_location const&) = default;
    source_location(source_location&&) = default;
    source_location& operator=(source_location&&) = default;

    /// The line number of the error
    std::size_t line() const { return line_; }

    /// The column number of the error
    std::size_t column() const { return column_; }

    /// The file name
    std::string_view file_name() const { return file_name_; }

private:
    std::string_view file_name_ = "N/A";
    std::size_t line_ = 0;
    std::size_t column_ = 0;
};

}  // namespace ibis::vhdl
