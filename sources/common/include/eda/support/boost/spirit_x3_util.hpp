/*
 * spirit_x3_util.hpp
 *
 *  Created on: 01.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_UTIL_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_UTIL_HPP_


namespace boost { namespace spirit { namespace x3
{

/**
 * Spirit X3.Parser utility for attribute handling
 *
 * \see [X3: Missing `as` directive #352](
 *       https://github.com/boostorg/spirit/issues/352#issuecomment-368354726)
 */
template <typename Subject>
struct protect_directive : Subject
{
    using base_type = Subject;

    protect_directive(Subject const& subject)
      : base_type(subject) {}
};

struct protect_gen
{
    template <typename Subject>
    protect_directive<typename extension::as_parser<Subject>::value_type>
    operator[](Subject const& subject) const
    {
        return { as_parser(subject) };
    }
};

auto const protect = protect_gen{};


/**
 * Spirit X3.Parser utility for attribute handling
 *
 * \see [Understanding the List Operator (%) in Boost.Spirit](
 *       https://stackoverflow.com/questions/33816662/understanding-the-list-operator-in-boost-spirit/33817135#33817135)
 */
template<typename T>
struct as_type {
    template<typename Expr>
    auto operator[](Expr&& expr) const {
        return x3::rule<struct _, T> { "as" } = x3::as_parser(
                std::forward<Expr>(expr));
    }
};

template<typename T> static const as_type<T> as = { };


}}}


namespace boost { namespace spirit { namespace x3 { namespace traits
{


template <typename Subject, typename Context>
struct attribute_of<x3::protect_directive<Subject>, Context>
    : attribute_of<Subject, Context> {};


}}}}


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_UTIL_HPP_ */
