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

}  // namespace boost::spirit::x3

namespace boost::spirit::x3::traits {

template <typename Subject, typename Context>
struct attribute_of<x3::protect_directive<Subject>, Context> : attribute_of<Subject, Context> {
};

//
// ===--------- Spirit X3 Debug Helper ---------==
//
#if defined(BOOST_SPIRIT_X3_DEBUG)
// After Spirit.X3 1.64 the code with defined BOOST_SPIRIT_X3_DEBUG seems to be
// changed. Old support for the AST nodes using operator<<() isn't required
// any more, but the code for x3::raw[] / boost::iterator_range<> is missing,
// hence Quick&Dirty to supply this.
namespace boost::spirit::x3::traits {

template <typename Out, typename T>
inline void print_attribute(Out& os, boost::iterator_range<T> const& range)
{
    os << range;
}
#endif

}  // namespace boost::spirit::x3::traits
