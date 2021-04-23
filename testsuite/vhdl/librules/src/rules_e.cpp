#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(element_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(enumeration_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(exit_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(expression_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
