#include <eda/vhdl/ast.hpp>
#include "testing_parser_def.hpp"


namespace testsuite {

    using attribute_type = ast::case_statement;
    using parser_type = parser::case_statement_type;

    // Explicit Template Instantiation
    template
    std::tuple<bool, std::string>
    testing_parser<attribute_type>::operator()(std::string const &, parser_type const&, bool);
}
