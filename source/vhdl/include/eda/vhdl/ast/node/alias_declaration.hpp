#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/alias_designator.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/signature.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct alias_declaration : position_tagged {
    ast::alias_designator alias_designator;
    optional<ast::subtype_indication> subtype_indication;
    ast::name name;
    optional<ast::signature> signature;
};

}  // namespace eda::vhdl::ast
