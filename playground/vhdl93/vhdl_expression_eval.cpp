/*
 * vhdl_expression_eval.cpp
 *
 *  Created on: 24.05.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast.hpp>
#include <eda/vhdl93/ast_printer.hpp>

#include <eda/vhdl93/parser/expression_parse.hpp>

#include <eda/support/boost/hana_overload.hpp>

#include <boost/variant.hpp>

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>


/**
 * Readme 2018:
 *
 * This was just a Test of future work if the parser will be finished. Over time
 * things has been changed (and not valid any more) and I'm not sure if this
 * will compile today.
 *
 * Hence, this is here for educational purpose and the dependencies in the
 * project's source are removed.
 *
 * ----8< ----ast/literal.cpp ----8<----
 *
 * struct literal : variant<
 *    nullary,
 *    numeric_literal,
 *    enumeration_literal,
 *    string_literal,
 *    bit_string_literal,
 *    keyword_token          // NULL
 * >
 * {
 *    // FixMe: only playground/vhdl_expression_eval requires this!
 *    literal(literal const&) = default;
 *    literal& operator=(literal const&) = default;
 *
 *    using base_type::base_type;
 *    using base_type::operator=;
 * };
 *
 * ---->8-------->8-------->8-------->8----
 *
 * ----8< ----eda/vhdl/parser/expression_parse.hpp ----8<----
 *
 *  #include <eda/vhdl/ast/node/expression.hpp>
 *
 * namespace eda { namespace vhdl { namespace parser {
 *
 *     // quick&dirty API for expression parsing and evaluation
 *     bool parse(const std::string& file, ast::expression& exp);
 *
 * } } } // namespace eda.vhdl.parser
 *
 *
 * ---->8-------->8-------->8-------->8----
 *
 * ----8< ----vhdl/src/expression_parse.cpp ----8<----
 *
 * bool parse(const std::string& input, ast::expression& expression_)
 * {
 *     parser::iterator_type iter = input.begin();
 *     parser::iterator_type const end = input.end();
 *
 *     parser::error_handler_type error_handler(iter, end, std::cout);
 *
 *     auto const parser =
 *         x3::with<x3::error_handler_tag>(std::ref(error_handler))
 *         [
 *               parser::expression
 *         ];
 *
 *     bool success = false;
 *
 *     try {
 *         success = x3::phrase_parse(iter, end, parser, parser::skipper, expression_);
 *
 *         if (success) {
 *             if (iter != end) {
 *                 error_handler(iter, "Error! Expecting end of input here: ");
 *             }
 *             else {
 *                 // nothing
 *             }
 *         }
 *     } catch(x3::expectation_failure<parser::iterator_type> const& e) {
 *         error_handler(e.where(), "Error! Expecting " + e.which() + " here: ");
 *     }
 *
 *     return success;
 * }
 *
 * ---->8-------->8-------->8-------->8----
 */

namespace eda { namespace vhdl93 { namespace ast {



// http://www.vhdl.renerta.com/mobile/source/vhd00029.htm
struct expression_visitor: public boost::static_visitor<bool>
{
    std::ostream& os;

    typedef std::function<
        void(x3::position_tagged,
        std::string const& /* message */)
    >                                   error_handler_type;

    error_handler_type                  m_error_handler;

    using output_type = boost::variant<
        operator_token, int32_t
    >;

    using output_queue_type = std::vector<output_type>;

    output_queue_type                   m_output_queue;

    template <typename ErrorHandler>
    expression_visitor(ErrorHandler const& error_handler)
    : os{ std::cout }
    , m_error_handler(
            [&](x3::position_tagged pos, std::string const& msg)
            { error_handler(pos, msg); }
      )
    { }

    template<typename... T>
    result_type operator()(x3::variant<T...> const& variant) {
        return boost::apply_visitor(*this, variant);
    }

    template<typename T>
    result_type operator()(x3::forward_ast<T> const& fwd) {
        return (*this)(fwd.get());
    }

    result_type operator()(aggregate const& node);
    result_type operator()(attribute_designator const& node);
    result_type operator()(attribute_name const& node);
    result_type operator()(based_literal const& node);
    result_type operator()(bit_string_literal const& node);
    result_type operator()(character_literal const& node);
    result_type operator()(choices const& node);
    result_type operator()(decimal_literal const& node);
    result_type operator()(element_association const& node);
    result_type operator()(expression const& node);
    result_type operator()(factor const& node);
    result_type operator()(function_call const& node);
    result_type operator()(identifier const& node);
    result_type operator()(index_constraint const& node);
    result_type operator()(indexed_name const& node);
    result_type operator()(operator_symbol const& node);
    result_type operator()(physical_literal const& node);
    result_type operator()(qualified_expression const& node);
    result_type operator()(range_constraint const& node);
    result_type operator()(relation const& node);
    result_type operator()(selected_name const& node);
    result_type operator()(shift_expression const& node);
    result_type operator()(signature const& node);
    result_type operator()(simple_expression const& node);
    result_type operator()(simple_name const& node);
    result_type operator()(slice_name const& node);
    result_type operator()(string_literal const& node);
    result_type operator()(subtype_indication const& node);
    result_type operator()(term const& node);
    result_type operator()(type_conversion const& node);
    result_type operator()(type_mark const& node);

    result_type operator()(keyword_token token);
    result_type operator()(nullary const&);

    output_queue_type const& output_queue() {
        return m_output_queue;
    }

    void output_queue(operator_token token) {
        m_output_queue.emplace_back(token);
    }

    template<typename Type>
    void output_queue(Type const& object) {
        m_output_queue.emplace_back(object);
    }
};


expression_visitor::result_type expression_visitor::operator()(expression const& node)
{
    if(!(*this)(node.relation)) {
        return false;
    }

    for(auto const& chunk : node.rest_list) {

        if(!(*this)(chunk.relation)) {
            return false;
        }

        // logical_operator ::= AND | OR | NAND | NOR | XOR | XNOR
        output_queue(chunk.logical_operator);
    }

    return true;
}


expression_visitor::result_type expression_visitor::operator()(relation const& node)
{
    if(!(*this)(node.shift_expression)) {
        return false;
    }

    if(node.rest.is_initialized()) {

        auto const& chunk = node.rest.get();

        if(!(*this)(chunk.shift_expression)) {
            return false;
        }
        output_queue(chunk.relational_operator);
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(shift_expression const& node)
{
    if(!(*this)(node.simple_expression)) {
        return false;
    }

    if(node.rest.is_initialized()) {

        auto const& chunk = node.rest.get();

        if(!(*this)(chunk.simple_expression)) {
            return false;
        }
        output_queue(chunk.shift_operator);
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(simple_expression const& node)
{
    if(!(*this)(node.term)) {
        return false;
    }

    if(node.sign.is_initialized()) { // optional

        auto const sign = node.sign.get();

        if(sign == ast::operator_token::SIGN_NEG) {
            output_queue(ast::operator_token::SIGN_NEG);
        }
        else {
            /* empty; skip positive sign */
        }
    }

    if(!node.rest_list.empty()) {
        for(auto const& chunk : node.rest_list) {

            if(!(*this)(chunk.term)) {
                return false;
            }

            output_queue(chunk.adding_operator);
        }
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(term const& node)
{
    if(!(*this)(node.factor)) {
        return false;
    }

    if(!node.rest_list.empty()) {
        for(auto const& chunk: node.rest_list) {

            if(!(*this)(chunk.factor)) {
                return false;
            }

            output_queue(chunk.multiplying_operator);
        }
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(factor const& node)
{
    util::visit_in_place(
        node,
        [this](ast::primary const &primary) {
            if(!(*this).operator()(primary)) {
                return false;
            }
        },
        [this](factor_unary_operation const &unary_function) {

            if(!(*this)(unary_function.primary)) {
                return false;
            }

            output_queue(unary_function.operator_);     // x ** y aka x^y
        },
        [this](factor_binary_operation const &binary_function) {

            if(!(*this)(binary_function.primary_lhs)) {
                return false;
            }
            if(!(*this)(binary_function.primary_rhs)) {
                return false;
            }

            output_queue(binary_function.operator_);    // ABS | NOT
        },
        [this](nullary const& null) {
            if(!(*this).operator()(null)) {
                return false;
            }
        }
    );
    return true;
}

expression_visitor::result_type expression_visitor::operator()(simple_name const& node)
{
    os << node.name;
    return true;
}

expression_visitor::result_type expression_visitor::operator()(identifier const& node)
{
    os << node.name;
    return true;
}

expression_visitor::result_type expression_visitor::operator()(decimal_literal const& node)
{
    output_queue(get<int32_t>(node));
    return true;
}

expression_visitor::result_type expression_visitor::operator()(based_literal const& node)
{
    os << node.base << "#"
       << node.number
       ;
    if(!node.exponent.empty()) {
        os << "#" << node.exponent;
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(physical_literal const& node)
{
    (*this)(node.literal);
    os << node.unit_name;
    return true;
}

expression_visitor::result_type expression_visitor::operator()(bit_string_literal const& node)
{
    using tag = bit_string_literal::tag;

    switch(node.hint) {
        case tag::bin: os << "BIN"; break;
        case tag::oct: os << "OCT"; break;
        case tag::hex: os << "HEX"; break;
        default:       os << "INVALID";
    }

    os << " " << node.literal;
    return true;
}

expression_visitor::result_type expression_visitor::operator()(character_literal const& node)
{
    os << "'" << node.literal << "'";
    return true;
}

expression_visitor::result_type expression_visitor::operator()(string_literal const& node)
{
    os << '"' << node.literal << '"';
    return true;
}

expression_visitor::result_type expression_visitor::operator()(operator_symbol const& node)
{
    os << node.literal;
    return true;
}

expression_visitor::result_type expression_visitor::operator()(selected_name const& node)
{
    os << "IMPLEMENT ME (selected_name)";
    return true;
}

expression_visitor::result_type expression_visitor::operator()(indexed_name const& node)
{
    os << "IMPLEMENT ME (indexed_name)";
    return true;
}

expression_visitor::result_type expression_visitor::operator()(slice_name const& node)
{
    os << "IMPLEMENT ME (slice_name)";
    return true;
}

expression_visitor::result_type expression_visitor::operator()(attribute_name const& node)
{
    os << "IMPLEMENT ME (attribute_name)";
    return true;
}

expression_visitor::result_type expression_visitor::operator()(function_call const& node)
{
    os << "IMPLEMENT ME (function_call)";
    return true;
}

/*----------------------------------------------------------------------------*/
expression_visitor::result_type expression_visitor::operator()(keyword_token token) {
    os << token;
    return true;
}

expression_visitor::result_type expression_visitor::operator()(nullary const&) {
    os << "\n*** WARNING: any AST variant node contains nullary ***\n";
    return false;
}


} } }  // namespace eda.vhdl93.ast



namespace eda { namespace vhdl93 { namespace ast {


struct expression_evaluator
{

    std::ostream& os;

    using rpn_type = boost::variant<
        operator_token, int32_t
    >;

    using result_type = int32_t;

    using stack_type = std::stack<result_type>;

    stack_type m_stack;


    expression_evaluator(std::ostream& os_)
    : os{os_}
    { }


    result_type operator()(std::vector<rpn_type> const& rpn_queue);

    void binary_function(operator_token token);
    void unary_function(operator_token token);
};


expression_evaluator::result_type expression_evaluator::operator()(std::vector<rpn_type> const& rpn_queue)
{
    for(auto const& e : rpn_queue) {
        os << e << " ";
    }
    os << "\n";

    for(auto const& v : rpn_queue) {
        util::visit_in_place(
            v,
            [this](int value) {
                m_stack.emplace(value);
            },
            [this](operator_token token) {
                switch(arity(token)) {
                case 2:
                    binary_function(token);
                    break;
                case 1:
                    unary_function(token);
                    break;
                default:
                    os << "\n*** ERROR: Unknown/wrong arity for operator " << token << " ***\n";
                }
            }
        );
    }

    if(m_stack.size() != 1) {
        os << "\n*** ERROR: result stack size != 1 ***\n";
        return 0;
    }

    return m_stack.top();
}

void expression_evaluator::binary_function(operator_token token)
{
    if( !(m_stack.size() >= 2) ) {
        os << "\n*** Wrong count of arguments on stack for binary function " << token << " ***\n";
        return;
    }

    auto rhs = m_stack.top();   m_stack.pop();
    auto lhs = m_stack.top();   m_stack.pop();

    using ast::operator_token;

    switch(token) {

        // miscellaneous_operator
        case operator_token::EXPONENT: {
            auto result = std::pow(lhs,  rhs);
            os << lhs << " ** " << rhs << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }

        // multiplying_operator
        case operator_token::MUL: {
            auto result = lhs * rhs;
            os << lhs << " * " << rhs << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }
        case operator_token::DIV: {
            auto result = lhs / rhs;
            os << lhs << " / " << rhs << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }

        // adding_operator
        case operator_token::ADD: {
            auto result = lhs + rhs;
            os << lhs << " + " << rhs << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }
        case operator_token::SUB: {
            auto result = lhs - rhs;
            os << lhs << " - " << rhs << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }
        default: {
            os << "\n*** binary function " << token << " not implemented ***\n";
        }
    }
}

void expression_evaluator::unary_function(operator_token token)
{
    if( !(m_stack.size() >= 1) ) {
        os << "\n*** Wrong count of arguments on stack for unary function " << token << " ***\n";
        return;
    }

    auto operand = m_stack.top();   m_stack.pop();

    using ast::operator_token;

    switch(token) {
        case operator_token::SIGN_POS: {
            auto result = operand;
            os << " +1 * " << operand << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }
        case operator_token::SIGN_NEG: {
            auto result = -operand;
            os << " -1 * " << operand << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }
        default: {
            os << "\n*** binary function " << token << " not implemented ***\n";
        }
    }
}



} } }  // namespace eda.vhdl93.ast



namespace x3 = boost::spirit::x3;
namespace ast = eda::vhdl93::ast;
namespace parser = eda::vhdl93::parser;


/* to avoid compile errors due to move_to traits of string_view, a mockup of
 * error handler is used. */
struct error_handler_mock
{
    std::ostream& os;

    error_handler_mock(std::ostream& os)
    : os{ os }
    { }

    void operator()(x3::position_tagged, std::string const& message) const
    {
        os << "Error at <unspecified>:\n";
        os << message << "\n";
    }
};


int main()
{

    for(std::string const str: {
           "4**2 * 3 - 3 + 8 / 4 / ( 1 + 1 )",
           "2 * (5 + 5)",
           "(5 + 5) * 2",
           "-3 * 2",
           "-3 + 2"
    }) {
      ast::expression expr;

      bool parse_ok = parser::parse(str, expr);

      std::cout << "parse '" << str << "': ";
      if (parse_ok) {
        std::cout << "succeeded:\n";

        error_handler_mock parser_error_handler{ std::cout };
        ast::expression_visitor visit{ parser_error_handler };
        if(!visit(expr)) {
            std::cout << "ERROR visiting expression!\nEnd.\n";
            return -1;
        }

        ast::expression_evaluator eval{ std::cout };
        auto result = eval(visit.output_queue());

        std::cout << "\nresult = " << result << "\n";
      } else {
        std::cout << "*** failed ***\n";
      }
    }

    return 0;
}
