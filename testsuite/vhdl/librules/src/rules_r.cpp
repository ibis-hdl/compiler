#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(range_constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(record_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(relation_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(return_statement_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
