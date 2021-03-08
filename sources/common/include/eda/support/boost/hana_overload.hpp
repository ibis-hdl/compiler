/*
 * hana_overload.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_HANA_OVERLOAD_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_HANA_OVERLOAD_HPP_

#include <boost/variant/apply_visitor.hpp>
#include <type_traits>

namespace eda {
namespace util {

// boost::hana::overload copy & paste

#if !defined(DOXYGEN) // temporary disabled for doxygen to avoid warnings

template <typename F, typename... G>
struct overload_t : overload_t<F>::type, overload_t<G...>::type {
    using type = overload_t;
    using overload_t<F>::type::operator();
    using overload_t<G...>::type::operator();

    template <typename F_, typename... G_>
    constexpr explicit overload_t(F_&& f, G_&&... g)
        : overload_t<F>::type(static_cast<F_&&>(f))
        , overload_t<G...>::type(static_cast<G_&&>(g)...)
    {
    }
};

template <typename F> struct overload_t<F> {
    using type = F;
};

template <typename R, typename... Args> struct overload_t<R (*)(Args...)> {
    using type = overload_t;
    R(*fptr_)
    (Args...);

    explicit constexpr overload_t(R (*fp)(Args...))
        : fptr_(fp)
    {
    }

    constexpr R operator()(Args... args) const { return fptr_(static_cast<Args&&>(args)...); }
};

#endif // DOXYGEN

struct make_overload_t {
    template <typename... F,
        typename Overload = typename overload_t<typename std::decay<F>::type...>::type>
    constexpr Overload operator()(F&&... f) const
    {
        return Overload(static_cast<F&&>(f)...);
    }
};

constexpr make_overload_t overload{};

/* ["Fire-and-forget"
 * visitation](https://vittorioromeo.info/index/blog/variants_lambdas_part_1.html) */
#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

template <typename... Ts> decltype(auto) visit(Ts&&... xs)
{
    return ::boost::apply_visitor(FWD(xs)...);
}

template <typename TVariant, typename... TVisitors>
auto visit_in_place(TVariant&& variant, TVisitors&&... visitors)
{
    // FixMe: Doesn't compile:
    // return boost::apply_visitor(std::forward<TVisitors>(visitors)...,
    // std::forward<TVariant>(variant));
    return util::visit(
        overload(std::forward<TVisitors>(visitors)...), std::forward<TVariant>(variant));
}

} // namespace util
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_HANA_OVERLOAD_HPP_ */
