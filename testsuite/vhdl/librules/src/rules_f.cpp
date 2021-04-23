#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(factor_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_open_information_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(formal_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(function_call_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
