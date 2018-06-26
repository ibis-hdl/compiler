/*
 * context.hpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_


#include <eda/vhdl/ast/util/string_span.hpp>
#include <eda/vhdl/ast/util/string_span_hash.hpp>

#include <unordered_map>
#include <iosfwd>


namespace eda { namespace vhdl {


/**
 * The VHDL context used for analyze and elaboration
 */
struct context {

    std::size_t                                     error_count;
    std::size_t                                     warning_count;

    std::unordered_map<ast::string_span, int>       dummy;

    context();
};


/**
 * IO-manipulator to print the context error/warning status on ostream
 */
class failure_status
{
    context const&                                  ctx;

public:
    failure_status(context const& ctx_)
    : ctx{ ctx_ }
    { }

    std::ostream& operator()(std::ostream& os) const;
};


static inline
std::ostream& operator<<(std::ostream& os, failure_status const& status) {
    return status(os);
}


} } // namespace eda.vhdl



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_ */
