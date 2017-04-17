/*
 * variant.hpp
 *
 *  Created on: 17.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_UTILS_FAKE_HEADER_BOOST_SPIRIT_HOME_X3_SUPPORT_AST_VARIANT_HPP_
#define SOURCES_VHDL93_UTILS_FAKE_HEADER_BOOST_SPIRIT_HOME_X3_SUPPORT_AST_VARIANT_HPP_


#include <boost/mpl/list.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <type_traits>


/**
 * boost.varaint fake header to make CasXML happy
 */
namespace boost { namespace spirit { namespace x3
{
    template <typename T>
    class forward_ast
    {
    public:

        typedef T type;

    public:

        forward_ast();

        forward_ast(forward_ast const& operand);

        forward_ast(forward_ast&& operand);

        forward_ast(T const& operand);

        forward_ast(T&& operand);

        ~forward_ast();

        forward_ast& operator=(forward_ast const& rhs);

        void swap(forward_ast& operand);

        forward_ast& operator=(T const& rhs);

        forward_ast& operator=(forward_ast&& rhs);

        forward_ast& operator=(T&& rhs);

        operator T const&() const;
        operator T&();
    };

    namespace detail
    {
        template <typename T>
        struct remove_forward : mpl::identity<T>
        {};

        template <typename T>
        struct remove_forward<forward_ast<T>> : mpl::identity<T>
        {};
    }

    template <typename ...Types>
    struct variant
    {
        // tell spirit that this is an adapted variant
        struct adapted_variant_tag;

        using variant_type = variant<Types...>;
        using types        = mpl::list<typename detail::remove_forward<Types>::type...>;
        using base_type    = variant; // The current instantiation

        template<typename T>
        using non_self_t // used only for SFINAE checks below
            = std::enable_if_t<!(std::is_base_of<base_type
                                                ,std::remove_reference_t<T>
                                                >
                                                ::value)
                              >;

        variant();

        template <typename T, class = non_self_t<T>>
        explicit variant(T const& rhs);

        template <typename T, class = non_self_t<T>>
        explicit variant(T&& rhs);

        variant(variant const& rhs);

        variant(variant& rhs);

        variant(variant&& rhs);

        variant& operator=(variant const& rhs);

        variant& operator=(variant&& rhs);

        template <typename T, class = non_self_t<T>>
        variant& operator=(T const& rhs);

        template <typename T, class = non_self_t<T>>
        variant& operator=(T&& rhs);

        template <typename F>
        typename F::result_type apply_visitor(F const& v);

        template <typename F>
        typename F::result_type apply_visitor(F const& v) const;

        template <typename F>
        typename F::result_type apply_visitor(F& v);

        template <typename F>
        typename F::result_type apply_visitor(F& v) const;

        variant_type const& get() const;

        variant_type& get();
    };
}}}

namespace boost
{
    template <typename T, typename ...Types>
    inline T const&
    get(boost::spirit::x3::variant<Types...> const& x);

    template <typename T, typename ...Types>
    inline T&
    get(boost::spirit::x3::variant<Types...>& x);

    template <typename T, typename ...Types>
    inline T const*
    get(boost::spirit::x3::variant<Types...> const* x);

    template <typename T, typename ...Types>
    inline T*
    get(boost::spirit::x3::variant<Types...>* x);
}



#endif /* SOURCES_VHDL93_UTILS_FAKE_HEADER_BOOST_SPIRIT_HOME_X3_SUPPORT_AST_VARIANT_HPP_ */
