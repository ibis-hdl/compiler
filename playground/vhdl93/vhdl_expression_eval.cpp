/*
 * vhdl_expression_eval.cpp
 *
 *  Created on: 24.05.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast.hpp>
#include <eda/vhdl93/ast_printer.hpp>

#include <eda/vhdl93/parser/parser_config.hpp>
#include <eda/vhdl93/parser/grammar_def.hpp>

#include <eda/support/boost/hana_overload.hpp>

#include <boost/variant.hpp>
#include <stack>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {



// http://www.vhdl.renerta.com/mobile/source/vhd00029.htm
struct expression_visitor: public boost::static_visitor<bool>
{
    std::ostream& os;
    ast::printer print;

    std::stack<operator_token>          m_operator_stack;

    using output_type = boost::variant<
        operator_token, int32_t
    >;

    using output_queue_type = std::vector<output_type>;

    output_queue_type                   m_output_queue;

    int_fast32_t m_subexpr_count{0};

    expression_visitor(std::ostream& os_) : os{os_}, print{os_} {
        print.verbose_symbol = true;
        print.verbose_variant = true;
    }

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

        // empty operator stack
        while(!m_operator_stack.empty()) {
            output_queue(m_operator_stack.top());
            m_operator_stack.pop();
        }

        if(m_subexpr_count != 0) {
            std::cerr << "\n*** WARNING: nested expression parenthesis mismatch ***\n";
        }

        return m_output_queue;
    }

    void eval_precedence(operator_token operator_);

    static inline bool is_expression(ast::primary const &primary) {

        return util::visit_in_place(
            primary,
            [](ast::nullary const&)             { return false; },
            [](ast::name const&)                { return false; },
            [](ast::literal const&)             { return false; },
            [](ast::aggregate const&)           { return false; },
            [](ast::function_call const&)       { return false; },
            [](ast::qualified_expression const&) { return false; },
            [](ast::type_conversion const&)     { return false; },
            [](ast::allocator const&)           { return false; },
            [](ast::expression const&)          { return true; }
        );
    };


    void output_queue(operator_token token) {
        /* avoid pushing expressions parentheses onto output queue. Further the
         * nested expressions (resp. the opening and closing parenthesis) are
         * counted for cross check with parser's AST for correctness. It's cheap
         * here and ensure sane pre-conditions on evaluation. */
        switch(token) {
            case operator_token::EXPR_BGN: {
                ++m_subexpr_count;
                break;
            }
            case operator_token::EXPR_END: {
                --m_subexpr_count;
                break;
            }
            default:
                m_output_queue.emplace_back(token);
        }
    }



    template<typename Type>
    void output_queue(Type const& object) {
        m_output_queue.emplace_back(object);
    }
};


expression_visitor::result_type expression_visitor::operator()(expression const& node)
{
    (*this)(node.relation);

    for(auto const& chunk : node.rest_list) {

        // logical_operator ::= AND | OR | NAND | NOR | XOR | XNOR
        eval_precedence(chunk.logical_operator);

        (*this)(chunk.relation);
    }

    return true;
}


expression_visitor::result_type expression_visitor::operator()(relation const& node)
{
    (*this)(node.shift_expression);

    if(node.rest.is_initialized()) {

        auto const& chunk = node.rest.get();

        // relational_operator ::=    = | /= | < | <= | > | >=
        eval_precedence(chunk.relational_operator);

        (*this)(chunk.shift_expression);
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(shift_expression const& node)
{
    (*this)(node.simple_expression);

    if(node.rest.is_initialized()) {

        auto const& chunk = node.rest.get();

        // shift_operator ::= SLL | SRL | SLA | SRA | ROL | ROR
        eval_precedence(chunk.shift_operator);

        (*this)(chunk.simple_expression);
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(simple_expression const& node)
{
    if(node.sign.is_initialized()) { // optional
        // sign ::= + | -
        eval_precedence(node.sign.get());
    }

    (*this)(node.term);

    if(!node.rest_list.empty()) {
        for(auto const& chunk : node.rest_list) {

            // adding_operator ::= + | - | &
            eval_precedence(chunk.adding_operator);

            (*this)(chunk.term);
        }
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(term const& node)
{
    (*this)(node.factor);

    if(!node.rest_list.empty()) {
        for(auto const& chunk: node.rest_list) {

            // multiplying_operator ::= * | / | MOD | REM
            eval_precedence(chunk.multiplying_operator);

            (*this)(chunk.factor);
        }
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(factor const& node)
{
    util::visit_in_place(
        node,
        [this](ast::primary const &primary) {

            bool const nested_expression = is_expression(primary);
            //if(nested_expression) { os << "Call of factor::expression\n"; }

            /* During parsing the information about the parentheses are
             * transformed into nested expressions (stored in factor's variant).
             * But this influences the precedence of operators. Hence, artificial
             * expression markers (aka parentheses) are injected. These are
             * filtered out by the Shunting Yard algorithm from the output
             * queue later. */
            if(nested_expression) { eval_precedence(operator_token::EXPR_BGN); }
            (*this).operator()(primary);
            if(nested_expression) { eval_precedence(operator_token::EXPR_END);}
        },
        [this](factor_unary_operation const &unary_function) {

            // x ** y aka x^y
            eval_precedence(unary_function.operator_);

            (*this)(unary_function.primary);
        },
        [this](factor_binary_operation const &binary_function) {
            (*this)(binary_function.primary_lhs);

            // ABS | NOT
            eval_precedence(binary_function.operator_);

            (*this)(binary_function.primary_rhs);
        },
        [this](nullary const& null) {
            (*this).operator()(null);
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
    //os << "push " << m_output_queue.back() << " output\n";
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
    os << "\n*** WARNING: any AST variant contains nullary ***\n";
    return false;
}

/*----------------------------------------------------------------------------*/
/*  Stack-based evaluation of expressions using Dijkstra Shunting-yard-Algorithm
 * base on [Infix to Postfix Notation](https://www.youtube.com/watch?v=rA0x7b4YiMI)
 * and evaluation:
 * [Evaluation of Postfix Expression](https://youtu.be/uh7fD8WiT28)
 */
void expression_visitor::eval_precedence(operator_token operator_)
{
    if(m_operator_stack.empty()) {
        //os << "push " << operator_ << " operator_stack\n";
        m_operator_stack.emplace(operator_);
    }
    else {
#if 1
        if(precedence(m_operator_stack.top()) < precedence(operator_)) {
            m_operator_stack.emplace(operator_);
        }
        else {
            output_queue(m_operator_stack.top());
            m_operator_stack.pop();
            m_operator_stack.emplace(operator_);
        }
#else
        os << "precedence: (" << m_operator_stack.top() << " >= " << logical_operator << ") = ";
        if(precedence(m_operator_stack.top()) >= precedence(logical_operator)) {
            os << "true\n";

            operator_token const op = m_operator_stack.top();
            os << "pop  " << op << " operator_stack\n";
            m_operator_stack.pop();

            os << "push " << op << " output\n";
            output_queue(op);

            os << "push " << logical_operator << " operator_stack\n";
            m_operator_stack.emplace(logical_operator);
        }
        else {
            os << "false\n";
            os << "pop  " << logical_operator << " operator_stack\n";
            m_operator_stack.emplace(logical_operator);
        }
#endif
    }
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


    expression_evaluator(std::ostream& os_) : os{os_}
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
                // get arity
                unsigned arity = 0;
                switch(token) {
                    case ast::operator_token::SIGN_NEG:
                        [[ falltrough]]
                    case ast::operator_token::SIGN_POS: {
                        arity = 1;
                        break;
                    }
                    default: {
                        arity = 2;
                    }
                }
                switch(arity) {
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
            os << " +" << operand << " = " << result << "\n";
            m_stack.emplace(result);
            break;
        }
        case operator_token::SIGN_NEG: {
            auto result = -operand;
            os << " -" << operand << " = " << result << "\n";
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


int main()
{

    for(std::string const str: {
           "4**2 * 3 - 3 + 8 / 4 / ( 1 + 1 )"
    }) {
      parser::iterator_type iter = str.begin(), end = str.end();
      ast::expression expr;

      parser::error_handler_type error_handler(iter, end, std::cout);

      auto const expr_parser =
          x3::with<x3::error_handler_tag>(std::ref(error_handler))
          [
           parser::expression
          ];

      bool parse_ok = x3::phrase_parse(iter, end, expr_parser, parser::skipper, expr);

      std::cout << "parse '" << str << "': ";
      if (parse_ok && iter == end) {
        std::cout << "succeeded:\n";
        ast::expression_visitor visit{std::cout};
        visit(expr);

        ast::expression_evaluator eval{std::cout};
        auto result = eval(visit.output_queue());

        std::cout << "\nresult = " << result << "\n";
      } else {
        std::cout << std::boolalpha
                  << "parse: " << parse_ok << "\n"
                  << "full:  " << (iter == end) << "\n";
        std::cout << "*** failed ***\n";
      }
    }

    return 0;
}
