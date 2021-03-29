#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(wait_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(waveform_type, iterator_type, context_type);

}  // namespace eda::vhdl::parser
