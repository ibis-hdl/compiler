#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {
BOOST_SPIRIT_INSTANTIATE(generate_statement_type, iterator_type, context_type);

BOOST_SPIRIT_INSTANTIATE(generic_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generic_map_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_template_declaration_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
