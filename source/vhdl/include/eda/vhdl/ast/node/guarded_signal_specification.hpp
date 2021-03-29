#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/signal_list.hpp>
#include <eda/vhdl/ast/node/name.hpp>

namespace eda::vhdl::ast {

struct guarded_signal_specification : position_tagged {
    ast::signal_list guarded_signal_list;
    ast::name type_mark;
};

}  // namespace eda::vhdl::ast
