#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(decimal_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(disconnection_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(discrete_range_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
