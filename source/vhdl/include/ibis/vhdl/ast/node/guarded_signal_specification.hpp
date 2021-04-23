#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/signal_list.hpp>
#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct guarded_signal_specification : position_tagged {
    ast::signal_list guarded_signal_list;
    ast::name type_mark;
};

}  // namespace ibis::vhdl::ast
