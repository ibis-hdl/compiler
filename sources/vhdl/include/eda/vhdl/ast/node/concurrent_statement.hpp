/*
 * concurrent_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_STATEMENT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/block_statement.hpp>
#include <eda/vhdl/ast/node/process_statement.hpp>
#include <eda/vhdl/ast/node/concurrent_procedure_call_statement.hpp>
#include <eda/vhdl/ast/node/concurrent_assertion_statement.hpp>
#include <eda/vhdl/ast/node/concurrent_signal_assignment_statement.hpp>
#include <eda/vhdl/ast/node/component_instantiation_statement.hpp>
#include <eda/vhdl/ast/node/generate_statement.hpp>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_statement : variant<
    ast::nullary,
    ast::block_statement,
    ast::process_statement,
    ast::concurrent_procedure_call_statement,
    ast::concurrent_assertion_statement,
    ast::concurrent_signal_assignment_statement,
    ast::component_instantiation_statement,
    ast::generate_statement
>
{
    /* Note, concurrent_statement is forwarded due to cyclic dependency at
     * block_statement_part. Since x3::variant has move constructor defined,
     * the copy constructor is implicit deleted, see
     * [Rule-of-Three becomes Rule-of-Five with C++11?](
     *  https://stackoverflow.com/questions/4782757/rule-of-three-becomes-rule-of-five-with-c11?answertab=active#tab-top).
     * Here we bring the compiler generated back and supply specific assign
     * operator= required to this variant - copy&paste from x3::variant.  */
    concurrent_statement() = default;
    ~concurrent_statement() = default;

    concurrent_statement(concurrent_statement const&) = default;
    concurrent_statement& operator=(concurrent_statement const&) = default;

    concurrent_statement(concurrent_statement&&) = default;
    concurrent_statement& operator=(concurrent_statement&&) = default;

    template <typename T, class = non_self_t<T>>
    concurrent_statement& operator=(T const& rhs) BOOST_NOEXCEPT_IF((std::is_nothrow_assignable<variant_type, T const&>{}))
    {
        var = rhs;
        return *this;
    }

    template <typename T, class = non_self_t<T>>
    concurrent_statement& operator=(T&& rhs) BOOST_NOEXCEPT_IF((std::is_nothrow_assignable<variant_type, T&&>::value))
    {
        var = std::forward<T>(rhs);
        return *this;
    }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_STATEMENT_HPP_ */
