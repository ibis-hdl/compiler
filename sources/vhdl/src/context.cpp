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
        os << error_message(ctx.error_count);
        if(ctx.warning_count) {
            os << translate(" and ");
        }
        os << warning_message(ctx.warning_count);
        os << translate(" generated.");
    }

    return os;
}


} } // namespace eda.vhdl

