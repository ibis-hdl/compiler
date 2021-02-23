/*
 * rules.cpp
 *
 *  Created on: 14.06.2018
 *      Author: olaf
 */

#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda {
namespace vhdl {
namespace parser {

BOOST_SPIRIT_INSTANTIATE(secondary_unit_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(selected_signal_assignment_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(sequential_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(shift_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_assignment_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(simple_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(slice_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(string_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subprogram_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subprogram_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subtype_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subtype_indication_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda
