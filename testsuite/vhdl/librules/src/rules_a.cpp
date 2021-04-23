#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

BOOST_SPIRIT_INSTANTIATE(abstract_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(actual_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(aggregate_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(alias_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(allocator_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(architecture_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(assertion_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(association_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(attribute_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(attribute_specification_type, iterator_type, context_type);

}  // namespace ibis::vhdl::parser
