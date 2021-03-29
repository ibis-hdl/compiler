#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/node/file_open_information.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct file_declaration : position_tagged {
    ast::identifier_list identifier_list;
    ast::subtype_indication subtype_indication;
    optional<ast::file_open_information> file_open_information;
};

}  // namespace eda::vhdl::ast
