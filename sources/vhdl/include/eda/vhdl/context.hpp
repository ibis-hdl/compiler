/*
 * context.hpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_CONTEXT_HPP_


#include <eda/vhdl/parser/common_types.hpp>

#include <boost/range/iterator_range.hpp>

#include <unordered_map>
#include <iosfwd>


namespace eda { namespace vhdl { namespace ast {

/* AST nodes holds string_span type as (iterator) references to the
 * file buffer.
 * FixMe: Make these type globally, it's used every where and scattered
 * around in different files, e.g. AST nodes, grammar_type, ... Maybe
 * once a day it can be replaced by std::string_view if Spirit.X3 support
 * it. */
using string_span = boost::iterator_range<parser::iterator_type>;

}}}


namespace std {

template<>
struct hash<eda::vhdl::ast::string_span>
{
    size_t operator()(eda::vhdl::ast::string_span const& range) const noexcept {
        //static_assert(std::string_view::value_type == range::value_type);
        /* FixMe: This hash calculation isn't performant. The problem behind:
         * in general, an iterator can't be converted to a pointer. */
        return std::hash<std::string>()(std::string(range.begin(), range.end()));
    }
};

} // namespace std


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