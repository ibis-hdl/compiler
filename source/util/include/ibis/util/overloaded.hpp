//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

namespace ibis::util {

///
/// Variant visitor overload for using with C++ lambda.
/// Until we get this in C++20 we have here our own overload.
///
/// @see https://en.cppreference.com/w/cpp/utility/variant/visit
/// @code
/// for (auto& v: vec) {
///   std::visit(overloaded {
///        [](auto arg) { std::cout << arg << ' '; },
///        [](double arg) { std::cout << std::fixed << arg << ' '; },
///        [](const std::string& arg) { std::cout << std::quoted(arg) << ' '; },
///    }, v);
/// }
/// @endcode
///
/// Also:
/// - @see [Overload: Build a Variant Visitor on the Fly](
///        https://arne-mertz.de/2018/05/overload-build-a-variant-visitor-on-the-fly/)
/// - @see [The Amazing std::visit](https://www.cppstories.com/2018/09/visit-variants/)
///
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>; // not needed in C++20...

}  // namespace ibis::util
