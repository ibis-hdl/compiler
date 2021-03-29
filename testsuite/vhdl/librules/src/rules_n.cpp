#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(next_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(numeric_literal_type, iterator_type, context_type);

}  // namespace eda::vhdl::parser
