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

    std::stack<operator_token>          operator_stack;

    using output_type = boost::variant<
        operator_token, int32_t
    >;
    std::vector<output_type>            output_queue;

    unsigned expr_count{0};

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

    void output(operator_token token) {
        /* avoid pushing expressions braces onto output queue */
        switch(token) {
            case operator_token::EXPR_BGN:
                [[fallthrough]];
            case operator_token::EXPR_END: {
                break;
                }
            default:
                output_queue.emplace_back(token);
        }
    }

    template<typename Type>
    void output(Type const& object) {
        output_queue.emplace_back(object);
    }
};


expression_visitor::result_type expression_visitor::operator()(expression const& node)
{
    (*this)(node.relation);

    for(auto const& chunk : node.rest_list) {
        os << " " << chunk.operator_ << " ";
        (*this)(chunk.relation);
    }

    return true;
}


expression_visitor::result_type expression_visitor::operator()(relation const& node)
{
    (*this)(node.shift_expression);

    if(node.rest.is_initialized()) {
        auto const& chunk = node.rest.get();
        os << " " << chunk.operator_ << " ";
        (*this)(chunk.shift_expression);
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(shift_expression const& node)
{
    (*this)(node.simple_expression);

    if(node.rest.is_initialized()) {
        auto const& chunk = node.rest.get();
        os << " " << chunk.operator_ << " ";
        (*this)(chunk.simple_expression);
    }
    return true;
}

expression_visitor::result_type expression_visitor::operator()(simple_expression const& node)
{
    if(node.sign.is_initialized()) { // optional
        eval_precedence(node.sign.get());
    }

    (*this)(node.term);

    if(!node.rest_list.empty()) {
        for(auto const& chunk : node.rest_list) {
            eval_precedence(chunk.operator_);
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
            eval_precedence(chunk.operator_);
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
            if(nested_expression) { os << "Call of factor::expression\n"; }

            if(nested_expression) { eval_precedence(operator_token::EXPR_BGN); }
            (*this).operator()(primary);
            if(nested_expression) { eval_precedence(operator_token::EXPR_END);}
        },
        [this](factor_unary_operation const &unary_function) {

            eval_precedence(unary_function.operator_);

            (*this)(unary_function.primary);
        },
        [this](factor_binary_operation const &binary_function) {
            (*this)(binary_function.primary_lhs);

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
    output(get<int32_t>(node));
    os << "push " << output_queue.back() << " output\n";
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
//  Stack-based evaluation of expressions using Dijkstra Shunting-yard-Algorithm
void expression_visitor::eval_precedence(operator_token operator_)
{
    if(operator_stack.empty()) {
        os << "push " << operator_ << " operator_stack\n";
        operator_stack.emplace(operator_);
    }
    else {
        os << "precedence: (" << operator_stack.top() << " >= " << operator_ << ") = ";
        if(precedence(operator_stack.top()) >= precedence(operator_)) {
            os << "true\n";

            operator_token const op = operator_stack.top();
            os << "pop  " << op << " operator_stack\n";
            operator_stack.pop();

            os << "push " << op << " output\n";
            output(op);

            os << "push " << operator_ << " operator_stack\n";
            operator_stack.emplace(operator_);
        }
        else {
            os << "false\n";
            os << "pop  " << operator_ << " operator_stack\n";
            operator_stack.emplace(operator_);
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
        ast::expression_visitor eval{std::cout};
        eval(expr);

        // empty operator stack
        while(!eval.operator_stack.empty()) {
            eval.output(eval.operator_stack.top());
            eval.operator_stack.pop();
        }
        std::cout << "RPN Stack:\n";
        for(auto const& e : eval.output_queue) {
            std::cout << e << " ";
        }
        std::cout << "\n";
      } else {
        std::cout << std::boolalpha
                  << "parse: " << parse_ok << "\n"
                  << "full:  " << (iter == end) << "\n";
        std::cout << "*** failed ***\n";
      }
    }
}
