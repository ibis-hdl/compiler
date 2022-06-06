//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/block_statement.hpp>
#include <ibis/vhdl/ast/node/process_statement.hpp>
#include <ibis/vhdl/ast/node/concurrent_procedure_call_statement.hpp>
#include <ibis/vhdl/ast/node/concurrent_assertion_statement.hpp>
#include <ibis/vhdl/ast/node/concurrent_signal_assignment_statement.hpp>
#include <ibis/vhdl/ast/node/component_instantiation_statement.hpp>
#include <ibis/vhdl/ast/node/generate_statement.hpp>

namespace ibis::vhdl::ast {

struct concurrent_statement
    : variant<ast::nullary,                                 // --
              ast::block_statement,                         // --
              ast::process_statement,                       // --
              ast::concurrent_procedure_call_statement,     // --
              ast::concurrent_assertion_statement,          // --
              ast::concurrent_signal_assignment_statement,  // --
              ast::component_instantiation_statement,       // --
              ast::generate_statement                       // --
              > {
    // Note, concurrent_statement is forwarded due to cyclic dependency at
    // block_statement_part. Since x3::variant has move constructor defined,
    // the copy constructor is implicit deleted, see
    // [Rule-of-Three becomes Rule-of-Five with C++11?](
    //  https://stackoverflow.com/questions/4782757/rule-of-three-becomes-rule-of-five-with-c11?answertab=active#tab-top).
    // Here we bring the compiler generated back and supply specific assign
    // operator= required to this variant - copy&paste from x3::variant.
    concurrent_statement() = default;
    ~concurrent_statement() = default;

    concurrent_statement(concurrent_statement const&) = default;
    concurrent_statement& operator=(concurrent_statement const&) = default;

    concurrent_statement(concurrent_statement&&) = default;
    concurrent_statement& operator=(concurrent_statement&&) = default;

    template <typename T, class = non_self_t<T>>
    concurrent_statement& operator=(T const& rhs)
        BOOST_NOEXCEPT_IF((std::is_nothrow_assignable<variant_type, T const&>{}))
    {
        var = rhs;
        return *this;
    }

    template <typename T, class = non_self_t<T>>
    concurrent_statement& operator=(T&& rhs)
        BOOST_NOEXCEPT_IF((std::is_nothrow_assignable<variant_type, T&&>::value))
    {
        var = std::forward<T>(rhs);
        return *this;
    }
};

}  // namespace ibis::vhdl::ast
