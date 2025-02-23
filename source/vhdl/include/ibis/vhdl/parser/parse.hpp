//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

// #include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>

#include <exception>
#include <iosfwd>
#include <string_view>
#include <string>
#include <vector>

namespace ibis::vhdl::ast {
struct design_unit;
using design_file = std::vector<ast::design_unit>;  // FixMe not clever, include <.../ast.hpp>
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::parser {

class parse {
public:
    using iterator_type = vhdl::parser::iterator_type;
    using position_cache_type = position_cache<iterator_type>;
    using current_file_type = ibis::util::file_mapper::current_file;
    using vhdl_context_type = parser::context;

public:
    ///
    /// Construct a new parse object.
    ///
    /// @param os_ Output stream for messages.
    ///
    parse(std::ostream& os_)
        : os{ os_ }
    {
    }

    ///
    /// Functor to call parse implementation.
    ///
    /// @param current_file file_mapper proxy with current_file context
    /// @param position_cache position_cache with the file contents to be parsed.
    /// @param vhdl_ctx The context used to parse and others.
    /// @param design_file AST node of input/file contents.
    /// @return true success.
    /// @return false failure.
    ///
    /// @todo Get rid off the skipper, embed it into own rule and new start
    /// rule, see e.g. [Best practice for boost spirit context-dependent grammar rule](
    /// https://stackoverflow.com/questions/66963381/best-practice-for-boost-spirit-context-dependent-grammar-rule)
    /// X3: Function Composition.
    ///
    /// @todo Limit the use of `x3::rule<>`, following [Spirit X3, How to get attribute type to
    /// match rule type?](
    /// https://stackoverflow.com/questions/56819120/spirit-x3-how-to-get-attribute-type-to-match-rule-type/56824271#56824271)
    /// this is only required if you have recursive rules or need external linkage
    /// on rules (define them in separate translation units).
    ///
    bool operator()(current_file_type&& current_file, position_cache_type& position_cache,
                    vhdl_context_type& vhdl_ctx, ast::design_file& design_file) const;

private:
    static std::string make_exception_description(std::exception const& exception,
                                                  std::string_view filename);

    static std::string make_exception_description(std::string_view filename);

private:
    std::ostream& os;
};

}  // namespace ibis::vhdl::parser
