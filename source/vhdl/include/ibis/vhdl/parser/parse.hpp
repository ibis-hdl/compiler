//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/parser/context.hpp>

#include <iosfwd>
#include <string>
#include <string_view>
#include <exception>

namespace ibis::vhdl::ast {
struct design_unit;
using design_file = std::vector<ast::design_unit>;
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::parser {

class parse {
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
    /// @param position_cache_proxy Proxy of position_cache with the file contents to be parsed.
    /// @param ctx The context used to parse and others.
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
    bool operator()(position_cache<parser::iterator_type>::proxy& position_cache_proxy,
                    parser::context& ctx, ast::design_file& design_file);

private:
    static std::string make_exception_description(std::exception const& exception,
                                                  std::string_view filename);

    static std::string make_exception_description(std::string_view filename);

private:
    std::ostream& os;
};

}  // namespace ibis::vhdl::parser
