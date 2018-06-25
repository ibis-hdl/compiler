/*
 * ctx.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/context.hpp>

#include <iostream>

#include <eda/support/boost/locale.hpp>


namespace eda { namespace vhdl {


context::context()
: error_count{ 0 }
, warning_count{ 0 }
{ }



namespace detail {

struct error_message {
    std::size_t const count;
    explicit error_message(std::size_t count_) : count{ count_ } { }
    std::ostream& operator()(std::ostream& os) const {
        using boost::locale::format;
        using boost::locale::translate;
        if(count) {
            os << format(translate(
                  "{1} error", "{1} errors", count))
                  % count
                  ;
        }
        return os;
    }
};

std::ostream& operator<<(std::ostream& os, error_message const& err_msg) {
    return err_msg(os);
}

struct warning_message {
    std::size_t const count;
    explicit warning_message(std::size_t count_) : count{ count_ } { }
    std::ostream& operator()(std::ostream& os) const {
        using boost::locale::format;
        using boost::locale::translate;
        if(count) {
            os << format(translate(
                  "{1} warning", "{1} warnings", count))
                  % count
                  ;
        }
        return os;
    }
};

std::ostream& operator<<(std::ostream& os, warning_message const& warn_msg) {
    return warn_msg(os);
}

} // namespace detail


std::ostream& failure_status::operator()(std::ostream& os) const
{
    using detail::warning_message;
    using detail::error_message;
    using boost::locale::translate;

    bool const any_failure = [&] {
        return ctx.error_count || ctx.warning_count;
    }();

    // FixMe: complicated for the translator, see https://wandbox.org/permlink/lgU6DK75axnthjWz
    if(any_failure) {
        os << error_message(ctx.error_count)
           << (ctx.warning_count ? translate(" and ") : translate("")) // same type req.!
           << warning_message(ctx.warning_count)
           << translate(" generated.")
           ;
    }

    return os;
}


} } // namespace eda.vhdl


#if 0
// <yazmir8azyr>: https://wandbox.org/permlink/wGDqfmxCKwqob5mp

#include <iostream>
#include <boost/locale.hpp>
#include <type_traits>

struct context {

    std::size_t                                     error_count;
    std::size_t                                     warning_count;

    context()
    : error_count{ 0 }
    , warning_count{ 0 }
    { }
};


struct failure_status
{
    context const&                                  ctx;

    failure_status(context const& ctx_)
    : ctx{ ctx_ }
    { }

    std::ostream& operator()(std::ostream& os) const;
};

static inline
std::ostream& operator<<(std::ostream& os, failure_status const& status) {
    return status(os);
}

// --- C++ lambda helper ----
template <typename T>
struct A {
    T x;
    friend std::ostream& operator<<(std::ostream& os, A a) {
        a.x(os);
        return os;
     }
};

template <typename T>
A<std::decay_t<T>> make_iomanip_thing(T&& x) { return { std::forward<T>(x) }; }
// ----------------------------

std::ostream& failure_status::operator()(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    bool const any_failure = ctx.error_count || ctx.warning_count;

    auto error_message = [](size_t count) {
        return make_iomanip_thing([count](std::ostream& os) {
            if(count) {
                os << format(translate(
                      "{1} error", "{1} errors", count))
                      % count
                      ;
            }
        });
    };

    auto warning_message = [](size_t count) {
        return make_iomanip_thing([count](std::ostream& os) {
            if(count) {
                os << format(translate(
                      "{1} warning", "{1} warnings", count))
                      % count
                      ;
            }
        });
    };

    if(any_failure) {
        os << error_message(ctx.error_count)
           << (ctx.warning_count ? translate(" and ") : translate("")) // same type req.!
           << warning_message(ctx.warning_count)
           << translate(" generated.")
           ;
    }

    return os;
}

int main()
{
    context ctx;
    ctx.error_count = 1;
    ctx.warning_count = 42;

    std::cout << failure_status(ctx) << "\n";
}
#endif

