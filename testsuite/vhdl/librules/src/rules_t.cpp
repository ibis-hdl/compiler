#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(type_conversion_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_definition_type, iterator_type, context_type);

}  // namespace eda::vhdl::parser
