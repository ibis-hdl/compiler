/*
 * ctx.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/context.hpp>
#include <eda/utils/make_iomanip.hpp>

#include <iostream>

#include <eda/support/boost/locale.hpp>


namespace eda { namespace vhdl {


context::context()
: error_count{ 0 }
, warning_count{ 0 }
{ }



std::ostream& failure_status::operator()(std::ostream& os) const
{
    using boost::locale::translate;
    using boost::locale::format;

    auto const error_message = [](size_t count) {
        return utils::make_iomanip([count](std::ostream& os_) {
            if(count) {
                os_ << format(translate(
                        // warning: implicit conversion loses integer precision: 'const size_t'
                        // (aka 'const unsigned long') to 'int' [-Wshorten-64-to-32]
                       "{1} error", "{1} errors", static_cast<int>(count)))
                       % count
                       ;
            }
        });
    };

    auto const warning_message = [](size_t count) {
        return utils::make_iomanip([count](std::ostream& os_) {
            if(count) {
                os_ << format(translate(
                        // warning: implicit conversion loses integer precision: 'const size_t'
                        // (aka 'const unsigned long') to 'int' [-Wshorten-64-to-32]
                       "{1} warning", "{1} warnings", static_cast<int>(count)))
                       % count
                       ;
            }
        });
    };

    bool const any_failure = ctx.error_count || ctx.warning_count;
    bool const all_failure = ctx.error_count && ctx.warning_count;

    // FixMe: complicated for the translator, see https://wandbox.org/permlink/lgU6DK75axnthjWz
    if(any_failure) {
        os << error_message(ctx.error_count)
           << (all_failure ? translate(" and ") : translate("")) // same type req.!
           << warning_message(ctx.warning_count)
           << translate(" generated.")
           ;
    }

    return os;
}


} } // namespace eda.vhdl



#if 0
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

    bool const any_failure = ctx.error_count || ctx.warning_count;

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

#endif
