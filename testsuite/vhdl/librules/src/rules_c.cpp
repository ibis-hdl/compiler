#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(case_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(character_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(choices_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_configuration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_instantiation_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(concurrent_assertion_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(conditional_signal_assignment_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(configuration_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(configuration_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constant_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constrained_array_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(context_clause_type, iterator_type, context_type);

}  // namespace eda::vhdl::parser
