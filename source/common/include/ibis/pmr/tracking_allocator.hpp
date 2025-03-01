//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <memory_resource>
#include <string_view>
#include <format>
#include <iostream>
#include <cstddef>

namespace ibis::pmr {

///
/// upstream polymorphic allocator e.g. used for formatting
///
/// @see [Special Allocators with C++17](
///       https://www.modernescpp.com/index.php/special-allocators-with-c17/)
///
/// @note Proof of concept using std::pmr [coliru](
///       https://coliru.stacked-crooked.com/a/f01afbac75d7723c)
/// Usage example:
/// @code
/// TrackingAllocator<true> upstream_allocator{ "'xyz' formatter" };
///
/// static constexpr std::size_t BUF_SIZE{ 42 };
///
/// std::array<string_view::value_type, BUF_SIZE> buf;
/// std::pmr::monotonic_buffer_resource pool{ buf.data(), buf.size(), &upstream_allocator };
/// std::pmr::string temp_literal{ &pool };
/// ...
/// @endcode
///
template <bool verbose = false>
class TrackingAllocator : public std::pmr::memory_resource {
public:
    constexpr TrackingAllocator(std::string_view name_ = { "N/A" })
        : name{ name_ }
    {
    }

    void* do_allocate(std::size_t bytes, std::size_t alignment) override
    {
        void* ptr = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        if constexpr (verbose) {
            std::cout << std::format("  pmr::allocate {:6} bytes at {} ({})\n", bytes, ptr, name);
        }
        return ptr;
    }

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override
    {
        if constexpr (verbose) {
            std::cout << std::format("  pmr::deallocate {:4} bytes at {} ({})\n", bytes, ptr, name);
        }
        return std::pmr::new_delete_resource()->deallocate(ptr, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
    {
        return std::pmr::new_delete_resource()->is_equal(other);
    }

private:
    std::string_view const name;
};

}  // namespace ibis::pmr
