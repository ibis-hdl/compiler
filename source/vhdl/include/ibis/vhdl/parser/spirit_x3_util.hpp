//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

namespace boost::spirit::x3 {

///
/// Spirit X3.Parser utility for attribute handling
///
/// \see [X3: Missing `as` directive #352](
///      https://github.com/boostorg/spirit/issues/352#issuecomment-368354726)
///
template <typename Subject>
struct protect_directive : Subject {
    using base_type = Subject;

    protect_directive(Subject const& subject)
        : base_type(subject)
    {
    }
};

struct protect_gen {
    template <typename Subject>
    protect_directive<typename extension::as_parser<Subject>::value_type> operator[](
        Subject const& subject) const
    {
        return { as_parser(subject) };
    }
};

auto const protect = protect_gen{};

///
/// Spirit X3 parser utility for attribute handling
///
/// @see [Understanding the List Operator (%) in Boost.Spirit](
///  https://stackoverflow.com/questions/33816662/understanding-the-list-operator-in-boost-spirit/33817135#33817135)
/// For a more modern variant with C++ lambdas check near the bottom of
/// [Spirit X3, Is this error handling approach useful?](
/// https://stackoverflow.com/questions/57048008/spirit-x3-is-this-error-handling-approach-useful/57067207#57067207)
///
template <typename T>
struct as_type {
    template <typename Expr>
    auto operator[](Expr&& expr) const
    {
        return x3::rule<struct _, T>{ "as" } = x3::as_parser(std::forward<Expr>(expr));
    }
};

template <typename T>
static const as_type<T> as = {};

namespace traits {

template <typename Subject, typename Context>
struct attribute_of<x3::protect_directive<Subject>, Context> : attribute_of<Subject, Context> {};

}  // namespace traits

}  // namespace boost::spirit::x3

#if defined(BOOST_SPIRIT_X3_DEBUG)

namespace boost::spirit::x3::traits {

template <typename Out, typename T, typename Enable>
struct print_attribute_debug;

namespace ast = ibis::vhdl::ast;

// We need to define a way to print the AST nodes for the debug handlers.
// There are also implementations in {based, bit_string, decimal}_literal.hpp
// For some (at least to me) unknown reason, they aren't lifted here.

template <typename Out>
struct print_attribute_debug<Out, ast::nullary, void> {
    static void call(Out& out, ast::nullary const&) { out << "[nullary]"; }
};

template <typename Out, typename T>
struct print_attribute_debug<Out, boost::iterator_range<T>, void> {
    static void call(Out& out, boost::iterator_range<T> const& range) { out << range; }
};

template <typename Out, typename T>
struct print_attribute_debug<Out, x3::forward_ast<T>, void> {
    template <typename... U>
    static void call(Out& out, ast::variant<U...> const& value)
    {
        print_attribute_debug<Out, T>::call(out, value.get(), variant_attribute());
    }
    template <typename U>
    static void call(Out& out, U const& value)
    {
        print_attribute_debug<Out, T>::call(out, value);
    }
};

}  // namespace boost::spirit::x3::traits

#endif
