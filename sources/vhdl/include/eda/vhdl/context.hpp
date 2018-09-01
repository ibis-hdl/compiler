/*
 * context.hpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_

// clang-format off
#include <eda/vhdl/ast/util/string_span.hpp>
#include <eda/vhdl/ast/util/string_span_hash.hpp>

#include <cstddef>
#include <unordered_map>
#include <exception>
#include <limits>
#include <iosfwd>
// clang-format on


namespace eda { namespace vhdl {


namespace detail {

/**
 * Tagged Counter
 *
 * Simply increments events and throw basic_counter::overflow if a configurable
 * limit has been reached.
 *
 * \see [Wandbox](https://wandbox.org/permlink/7o4pPgrmHDQUJj1x)
 */
template<typename Tag>
class basic_counter
{
public:
    struct overflow: public std::exception { };

public:
    using value_type = std::size_t;

public:
    basic_counter(value_type limit_ = std::numeric_limits<value_type>::max())
    : treshold { limit_ }
    , value{ 0 }
    { }

public:
    basic_counter& operator++() {    // prefix ++
        ++value;
        if (value > treshold) {
            throw overflow{};
        }
        return *this;
    }

    basic_counter operator++(int) {  // postfix ++
        basic_counter result(*this);
        ++(*this);
        return result;
    }

    operator value_type() const {    // user-defined conversion
        return value;
    }

    value_type& limit() { return treshold; }
    value_type limit() const { return treshold; }

    std::ostream& print(std::ostream& os) const {
        os << value;
        return os;
    }

private:
    // clang-format off
    value_type                                      treshold;
    value_type                                      value;
    // clang-format on
};


template <typename Tag>
std::ostream& operator<<(std::ostream& os, basic_counter<Tag> const& counter) {
    return counter.print(os);
}

} // namespace detail


/**
 * The VHDL context used for analyze and elaboration
 *
 * The error_count will throw if the limit of errors is reached:
 * \code
 * try {
 *    ... // analyse
 * }
 * catch(context::error_counter::overflow const&) {
 *     std::cerr << "fatal error: too many errors emitted, stopping now "
 *               << "[-ferror-limit=]"
 *     // ...
 * }
 * \endcode
 */
class context
{
public:
    context();

public:
    using error_counter = detail::basic_counter<struct error_tag>;
    using warning_counter = detail::basic_counter<struct warning_tag>;

    error_counter                                   error_count;
    warning_counter                                 warning_count;

public:
    bool error_free() const {
        return error_count == 0;
    }

private:
    // clang-format off
    std::unordered_map<ast::string_span, int>       dummy;
    // clang-format on
};


/**
 * IO-manipulator to print the context error/warning status on ostream
 */
class failure_status
{
    // clang-format off
    context const&                                  ctx;
    // clang-format on

public:
    failure_status(context const& ctx_)
    : ctx{ ctx_ }
    { }

    std::ostream& print(std::ostream& os) const;
};


static inline
std::ostream& operator<<(std::ostream& os, failure_status const& status) {
    return status.print(os);
}


} } // namespace eda.vhdl



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_ */
