//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <format>

namespace testsuite::vhdl::numeric_convert::util {

///
/// binary string literal test pattern generator
///
class bit_string_literal_generator {
public:
    using value_type = std::uint64_t;

public:
    static std::string bin(value_type number, std::string_view postfix = "")
    {
        return std::format(R"(b"{:b}{}")", number, postfix);
    }

    static std::string oct(value_type number, std::string_view postfix = "")
    {
        return std::format(R"(o"{:o}{}")", number, postfix);
    }

    static std::string hex(value_type number, std::string_view postfix = "")
    {
        return std::format(R"(x"{:x}{}")", number, postfix);
    }
};

}  // namespace testsuite::vhdl::numeric_convert::util
