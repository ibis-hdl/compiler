#include <eda/vhdl/parser/grammar.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda::vhdl::parser {

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_INSTANTIATE(design_file_type, iterator_type, context_type);
#endif

parser::design_file_type const& grammar() { return eda::vhdl::parser::design_file; }

}  // namespace eda::vhdl::parser
