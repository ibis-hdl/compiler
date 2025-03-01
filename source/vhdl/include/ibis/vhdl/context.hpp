//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/util/tagged_treshold_counter.hpp>

#include <cstdint>
#include <functional>
#include <iosfwd>

namespace ibis::vhdl {

///
/// The VHDL context used for analyze and elaboration with {error, warnings} counter
///
class vhdl_global_context {
public:
    using value_type = std::uint32_t;

    using error_counter = util::tagged_treshold_counter<value_type, struct error_tag>;
    using warning_counter = util::tagged_treshold_counter<value_type, struct warning_tag>;

    static constexpr auto DEFAULT_ERROR_LIMIT = 42U;

public:
    ///
    /// Creates the VHDL context
    ///
    /// @param error_limit threshold of error count value.
    ///
    explicit vhdl_global_context(value_type error_limit = DEFAULT_ERROR_LIMIT)
        : error_count{ error_limit }
        , warning_count{ warning_counter::MAX_THRESHOLD }
    {
    }

    ~vhdl_global_context() = default;

    vhdl_global_context(vhdl_global_context&&) = default;
    vhdl_global_context& operator=(vhdl_global_context&&) = default;

    // non-copyable
    vhdl_global_context(vhdl_global_context&) = delete;
    vhdl_global_context& operator=(vhdl_global_context&) = delete;

public:
    enum class Standard : std::uint8_t { VHDL93, VHDL2000, VHDL2002, VHDL2007, VHDL2008, VHDL2019 };

public:
    class failure_status;

    failure_status get_failure_status() const;

    bool error_free() const { return error_count == 0; }

    bool has_errors() const { return error_count != 0; }
    bool has_warnings() const { return warning_count != 0; }

    error_counter& errors() { return error_count; }
    value_type errors() const { return error_count.get(); }

    warning_counter& warnings() { return warning_count; }
    value_type warnings() const { return warning_count.get(); }

private:
    error_counter error_count;
    warning_counter warning_count;
};

///
/// IO-manipulator to print the context error/warning status of context
///
class vhdl_global_context::failure_status {
    std::reference_wrapper<vhdl_global_context const> ref_vhdl_ctx;

public:
    using value_type = vhdl_global_context::value_type;

public:
    explicit failure_status(vhdl_global_context const& ctx)
        : ref_vhdl_ctx{ std::ref(ctx) }
    {
    }

    bool error_free() const { return ref_vhdl_ctx.get().error_free(); }
    bool has_errors() const { return ref_vhdl_ctx.get().has_errors(); }
    bool has_warnings() const { return ref_vhdl_ctx.get().has_warnings(); }

    value_type errors() const { return ref_vhdl_ctx.get().errors(); }
    value_type warnings() const { return ref_vhdl_ctx.get().warnings(); }
};

inline vhdl_global_context::failure_status vhdl_global_context::get_failure_status() const
{
    return failure_status(*this);
}

std::ostream& operator<<(std::ostream& os, vhdl::vhdl_global_context::failure_status const& status);

}  // namespace ibis::vhdl
