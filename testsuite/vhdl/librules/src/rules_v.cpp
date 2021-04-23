#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(variable_assignment_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(variable_declaration_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
