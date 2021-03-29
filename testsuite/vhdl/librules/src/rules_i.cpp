#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(identifier_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(identifier_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(if_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(index_constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(index_subtype_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(indexed_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(integer_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_constant_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_signal_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_variable_declaration_type, iterator_type, context_type);

}  // namespace eda::vhdl::parser
