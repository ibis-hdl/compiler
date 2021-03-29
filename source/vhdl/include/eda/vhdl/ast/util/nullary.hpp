#pragma once

namespace eda::vhdl::ast {

/**
 * helper class to catch an 'empty' variant. C++ variant ensures a never empty
 * guarantee which isn't always desirable.
 */
struct nullary {
};

}  // namespace eda::vhdl::ast
