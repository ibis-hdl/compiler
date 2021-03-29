#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(decimal_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(disconnection_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(discrete_range_type, iterator_type, context_type);

}  // namespace eda::vhdl::parser
