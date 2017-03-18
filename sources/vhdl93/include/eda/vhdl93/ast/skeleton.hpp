/*
 * abstract_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct based_literal;
struct decimal_literal;

struct abstract_literal :
    x3::variant<
        x3::forward_ast<based_literal>,
        x3::forward_ast<decimal_literal>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_ */


/*
 * access_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACCESS_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACCESS_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct access;
struct subtype_indication;

struct access_type_definition : x3::position_tagged
{
    access              access;             
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, access_type_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACCESS_TYPE_DEFINITION_HPP_ */


/*
 * actual_designator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_DESIGNATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct file_name;
struct open;
struct signal_name;
struct variable_name;

struct actual_designator :
    x3::variant<
        x3::forward_ast<expression>,
        x3::forward_ast<file_name>,
        x3::forward_ast<open>,
        x3::forward_ast<signal_name>,
        x3::forward_ast<variable_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_DESIGNATOR_HPP_ */


/*
 * actual_parameter_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PARAMETER_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PARAMETER_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct parameter_association_list;

struct actual_parameter_part : x3::position_tagged
{
    parameter_association_listparameter_association_list;
};


std::ostream& operator<<(std::ostream& os, actual_parameter_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PARAMETER_PART_HPP_ */


/*
 * actual_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct actual_designator;
struct function_name;
struct type_mark;

struct actual_part :
    x3::variant<
        x3::forward_ast<actual_designator>,
        x3::forward_ast<function_name>,
        x3::forward_ast<type_mark>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PART_HPP_ */


/*
 * aggregate.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_AGGREGATE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_AGGREGATE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct element_association;

struct aggregate : x3::position_tagged
{
    element_association element_association;
};


std::ostream& operator<<(std::ostream& os, aggregate const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_AGGREGATE_HPP_ */


/*
 * alias_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias;
struct alias_designator;
struct is;
struct name;
struct signature;
struct subtype_indication;

struct alias_declaration : x3::position_tagged
{
    alias               alias;              
    alias_designator    alias_designator;   
    is                  is;                 
    name                name;               
    signature           signature;          
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, alias_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DECLARATION_HPP_ */


/*
 * alias_designator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DESIGNATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct character_literal;
struct identifier;
struct operator_symbol;

struct alias_designator :
    x3::variant<
        x3::forward_ast<character_literal>,
        x3::forward_ast<identifier>,
        x3::forward_ast<operator_symbol>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DESIGNATOR_HPP_ */


/*
 * allocator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALLOCATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALLOCATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct new;
struct qualified_expression;
struct subtype_indication;

struct allocator :
    x3::variant<
        x3::forward_ast<new>,
        x3::forward_ast<qualified_expression>,
        x3::forward_ast<subtype_indication>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALLOCATOR_HPP_ */


/*
 * architecture_body.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_BODY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_BODY_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct architecture;
struct architecture_declarative_part;
struct architecture_simple_name;
struct architecture_statement_part;
struct begin;
struct end;
struct entity_name;
struct identifier;
struct is;
struct of;

struct architecture_body : x3::position_tagged
{
    architecture        architecture;       
    architecture_declarative_partarchitecture_declarative_part;
    architecture_simple_namearchitecture_simple_name;
    architecture_statement_partarchitecture_statement_part;
    begin               begin;              
    end                 end;                
    entity_name         entity_name;        
    identifier          identifier;         
    is                  is;                 
    of                  of;                 
};


std::ostream& operator<<(std::ostream& os, architecture_body const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_BODY_HPP_ */


/*
 * architecture_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct block_declarative_item;

struct architecture_declarative_part : x3::position_tagged
{
    block_declarative_itemblock_declarative_item;
};


std::ostream& operator<<(std::ostream& os, architecture_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_DECLARATIVE_PART_HPP_ */


/*
 * architecture_statement_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_STATEMENT_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct concurrent_statement;

struct architecture_statement_part : x3::position_tagged
{
    concurrent_statementconcurrent_statement;
};


std::ostream& operator<<(std::ostream& os, architecture_statement_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_STATEMENT_PART_HPP_ */


/*
 * array_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARRAY_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARRAY_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct constrained_array_definition;
struct unconstrained_array_definition;

struct array_type_definition :
    x3::variant<
        x3::forward_ast<constrained_array_definition>,
        x3::forward_ast<unconstrained_array_definition>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARRAY_TYPE_DEFINITION_HPP_ */


/*
 * assertion.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct assert;
struct condition;
struct expression;
struct report;
struct severity;

struct assertion : x3::position_tagged
{
    assert              assert;             
    condition           condition;          
    expression          expression;         
    report              report;             
    severity            severity;           
};


std::ostream& operator<<(std::ostream& os, assertion const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_HPP_ */


/*
 * assertion_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct assertion;
struct label;

struct assertion_statement : x3::position_tagged
{
    assertion           assertion;          
    label               label;              
};


std::ostream& operator<<(std::ostream& os, assertion_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_STATEMENT_HPP_ */


/*
 * association_element.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_ELEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_ELEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct actual_part;
struct formal_part;

struct association_element : x3::position_tagged
{
    actual_part         actual_part;        
    formal_part         formal_part;        
};


std::ostream& operator<<(std::ostream& os, association_element const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_ELEMENT_HPP_ */


/*
 * association_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct association_element;

struct association_list : x3::position_tagged
{
    association_element association_element;
};


std::ostream& operator<<(std::ostream& os, association_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_LIST_HPP_ */


/*
 * attribute_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute;
struct identifier;
struct type_mark;

struct attribute_declaration : x3::position_tagged
{
    attribute           attribute;          
    identifier          identifier;         
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, attribute_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DECLARATION_HPP_ */


/*
 * attribute_designator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DESIGNATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute_simple_name;

struct attribute_designator : x3::position_tagged
{
    attribute_simple_nameattribute_simple_name;
};


std::ostream& operator<<(std::ostream& os, attribute_designator const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DESIGNATOR_HPP_ */


/*
 * attribute_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute_designator;
struct expression;
struct prefix;
struct signature;

struct attribute_name : x3::position_tagged
{
    attribute_designatorattribute_designator;
    expression          expression;         
    prefix              prefix;             
    signature           signature;          
};


std::ostream& operator<<(std::ostream& os, attribute_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_NAME_HPP_ */


/*
 * attribute_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute;
struct attribute_designator;
struct entity_specification;
struct expression;
struct is;
struct of;

struct attribute_specification : x3::position_tagged
{
    attribute           attribute;          
    attribute_designatorattribute_designator;
    entity_specificationentity_specification;
    expression          expression;         
    is                  is;                 
    of                  of;                 
};


std::ostream& operator<<(std::ostream& os, attribute_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_SPECIFICATION_HPP_ */


/*
 * base.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct integer;

struct base : x3::position_tagged
{
    integer             integer;            
};


std::ostream& operator<<(std::ostream& os, base const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_HPP_ */


/*
 * base_specifier.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_SPECIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_SPECIFIER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct B;
struct O;
struct X;

struct base_specifier :
    x3::variant<
        x3::forward_ast<B>,
        x3::forward_ast<O>,
        x3::forward_ast<X>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_SPECIFIER_HPP_ */


/*
 * base_unit_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_UNIT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_UNIT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;

struct base_unit_declaration : x3::position_tagged
{
    identifier          identifier;         
};


std::ostream& operator<<(std::ostream& os, base_unit_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASE_UNIT_DECLARATION_HPP_ */


/*
 * based_integer.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_INTEGER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_INTEGER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct extended_digit;
struct underline;

struct based_integer : x3::position_tagged
{
    extended_digit      extended_digit;     
    underline           underline;          
};


std::ostream& operator<<(std::ostream& os, based_integer const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_INTEGER_HPP_ */


/*
 * based_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct base;
struct based_integer;
struct exponent;

struct based_literal : x3::position_tagged
{
    base                base;               
    based_integer       based_integer;      
    exponent            exponent;           
};


std::ostream& operator<<(std::ostream& os, based_literal const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_ */


/*
 * basic_character.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_CHARACTER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_CHARACTER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct basic_graphic_character;
struct format_effector;

struct basic_character :
    x3::variant<
        x3::forward_ast<basic_graphic_character>,
        x3::forward_ast<format_effector>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_CHARACTER_HPP_ */


/*
 * basic_graphic_character.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_GRAPHIC_CHARACTER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_GRAPHIC_CHARACTER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct digit;
struct space_character;
struct special_character|;
struct upper_case_letter;

struct basic_graphic_character :
    x3::variant<
        x3::forward_ast<digit>,
        x3::forward_ast<space_character>,
        x3::forward_ast<special_character|>,
        x3::forward_ast<upper_case_letter>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_GRAPHIC_CHARACTER_HPP_ */


/*
 * basic_identifier.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_IDENTIFIER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct letter;
struct letter_or_digit;
struct underline;

struct basic_identifier : x3::position_tagged
{
    letter              letter;             
    letter_or_digit     letter_or_digit;    
    underline           underline;          
};


std::ostream& operator<<(std::ostream& os, basic_identifier const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASIC_IDENTIFIER_HPP_ */


/*
 * binding_indication.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINDING_INDICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINDING_INDICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_aspect;
struct generic_map_aspect;
struct port_map_aspect;
struct use;

struct binding_indication : x3::position_tagged
{
    entity_aspect       entity_aspect;      
    generic_map_aspect  generic_map_aspect; 
    port_map_aspect     port_map_aspect;    
    use                 use;                
};


std::ostream& operator<<(std::ostream& os, binding_indication const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINDING_INDICATION_HPP_ */


/*
 * bit_string_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct base_specifier;
struct bit_value;

struct bit_string_literal : x3::position_tagged
{
    base_specifier      base_specifier;     
    bit_value           bit_value;          
};


std::ostream& operator<<(std::ostream& os, bit_string_literal const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_ */


/*
 * bit_value.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_VALUE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_VALUE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct extended_digit;
struct underline;

struct bit_value : x3::position_tagged
{
    extended_digit      extended_digit;     
    underline           underline;          
};


std::ostream& operator<<(std::ostream& os, bit_value const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_VALUE_HPP_ */


/*
 * block_configuration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_CONFIGURATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_CONFIGURATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct block_specification;
struct configuration_item;
struct end;
struct for;
struct use_clause;

struct block_configuration : x3::position_tagged
{
    block_specification block_specification;
    configuration_item  configuration_item; 
    end                 end;                
    for                 for;                
    use_clause          use_clause;         
};


std::ostream& operator<<(std::ostream& os, block_configuration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_CONFIGURATION_HPP_ */


/*
 * block_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct attribute_declaration;
struct attribute_specification;
struct component_declaration;
struct configuration_specification;
struct constant_declaration;
struct disconnection_specification;
struct file_declaration;
struct group_declaration;
struct group_template_declaration;
struct shared_variable_declaration;
struct signal_declaration;
struct subprogram_body;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;
struct use_clause;

struct block_declarative_item :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<attribute_declaration>,
        x3::forward_ast<attribute_specification>,
        x3::forward_ast<component_declaration>,
        x3::forward_ast<configuration_specification>,
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<disconnection_specification>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<shared_variable_declaration>,
        x3::forward_ast<signal_declaration>,
        x3::forward_ast<subprogram_body>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>,
        x3::forward_ast<use_clause>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_DECLARATIVE_ITEM_HPP_ */


/*
 * block_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct block_declarative_item;

struct block_declarative_part : x3::position_tagged
{
    block_declarative_itemblock_declarative_item;
};


std::ostream& operator<<(std::ostream& os, block_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_DECLARATIVE_PART_HPP_ */


/*
 * block_header.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_HEADER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_HEADER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct generic_clause;
struct generic_map_aspect;
struct port_clause;
struct port_map_aspect;

struct block_header : x3::position_tagged
{
    generic_clause      generic_clause;     
    generic_map_aspect  generic_map_aspect; 
    port_clause         port_clause;        
    port_map_aspect     port_map_aspect;    
};


std::ostream& operator<<(std::ostream& os, block_header const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_HEADER_HPP_ */


/*
 * block_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct architecture_name;
struct block_statement_label;
struct generate_statement_label;
struct index_specification;

struct block_specification :
    x3::variant<
        x3::forward_ast<architecture_name>,
        x3::forward_ast<block_statement_label>,
        x3::forward_ast<generate_statement_label>,
        x3::forward_ast<index_specification>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_SPECIFICATION_HPP_ */


/*
 * block_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct begin;
struct block;
struct block_declarative_part;
struct block_header;
struct block_label;
struct block_statement_part;
struct end;
struct guard_expression;
struct is;

struct block_statement : x3::position_tagged
{
    begin               begin;              
    block               block;              
    block_declarative_partblock_declarative_part;
    block_header        block_header;       
    block_label         block_label;        
    block_statement_partblock_statement_part;
    end                 end;                
    guard_expression    guard_expression;   
    is                  is;                 
};


std::ostream& operator<<(std::ostream& os, block_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_HPP_ */


/*
 * block_statement_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct concurrent_statement;

struct block_statement_part : x3::position_tagged
{
    concurrent_statementconcurrent_statement;
};


std::ostream& operator<<(std::ostream& os, block_statement_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_PART_HPP_ */


/*
 * case_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct case;
struct case_label;
struct case_statement_alternative;
struct end;
struct expression;
struct is;

struct case_statement : x3::position_tagged
{
    case                case;               
    case_label          case_label;         
    case_statement_alternativecase_statement_alternative;
    end                 end;                
    expression          expression;         
    is                  is;                 
};


std::ostream& operator<<(std::ostream& os, case_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_HPP_ */


/*
 * case_statement_alternative.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_ALTERNATIVE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_ALTERNATIVE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct choices;
struct sequence_of_statements;
struct when;

struct case_statement_alternative : x3::position_tagged
{
    choices             choices;            
    sequence_of_statementssequence_of_statements;
    when                when;               
};


std::ostream& operator<<(std::ostream& os, case_statement_alternative const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_ALTERNATIVE_HPP_ */


/*
 * character_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHARACTER_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHARACTER_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct graphic_character;

struct character_literal : x3::position_tagged
{
    graphic_character   graphic_character;  
};


std::ostream& operator<<(std::ostream& os, character_literal const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHARACTER_LITERAL_HPP_ */


/*
 * choice.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHOICE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHOICE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct discrete_range;
struct element_simple_name;
struct others;
struct simple_expression;

struct choice :
    x3::variant<
        x3::forward_ast<discrete_range>,
        x3::forward_ast<element_simple_name>,
        x3::forward_ast<others>,
        x3::forward_ast<simple_expression>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHOICE_HPP_ */


/*
 * choices.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHOICES_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHOICES_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct choice;

struct choices :
    x3::variant<
        x3::forward_ast<choice>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CHOICES_HPP_ */


/*
 * component_configuration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_CONFIGURATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_CONFIGURATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct binding_indication;
struct block_configuration;
struct component_specification;
struct end;
struct for;

struct component_configuration : x3::position_tagged
{
    binding_indication  binding_indication; 
    block_configuration block_configuration;
    component_specificationcomponent_specification;
    end                 end;                
    for                 for;                
};


std::ostream& operator<<(std::ostream& os, component_configuration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_CONFIGURATION_HPP_ */


/*
 * component_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct component;
struct component_simple_name;
struct end;
struct identifier;
struct is;
struct local_generic_clause;
struct local_port_clause;

struct component_declaration : x3::position_tagged
{
    component           component;          
    component_simple_namecomponent_simple_name;
    end                 end;                
    identifier          identifier;         
    is                  is;                 
    local_generic_clauselocal_generic_clause;
    local_port_clause   local_port_clause;  
};


std::ostream& operator<<(std::ostream& os, component_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_DECLARATION_HPP_ */


/*
 * component_instantiation_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_INSTANTIATION_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_INSTANTIATION_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct generic_map_aspect;
struct instantiated_unit;
struct instantiation_label;
struct port_map_aspect;

struct component_instantiation_statement : x3::position_tagged
{
    generic_map_aspect  generic_map_aspect; 
    instantiated_unit   instantiated_unit;  
    instantiation_label instantiation_label;
    port_map_aspect     port_map_aspect;    
};


std::ostream& operator<<(std::ostream& os, component_instantiation_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_INSTANTIATION_STATEMENT_HPP_ */


/*
 * component_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct component_name;
struct instantiation_list;

struct component_specification : x3::position_tagged
{
    component_name      component_name;     
    instantiation_list  instantiation_list; 
};


std::ostream& operator<<(std::ostream& os, component_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_SPECIFICATION_HPP_ */


/*
 * composite_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPOSITE_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPOSITE_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct array_type_definition;
struct record_type_definition;

struct composite_type_definition :
    x3::variant<
        x3::forward_ast<array_type_definition>,
        x3::forward_ast<record_type_definition>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPOSITE_TYPE_DEFINITION_HPP_ */


/*
 * concurrent_assertion_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_ASSERTION_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_ASSERTION_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct assertion;
struct label;
struct postponed;

struct concurrent_assertion_statement : x3::position_tagged
{
    assertion           assertion;          
    label               label;              
    postponed           postponed;          
};


std::ostream& operator<<(std::ostream& os, concurrent_assertion_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_ASSERTION_STATEMENT_HPP_ */


/*
 * concurrent_procedure_call_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct label;
struct postponed;
struct procedure_call;

struct concurrent_procedure_call_statement : x3::position_tagged
{
    label               label;              
    postponed           postponed;          
    procedure_call      procedure_call;     
};


std::ostream& operator<<(std::ostream& os, concurrent_procedure_call_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_ */


/*
 * concurrent_signal_assignment_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct conditional_signal_assignment;
struct label;
struct postponed;
struct selected_signal_assignment;

struct concurrent_signal_assignment_statement :
    x3::variant<
        x3::forward_ast<conditional_signal_assignment>,
        x3::forward_ast<label>,
        x3::forward_ast<postponed>,
        x3::forward_ast<selected_signal_assignment>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_ */


/*
 * concurrent_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct block_statement;
struct component_instantiation_statement;
struct concurrent_assertion_statement;
struct concurrent_procedure_call_statement;
struct concurrent_signal_assignment_statement;
struct generate_statement;
struct process_statement;

struct concurrent_statement :
    x3::variant<
        x3::forward_ast<block_statement>,
        x3::forward_ast<component_instantiation_statement>,
        x3::forward_ast<concurrent_assertion_statement>,
        x3::forward_ast<concurrent_procedure_call_statement>,
        x3::forward_ast<concurrent_signal_assignment_statement>,
        x3::forward_ast<generate_statement>,
        x3::forward_ast<process_statement>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_STATEMENT_HPP_ */


/*
 * condition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct boolean_expression;

struct condition : x3::position_tagged
{
    boolean_expression  boolean_expression; 
};


std::ostream& operator<<(std::ostream& os, condition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_HPP_ */


/*
 * condition_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct until;

struct condition_clause : x3::position_tagged
{
    condition           condition;          
    until               until;              
};


std::ostream& operator<<(std::ostream& os, condition_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_CLAUSE_HPP_ */


/*
 * conditional_signal_assignment.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct conditional_waveforms;
struct options;
struct target;

struct conditional_signal_assignment : x3::position_tagged
{
    conditional_waveformsconditional_waveforms;
    options             options;            
    target              target;             
};


std::ostream& operator<<(std::ostream& os, conditional_signal_assignment const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_ */


/*
 * conditional_waveforms.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_WAVEFORMS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_WAVEFORMS_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct else;
struct waveform;
struct when;

struct conditional_waveforms : x3::position_tagged
{
    condition           condition;          
    else                else;               
    waveform            waveform;           
    when                when;               
};


std::ostream& operator<<(std::ostream& os, conditional_waveforms const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_WAVEFORMS_HPP_ */


/*
 * configuration_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct block_configuration;
struct configuration;
struct configuration_declarative_part;
struct configuration_simple_name;
struct end;
struct entity_name;
struct identifier;
struct is;
struct of;

struct configuration_declaration : x3::position_tagged
{
    block_configuration block_configuration;
    configuration       configuration;      
    configuration_declarative_partconfiguration_declarative_part;
    configuration_simple_nameconfiguration_simple_name;
    end                 end;                
    entity_name         entity_name;        
    identifier          identifier;         
    is                  is;                 
    of                  of;                 
};


std::ostream& operator<<(std::ostream& os, configuration_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATION_HPP_ */


/*
 * configuration_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute_specification;
struct group_declaration;
struct use_clause;

struct configuration_declarative_item :
    x3::variant<
        x3::forward_ast<attribute_specification>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<use_clause>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATIVE_ITEM_HPP_ */


/*
 * configuration_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct configuration_declarative_item;

struct configuration_declarative_part : x3::position_tagged
{
    configuration_declarative_itemconfiguration_declarative_item;
};


std::ostream& operator<<(std::ostream& os, configuration_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_DECLARATIVE_PART_HPP_ */


/*
 * configuration_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct block_configuration;
struct component_configuration;

struct configuration_item :
    x3::variant<
        x3::forward_ast<block_configuration>,
        x3::forward_ast<component_configuration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_ITEM_HPP_ */


/*
 * configuration_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct binding_indication;
struct component_specification;
struct for;

struct configuration_specification : x3::position_tagged
{
    binding_indication  binding_indication; 
    component_specificationcomponent_specification;
    for                 for;                
};


std::ostream& operator<<(std::ostream& os, configuration_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_SPECIFICATION_HPP_ */


/*
 * constant_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTANT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTANT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct constant;
struct expression;
struct identifier_list;
struct subtype_indication;

struct constant_declaration : x3::position_tagged
{
    constant            constant;           
    expression          expression;         
    identifier_list     identifier_list;    
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, constant_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTANT_DECLARATION_HPP_ */


/*
 * constrained_array_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINED_ARRAY_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINED_ARRAY_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct array;
struct element_subtype_indication;
struct index_constraint;
struct of;

struct constrained_array_definition : x3::position_tagged
{
    array               array;              
    element_subtype_indicationelement_subtype_indication;
    index_constraint    index_constraint;   
    of                  of;                 
};


std::ostream& operator<<(std::ostream& os, constrained_array_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINED_ARRAY_DEFINITION_HPP_ */


/*
 * constraint.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct index_constraint;
struct range_constraint;

struct constraint :
    x3::variant<
        x3::forward_ast<index_constraint>,
        x3::forward_ast<range_constraint>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINT_HPP_ */


/*
 * context_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct context_item;

struct context_clause : x3::position_tagged
{
    context_item        context_item;       
};


std::ostream& operator<<(std::ostream& os, context_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_CLAUSE_HPP_ */


/*
 * context_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct library_clause;
struct use_clause;

struct context_item :
    x3::variant<
        x3::forward_ast<library_clause>,
        x3::forward_ast<use_clause>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_ITEM_HPP_ */


/*
 * decimal_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct exponent;
struct integer;

struct decimal_literal : x3::position_tagged
{
    exponent            exponent;           
    integer             integer;            
};


std::ostream& operator<<(std::ostream& os, decimal_literal const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_ */


/*
 * declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct attribute_declaration;
struct component_declaration;
struct configuration_declaration;
struct entity_declaration;
struct group_declaration;
struct group_template_declaration;
struct interface_declaration;
struct object_declaration;
struct package_declaration;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;

struct declaration :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<attribute_declaration>,
        x3::forward_ast<component_declaration>,
        x3::forward_ast<configuration_declaration>,
        x3::forward_ast<entity_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<interface_declaration>,
        x3::forward_ast<object_declaration>,
        x3::forward_ast<package_declaration>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECLARATION_HPP_ */


/*
 * delay_mechanism.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct inertial;
struct reject;
struct time_expression;
struct transport;

struct delay_mechanism :
    x3::variant<
        x3::forward_ast<inertial>,
        x3::forward_ast<reject>,
        x3::forward_ast<time_expression>,
        x3::forward_ast<transport>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_ */


/*
 * design_file.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_FILE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_FILE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct design_unit;

struct design_file : x3::position_tagged
{
    design_unit         design_unit;        
};


std::ostream& operator<<(std::ostream& os, design_file const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_FILE_HPP_ */


/*
 * design_unit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_UNIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct context_clause;
struct library_unit;

struct design_unit : x3::position_tagged
{
    context_clause      context_clause;     
    library_unit        library_unit;       
};


std::ostream& operator<<(std::ostream& os, design_unit const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_UNIT_HPP_ */


/*
 * designator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGNATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;
struct operator_symbol;

struct designator :
    x3::variant<
        x3::forward_ast<identifier>,
        x3::forward_ast<operator_symbol>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGNATOR_HPP_ */


/*
 * direction.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DIRECTION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DIRECTION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct downto;
struct to;

struct direction :
    x3::variant<
        x3::forward_ast<downto>,
        x3::forward_ast<to>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DIRECTION_HPP_ */


/*
 * disconnection_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCONNECTION_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCONNECTION_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct after;
struct disconnect;
struct guarded_signal_specification;
struct time_expression;

struct disconnection_specification : x3::position_tagged
{
    after               after;              
    disconnect          disconnect;         
    guarded_signal_specificationguarded_signal_specification;
    time_expression     time_expression;    
};


std::ostream& operator<<(std::ostream& os, disconnection_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCONNECTION_SPECIFICATION_HPP_ */


/*
 * discrete_range.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCRETE_RANGE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCRETE_RANGE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct discrete_subtype_indication;
struct range;

struct discrete_range :
    x3::variant<
        x3::forward_ast<discrete_subtype_indication>,
        x3::forward_ast<range>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCRETE_RANGE_HPP_ */


/*
 * element_association.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_ASSOCIATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_ASSOCIATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct choices;
struct expression;

struct element_association : x3::position_tagged
{
    choices             choices;            
    expression          expression;         
};


std::ostream& operator<<(std::ostream& os, element_association const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_ASSOCIATION_HPP_ */


/*
 * element_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct element_subtype_definition;
struct identifier_list;

struct element_declaration : x3::position_tagged
{
    element_subtype_definitionelement_subtype_definition;
    identifier_list     identifier_list;    
};


std::ostream& operator<<(std::ostream& os, element_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_DECLARATION_HPP_ */


/*
 * element_subtype_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_SUBTYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_SUBTYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct subtype_indication;

struct element_subtype_definition : x3::position_tagged
{
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, element_subtype_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_SUBTYPE_DEFINITION_HPP_ */


/*
 * entity_aspect.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_ASPECT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_ASPECT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct architecture_identifier;
struct configuration;
struct configuration_name;
struct entity;
struct entity_name;
struct open;

struct entity_aspect :
    x3::variant<
        x3::forward_ast<architecture_identifier>,
        x3::forward_ast<configuration>,
        x3::forward_ast<configuration_name>,
        x3::forward_ast<entity>,
        x3::forward_ast<entity_name>,
        x3::forward_ast<open>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_ASPECT_HPP_ */


/*
 * entity_class.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct architecture;
struct component;
struct configuration;
struct constant;
struct entity;
struct file;
struct function;
struct group;
struct label;
struct literal;
struct package;
struct procedure;
struct signal;
struct subtype;
struct type;
struct units;
struct variable;

struct entity_class :
    x3::variant<
        x3::forward_ast<architecture>,
        x3::forward_ast<component>,
        x3::forward_ast<configuration>,
        x3::forward_ast<constant>,
        x3::forward_ast<entity>,
        x3::forward_ast<file>,
        x3::forward_ast<function>,
        x3::forward_ast<group>,
        x3::forward_ast<label>,
        x3::forward_ast<literal>,
        x3::forward_ast<package>,
        x3::forward_ast<procedure>,
        x3::forward_ast<signal>,
        x3::forward_ast<subtype>,
        x3::forward_ast<type>,
        x3::forward_ast<units>,
        x3::forward_ast<variable>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_HPP_ */


/*
 * entity_class_entry.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_class;

struct entity_class_entry : x3::position_tagged
{
    entity_class        entity_class;       
};


std::ostream& operator<<(std::ostream& os, entity_class_entry const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_HPP_ */


/*
 * entity_class_entry_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_class_entry;

struct entity_class_entry_list : x3::position_tagged
{
    entity_class_entry  entity_class_entry; 
};


std::ostream& operator<<(std::ostream& os, entity_class_entry_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_LIST_HPP_ */


/*
 * entity_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct begin;
struct end;
struct entity;
struct entity_declarative_part;
struct entity_header;
struct entity_simple_name;
struct entity_statement_part;
struct identifier;
struct is;

struct entity_declaration : x3::position_tagged
{
    begin               begin;              
    end                 end;                
    entity              entity;             
    entity_declarative_partentity_declarative_part;
    entity_header       entity_header;      
    entity_simple_name  entity_simple_name; 
    entity_statement_partentity_statement_part;
    identifier          identifier;         
    is                  is;                 
};


std::ostream& operator<<(std::ostream& os, entity_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATION_HPP_ */


/*
 * entity_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct attribute_declaration;
struct attribute_specification;
struct constant_declaration;
struct disconnection_specification;
struct file_declaration;
struct group_declaration;
struct group_template_declaration;
struct shared_variable_declaration;
struct signal_declaration;
struct subprogram_body;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;
struct use_clause;

struct entity_declarative_item :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<attribute_declaration>,
        x3::forward_ast<attribute_specification>,
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<disconnection_specification>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<shared_variable_declaration>,
        x3::forward_ast<signal_declaration>,
        x3::forward_ast<subprogram_body>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>,
        x3::forward_ast<use_clause>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATIVE_ITEM_HPP_ */


/*
 * entity_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_declarative_item;

struct entity_declarative_part : x3::position_tagged
{
    entity_declarative_itementity_declarative_item;
};


std::ostream& operator<<(std::ostream& os, entity_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATIVE_PART_HPP_ */


/*
 * entity_designator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DESIGNATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_tag;
struct signature;

struct entity_designator : x3::position_tagged
{
    entity_tag          entity_tag;         
    signature           signature;          
};


std::ostream& operator<<(std::ostream& os, entity_designator const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DESIGNATOR_HPP_ */


/*
 * entity_header.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_HEADER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_HEADER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct formal_generic_clause;
struct formal_port_clause;

struct entity_header : x3::position_tagged
{
    formal_generic_clauseformal_generic_clause;
    formal_port_clause  formal_port_clause; 
};


std::ostream& operator<<(std::ostream& os, entity_header const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_HEADER_HPP_ */


/*
 * entity_name_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_NAME_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_NAME_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct all;
struct entity_designator;
struct others;

struct entity_name_list :
    x3::variant<
        x3::forward_ast<all>,
        x3::forward_ast<entity_designator>,
        x3::forward_ast<others>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_NAME_LIST_HPP_ */


/*
 * entity_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_class;
struct entity_name_list;

struct entity_specification : x3::position_tagged
{
    entity_class        entity_class;       
    entity_name_list    entity_name_list;   
};


std::ostream& operator<<(std::ostream& os, entity_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_SPECIFICATION_HPP_ */


/*
 * entity_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct concurrent_assertion_statement;
struct passive_concurrent_procedure_call_statement;
struct passive_process_statement;

struct entity_statement :
    x3::variant<
        x3::forward_ast<concurrent_assertion_statement>,
        x3::forward_ast<passive_concurrent_procedure_call_statement>,
        x3::forward_ast<passive_process_statement>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_HPP_ */


/*
 * entity_statement_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_statement;

struct entity_statement_part : x3::position_tagged
{
    entity_statement    entity_statement;   
};


std::ostream& operator<<(std::ostream& os, entity_statement_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_PART_HPP_ */


/*
 * entity_tag.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_TAG_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_TAG_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct character_literal;
struct operator_symbol;
struct simple_name;

struct entity_tag :
    x3::variant<
        x3::forward_ast<character_literal>,
        x3::forward_ast<operator_symbol>,
        x3::forward_ast<simple_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_TAG_HPP_ */


/*
 * enumeration_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct character_literal;
struct identifier;

struct enumeration_literal :
    x3::variant<
        x3::forward_ast<character_literal>,
        x3::forward_ast<identifier>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_LITERAL_HPP_ */


/*
 * enumeration_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct enumeration_literal;

struct enumeration_type_definition : x3::position_tagged
{
    enumeration_literal enumeration_literal;
};


std::ostream& operator<<(std::ostream& os, enumeration_type_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_ */


/*
 * exit_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXIT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXIT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct exit;
struct label;
struct loop_label;
struct when;

struct exit_statement : x3::position_tagged
{
    condition           condition;          
    exit                exit;               
    label               label;              
    loop_label          loop_label;         
    when                when;               
};


std::ostream& operator<<(std::ostream& os, exit_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXIT_STATEMENT_HPP_ */


/*
 * exponent.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPONENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPONENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct +;
struct -;
struct E;
struct integer;

struct exponent :
    x3::variant<
        x3::forward_ast<+>,
        x3::forward_ast<->,
        x3::forward_ast<E>,
        x3::forward_ast<integer>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPONENT_HPP_ */


/*
 * expression.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct and;
struct nand;
struct nor;
struct or;
struct relation;
struct xnor;
struct xor;

struct expression :
    x3::variant<
        x3::forward_ast<and>,
        x3::forward_ast<nand>,
        x3::forward_ast<nor>,
        x3::forward_ast<or>,
        x3::forward_ast<relation>,
        x3::forward_ast<xnor>,
        x3::forward_ast<xor>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_ */


/*
 * extended_digit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXTENDED_DIGIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXTENDED_DIGIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct digit;
struct letter;

struct extended_digit :
    x3::variant<
        x3::forward_ast<digit>,
        x3::forward_ast<letter>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXTENDED_DIGIT_HPP_ */


/*
 * extended_identifier.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXTENDED_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXTENDED_IDENTIFIER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct \;
struct graphic_character;

struct extended_identifier : x3::position_tagged
{
    \                   \;                  
    graphic_character   graphic_character;  
};


std::ostream& operator<<(std::ostream& os, extended_identifier const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXTENDED_IDENTIFIER_HPP_ */


/*
 * factor.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct **;
struct abs;
struct not;
struct primary;

struct factor :
    x3::variant<
        x3::forward_ast<**>,
        x3::forward_ast<abs>,
        x3::forward_ast<not>,
        x3::forward_ast<primary>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_ */


/*
 * file_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct file;
struct file_open_information;
struct identifier_list;
struct subtype_indication;

struct file_declaration : x3::position_tagged
{
    file                file;               
    file_open_informationfile_open_information;
    identifier_list     identifier_list;    
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, file_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_DECLARATION_HPP_ */


/*
 * file_logical_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_LOGICAL_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_LOGICAL_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct string_expression;

struct file_logical_name : x3::position_tagged
{
    string_expression   string_expression;  
};


std::ostream& operator<<(std::ostream& os, file_logical_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_LOGICAL_NAME_HPP_ */


/*
 * file_open_information.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_OPEN_INFORMATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_OPEN_INFORMATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct file_logical_name;
struct file_open_kind_expression;
struct is;
struct open;

struct file_open_information : x3::position_tagged
{
    file_logical_name   file_logical_name;  
    file_open_kind_expressionfile_open_kind_expression;
    is                  is;                 
    open                open;               
};


std::ostream& operator<<(std::ostream& os, file_open_information const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_OPEN_INFORMATION_HPP_ */


/*
 * file_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct file;
struct floating_type_definition;
struct of;
struct range_constraint;
struct type_mark;

struct file_type_definition : x3::position_tagged
{
    file                file;               
    floating_type_definitionfloating_type_definition;
    of                  of;                 
    range_constraint    range_constraint;   
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, file_type_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_TYPE_DEFINITION_HPP_ */


/*
 * formal_designator.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_DESIGNATOR_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct generic_name;
struct parameter_name;
struct port_name;

struct formal_designator :
    x3::variant<
        x3::forward_ast<generic_name>,
        x3::forward_ast<parameter_name>,
        x3::forward_ast<port_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_DESIGNATOR_HPP_ */


/*
 * formal_parameter_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PARAMETER_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PARAMETER_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct parameter_interface_list;

struct formal_parameter_list : x3::position_tagged
{
    parameter_interface_listparameter_interface_list;
};


std::ostream& operator<<(std::ostream& os, formal_parameter_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PARAMETER_LIST_HPP_ */


/*
 * formal_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct formal_designator;
struct function_name;
struct type_mark;

struct formal_part :
    x3::variant<
        x3::forward_ast<formal_designator>,
        x3::forward_ast<function_name>,
        x3::forward_ast<type_mark>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PART_HPP_ */


/*
 * full_type_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FULL_TYPE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FULL_TYPE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;
struct is;
struct type;
struct type_definition;

struct full_type_declaration : x3::position_tagged
{
    identifier          identifier;         
    is                  is;                 
    type                type;               
    type_definition     type_definition;    
};


std::ostream& operator<<(std::ostream& os, full_type_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FULL_TYPE_DECLARATION_HPP_ */


/*
 * function_call.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct actual_parameter_part;
struct function_name;

struct function_call : x3::position_tagged
{
    actual_parameter_partactual_parameter_part;
    function_name       function_name;      
};


std::ostream& operator<<(std::ostream& os, function_call const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_ */


/*
 * generate_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATE_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATE_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct begin;
struct block_declarative_item;
struct concurrent_statement;
struct end;
struct generate;
struct generate_label;
struct generation_scheme;

struct generate_statement : x3::position_tagged
{
    begin               begin;              
    block_declarative_itemblock_declarative_item;
    concurrent_statementconcurrent_statement;
    end                 end;                
    generate            generate;           
    generate_label      generate_label;     
    generation_scheme   generation_scheme;  
};


std::ostream& operator<<(std::ostream& os, generate_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATE_STATEMENT_HPP_ */


/*
 * generation_scheme.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATION_SCHEME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATION_SCHEME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct for;
struct generate_parameter_specification;
struct if;

struct generation_scheme :
    x3::variant<
        x3::forward_ast<condition>,
        x3::forward_ast<for>,
        x3::forward_ast<generate_parameter_specification>,
        x3::forward_ast<if>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATION_SCHEME_HPP_ */


/*
 * generic_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct generic;
struct generic_list;

struct generic_clause : x3::position_tagged
{
    generic             generic;            
    generic_list        generic_list;       
};


std::ostream& operator<<(std::ostream& os, generic_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_CLAUSE_HPP_ */


/*
 * generic_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct generic_interface_list;

struct generic_list : x3::position_tagged
{
    generic_interface_listgeneric_interface_list;
};


std::ostream& operator<<(std::ostream& os, generic_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_LIST_HPP_ */


/*
 * generic_map_aspect.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_MAP_ASPECT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_MAP_ASPECT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct generic;
struct generic_association_list;
struct map;

struct generic_map_aspect : x3::position_tagged
{
    generic             generic;            
    generic_association_listgeneric_association_list;
    map                 map;                
};


std::ostream& operator<<(std::ostream& os, generic_map_aspect const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_MAP_ASPECT_HPP_ */


/*
 * graphic_character.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GRAPHIC_CHARACTER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GRAPHIC_CHARACTER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct basic_graphic_character;
struct lower_case_letter;
struct other_special_character;

struct graphic_character :
    x3::variant<
        x3::forward_ast<basic_graphic_character>,
        x3::forward_ast<lower_case_letter>,
        x3::forward_ast<other_special_character>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GRAPHIC_CHARACTER_HPP_ */


/*
 * group_constituent.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct character_literal;
struct name;

struct group_constituent :
    x3::variant<
        x3::forward_ast<character_literal>,
        x3::forward_ast<name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_HPP_ */


/*
 * group_constituent_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct group_constituent;

struct group_constituent_list : x3::position_tagged
{
    group_constituent   group_constituent;  
};


std::ostream& operator<<(std::ostream& os, group_constituent_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_LIST_HPP_ */


/*
 * group_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct group;
struct group_constituent_list;
struct group_template_name;
struct identifier;

struct group_declaration : x3::position_tagged
{
    group               group;              
    group_constituent_listgroup_constituent_list;
    group_template_name group_template_name;
    identifier          identifier;         
};


std::ostream& operator<<(std::ostream& os, group_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_DECLARATION_HPP_ */


/*
 * group_template_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_TEMPLATE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_TEMPLATE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct entity_class_entry_list;
struct group;
struct identifier;
struct is;

struct group_template_declaration : x3::position_tagged
{
    entity_class_entry_listentity_class_entry_list;
    group               group;              
    identifier          identifier;         
    is                  is;                 
};


std::ostream& operator<<(std::ostream& os, group_template_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_TEMPLATE_DECLARATION_HPP_ */


/*
 * guarded_signal_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct guarded_signal_list;
struct type_mark;

struct guarded_signal_specification : x3::position_tagged
{
    guarded_signal_list guarded_signal_list;
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, guarded_signal_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_ */


/*
 * identifier.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct basic_identifier;
struct extended_identifier;

struct identifier :
    x3::variant<
        x3::forward_ast<basic_identifier>,
        x3::forward_ast<extended_identifier>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_ */


/*
 * identifier_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;

struct identifier_list : x3::position_tagged
{
    identifier          identifier;         
};


std::ostream& operator<<(std::ostream& os, identifier_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_LIST_HPP_ */


/*
 * if_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IF_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IF_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct else;
struct elsif;
struct end;
struct if;
struct if_label;
struct sequence_of_statements;
struct then;

struct if_statement : x3::position_tagged
{
    condition           condition;          
    else                else;               
    elsif               elsif;              
    end                 end;                
    if                  if;                 
    if_label            if_label;           
    sequence_of_statementssequence_of_statements;
    then                then;               
};


std::ostream& operator<<(std::ostream& os, if_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IF_STATEMENT_HPP_ */


/*
 * incomplete_type_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INCOMPLETE_TYPE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INCOMPLETE_TYPE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;
struct type;

struct incomplete_type_declaration : x3::position_tagged
{
    identifier          identifier;         
    type                type;               
};


std::ostream& operator<<(std::ostream& os, incomplete_type_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INCOMPLETE_TYPE_DECLARATION_HPP_ */


/*
 * index_constraint.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_CONSTRAINT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_CONSTRAINT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct discrete_range;

struct index_constraint : x3::position_tagged
{
    discrete_range      discrete_range;     
};


std::ostream& operator<<(std::ostream& os, index_constraint const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_CONSTRAINT_HPP_ */


/*
 * index_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct discrete_range;
struct static_expression;

struct index_specification :
    x3::variant<
        x3::forward_ast<discrete_range>,
        x3::forward_ast<static_expression>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SPECIFICATION_HPP_ */


/*
 * index_subtype_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SUBTYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SUBTYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct range;
struct type_mark;

struct index_subtype_definition : x3::position_tagged
{
    range               range;              
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, index_subtype_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SUBTYPE_DEFINITION_HPP_ */


/*
 * indexed_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEXED_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEXED_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct prefix;

struct indexed_name : x3::position_tagged
{
    expression          expression;         
    prefix              prefix;             
};


std::ostream& operator<<(std::ostream& os, indexed_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEXED_NAME_HPP_ */


/*
 * instantiated_unit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATED_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATED_UNIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct architecture_identifier;
struct component;
struct component_name;
struct configuration;
struct configuration_name;
struct entity;
struct entity_name;

struct instantiated_unit :
    x3::variant<
        x3::forward_ast<architecture_identifier>,
        x3::forward_ast<component>,
        x3::forward_ast<component_name>,
        x3::forward_ast<configuration>,
        x3::forward_ast<configuration_name>,
        x3::forward_ast<entity>,
        x3::forward_ast<entity_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATED_UNIT_HPP_ */


/*
 * instantiation_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATION_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATION_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct all;
struct instantiation_label;
struct others;

struct instantiation_list :
    x3::variant<
        x3::forward_ast<all>,
        x3::forward_ast<instantiation_label>,
        x3::forward_ast<others>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATION_LIST_HPP_ */


/*
 * integer.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTEGER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTEGER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct digit;
struct underline;

struct integer : x3::position_tagged
{
    digit               digit;              
    underline           underline;          
};


std::ostream& operator<<(std::ostream& os, integer const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTEGER_HPP_ */


/*
 * integer_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTEGER_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTEGER_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct range_constraint;

struct integer_type_definition : x3::position_tagged
{
    range_constraint    range_constraint;   
};


std::ostream& operator<<(std::ostream& os, integer_type_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTEGER_TYPE_DEFINITION_HPP_ */


/*
 * interface_constant_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_CONSTANT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_CONSTANT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct constant;
struct identifier_list;
struct in;
struct static_expression;
struct subtype_indication;

struct interface_constant_declaration : x3::position_tagged
{
    constant            constant;           
    identifier_list     identifier_list;    
    in                  in;                 
    static_expression   static_expression;  
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, interface_constant_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_CONSTANT_DECLARATION_HPP_ */


/*
 * interface_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct interface_constant_declaration;
struct interface_file_declaration;
struct interface_signal_declaration;
struct interface_variable_declaration;

struct interface_declaration :
    x3::variant<
        x3::forward_ast<interface_constant_declaration>,
        x3::forward_ast<interface_file_declaration>,
        x3::forward_ast<interface_signal_declaration>,
        x3::forward_ast<interface_variable_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_DECLARATION_HPP_ */


/*
 * interface_element.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_ELEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_ELEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct interface_declaration;

struct interface_element : x3::position_tagged
{
    interface_declarationinterface_declaration;
};


std::ostream& operator<<(std::ostream& os, interface_element const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_ELEMENT_HPP_ */


/*
 * interface_file_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_FILE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_FILE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct file;
struct identifier_list;
struct subtype_indication;

struct interface_file_declaration : x3::position_tagged
{
    file                file;               
    identifier_list     identifier_list;    
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, interface_file_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_FILE_DECLARATION_HPP_ */


/*
 * interface_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct interface_element;

struct interface_list : x3::position_tagged
{
    interface_element   interface_element;  
};


std::ostream& operator<<(std::ostream& os, interface_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_LIST_HPP_ */


/*
 * interface_signal_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_SIGNAL_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_SIGNAL_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct bus;
struct identifier_list;
struct mode;
struct signal;
struct static_expression;
struct subtype_indication;

struct interface_signal_declaration : x3::position_tagged
{
    bus                 bus;                
    identifier_list     identifier_list;    
    mode                mode;               
    signal              signal;             
    static_expression   static_expression;  
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, interface_signal_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_SIGNAL_DECLARATION_HPP_ */


/*
 * interface_variable_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_VARIABLE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_VARIABLE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier_list;
struct mode;
struct static_expression;
struct subtype_indication;
struct variable;

struct interface_variable_declaration : x3::position_tagged
{
    identifier_list     identifier_list;    
    mode                mode;               
    static_expression   static_expression;  
    subtype_indication  subtype_indication; 
    variable            variable;           
};


std::ostream& operator<<(std::ostream& os, interface_variable_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_VARIABLE_DECLARATION_HPP_ */


/*
 * iteration_scheme.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ITERATION_SCHEME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ITERATION_SCHEME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct for;
struct loop_parameter_specification;
struct while;

struct iteration_scheme :
    x3::variant<
        x3::forward_ast<condition>,
        x3::forward_ast<for>,
        x3::forward_ast<loop_parameter_specification>,
        x3::forward_ast<while>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ITERATION_SCHEME_HPP_ */


/*
 * label.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LABEL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LABEL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;

struct label : x3::position_tagged
{
    identifier          identifier;         
};


std::ostream& operator<<(std::ostream& os, label const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LABEL_HPP_ */


/*
 * letter.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LETTER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LETTER_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct lower_case_letter;
struct upper_case_letter;

struct letter :
    x3::variant<
        x3::forward_ast<lower_case_letter>,
        x3::forward_ast<upper_case_letter>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LETTER_HPP_ */


/*
 * letter_or_digit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LETTER_OR_DIGIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LETTER_OR_DIGIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct digit;
struct letter;

struct letter_or_digit :
    x3::variant<
        x3::forward_ast<digit>,
        x3::forward_ast<letter>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LETTER_OR_DIGIT_HPP_ */


/*
 * library_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct library;
struct logical_name_list;

struct library_clause : x3::position_tagged
{
    library             library;            
    logical_name_list   logical_name_list;  
};


std::ostream& operator<<(std::ostream& os, library_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_CLAUSE_HPP_ */


/*
 * library_unit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_UNIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct primary_unit;
struct secondary_unit;

struct library_unit :
    x3::variant<
        x3::forward_ast<primary_unit>,
        x3::forward_ast<secondary_unit>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_UNIT_HPP_ */


/*
 * literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct bit_string_literal;
struct enumeration_literal;
struct null;
struct numeric_literal;
struct string_literal;

struct literal :
    x3::variant<
        x3::forward_ast<bit_string_literal>,
        x3::forward_ast<enumeration_literal>,
        x3::forward_ast<null>,
        x3::forward_ast<numeric_literal>,
        x3::forward_ast<string_literal>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_ */


/*
 * logical_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOGICAL_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOGICAL_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;

struct logical_name : x3::position_tagged
{
    identifier          identifier;         
};


std::ostream& operator<<(std::ostream& os, logical_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOGICAL_NAME_HPP_ */


/*
 * logical_name_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOGICAL_NAME_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOGICAL_NAME_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct logical_name;

struct logical_name_list : x3::position_tagged
{
    logical_name        logical_name;       
};


std::ostream& operator<<(std::ostream& os, logical_name_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOGICAL_NAME_LIST_HPP_ */


/*
 * loop_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOOP_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOOP_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct end;
struct iteration_scheme;
struct loop;
struct loop_label;
struct sequence_of_statements;

struct loop_statement : x3::position_tagged
{
    end                 end;                
    iteration_scheme    iteration_scheme;   
    loop                loop;               
    loop_label          loop_label;         
    sequence_of_statementssequence_of_statements;
};


std::ostream& operator<<(std::ostream& os, loop_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOOP_STATEMENT_HPP_ */


/*
 * mode.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_MODE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_MODE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct buffer;
struct in;
struct inout;
struct linkage;
struct out;

struct mode :
    x3::variant<
        x3::forward_ast<buffer>,
        x3::forward_ast<in>,
        x3::forward_ast<inout>,
        x3::forward_ast<linkage>,
        x3::forward_ast<out>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_MODE_HPP_ */


/*
 * name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute_name;
struct indexed_name;
struct operator_symbol;
struct selected_name;
struct simple_name;
struct slice_name;

struct name :
    x3::variant<
        x3::forward_ast<attribute_name>,
        x3::forward_ast<indexed_name>,
        x3::forward_ast<operator_symbol>,
        x3::forward_ast<selected_name>,
        x3::forward_ast<simple_name>,
        x3::forward_ast<slice_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_ */


/*
 * next_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NEXT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NEXT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition;
struct label;
struct loop_label;
struct next;
struct when;

struct next_statement : x3::position_tagged
{
    condition           condition;          
    label               label;              
    loop_label          loop_label;         
    next                next;               
    when                when;               
};


std::ostream& operator<<(std::ostream& os, next_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NEXT_STATEMENT_HPP_ */


/*
 * null_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NULL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NULL_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct label;
struct null;

struct null_statement : x3::position_tagged
{
    label               label;              
    null                null;               
};


std::ostream& operator<<(std::ostream& os, null_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NULL_STATEMENT_HPP_ */


/*
 * numeric_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NUMERIC_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NUMERIC_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct abstract_literal;
struct physical_literal;

struct numeric_literal :
    x3::variant<
        x3::forward_ast<abstract_literal>,
        x3::forward_ast<physical_literal>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NUMERIC_LITERAL_HPP_ */


/*
 * object_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OBJECT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OBJECT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct constant_declaration;
struct file_declaration;
struct signal_declaration;
struct variable_declaration;

struct object_declaration :
    x3::variant<
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<signal_declaration>,
        x3::forward_ast<variable_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OBJECT_DECLARATION_HPP_ */


/*
 * operator_symbol.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct string_literal;

struct operator_symbol : x3::position_tagged
{
    string_literal      string_literal;     
};


std::ostream& operator<<(std::ostream& os, operator_symbol const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_ */


/*
 * options.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPTIONS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPTIONS_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct delay_mechanism;
struct guarded;

struct options : x3::position_tagged
{
    delay_mechanism     delay_mechanism;    
    guarded             guarded;            
};


std::ostream& operator<<(std::ostream& os, options const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPTIONS_HPP_ */


/*
 * package_body.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct body;
struct end;
struct is;
struct package;
struct package_body_declarative_part;
struct package_simple_name;

struct package_body : x3::position_tagged
{
    body                body;               
    end                 end;                
    is                  is;                 
    package             package;            
    package_body_declarative_partpackage_body_declarative_part;
    package_simple_name package_simple_name;
};


std::ostream& operator<<(std::ostream& os, package_body const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_HPP_ */


/*
 * package_body_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct constant_declaration;
struct file_declaration;
struct group_declaration;
struct group_template_declaration;
struct shared_variable_declaration;
struct subprogram_body;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;
struct use_clause;

struct package_body_declarative_item :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<shared_variable_declaration>,
        x3::forward_ast<subprogram_body>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>,
        x3::forward_ast<use_clause>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_DECLARATIVE_ITEM_HPP_ */


/*
 * package_body_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct package_body_declarative_item;

struct package_body_declarative_part : x3::position_tagged
{
    package_body_declarative_itempackage_body_declarative_item;
};


std::ostream& operator<<(std::ostream& os, package_body_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_ */


/*
 * package_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct end;
struct identifier;
struct is;
struct package;
struct package_declarative_part;
struct package_simple_name;

struct package_declaration : x3::position_tagged
{
    end                 end;                
    identifier          identifier;         
    is                  is;                 
    package             package;            
    package_declarative_partpackage_declarative_part;
    package_simple_name package_simple_name;
};


std::ostream& operator<<(std::ostream& os, package_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATION_HPP_ */


/*
 * package_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct attribute_declaration;
struct attribute_specification;
struct component_declaration;
struct constant_declaration;
struct disconnection_specification;
struct file_declaration;
struct group_declaration;
struct group_template_declaration;
struct shared_variable_declaration;
struct signal_declaration;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;
struct use_clause;

struct package_declarative_item :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<attribute_declaration>,
        x3::forward_ast<attribute_specification>,
        x3::forward_ast<component_declaration>,
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<disconnection_specification>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<shared_variable_declaration>,
        x3::forward_ast<signal_declaration>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>,
        x3::forward_ast<use_clause>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATIVE_ITEM_HPP_ */


/*
 * package_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct package_declarative_item;

struct package_declarative_part : x3::position_tagged
{
    package_declarative_itempackage_declarative_item;
};


std::ostream& operator<<(std::ostream& os, package_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATIVE_PART_HPP_ */


/*
 * parameter_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PARAMETER_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PARAMETER_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct discrete_range;
struct identifier;
struct in;

struct parameter_specification : x3::position_tagged
{
    discrete_range      discrete_range;     
    identifier          identifier;         
    in                  in;                 
};


std::ostream& operator<<(std::ostream& os, parameter_specification const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PARAMETER_SPECIFICATION_HPP_ */


/*
 * physical_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct abstract_literal;
struct unit_name;

struct physical_literal : x3::position_tagged
{
    abstract_literal    abstract_literal;   
    unit_name           unit_name;          
};


std::ostream& operator<<(std::ostream& os, physical_literal const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_LITERAL_HPP_ */


/*
 * physical_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct base_unit_declaration;
struct end;
struct physical_type_simple_name;
struct range_constraint;
struct secondary_unit_declaration;
struct units;

struct physical_type_definition : x3::position_tagged
{
    base_unit_declarationbase_unit_declaration;
    end                 end;                
    physical_type_simple_namephysical_type_simple_name;
    range_constraint    range_constraint;   
    secondary_unit_declarationsecondary_unit_declaration;
    units               units;              
};


std::ostream& operator<<(std::ostream& os, physical_type_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_TYPE_DEFINITION_HPP_ */


/*
 * port_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct port;
struct port_list;

struct port_clause : x3::position_tagged
{
    port                port;               
    port_list           port_list;          
};


std::ostream& operator<<(std::ostream& os, port_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_CLAUSE_HPP_ */


/*
 * port_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct port_interface_list;

struct port_list : x3::position_tagged
{
    port_interface_list port_interface_list;
};


std::ostream& operator<<(std::ostream& os, port_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_LIST_HPP_ */


/*
 * port_map_aspect.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_MAP_ASPECT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_MAP_ASPECT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct map;
struct port;
struct port_association_list;

struct port_map_aspect : x3::position_tagged
{
    map                 map;                
    port                port;               
    port_association_listport_association_list;
};


std::ostream& operator<<(std::ostream& os, port_map_aspect const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PORT_MAP_ASPECT_HPP_ */


/*
 * prefix.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PREFIX_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PREFIX_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct function_call;
struct name;

struct prefix :
    x3::variant<
        x3::forward_ast<function_call>,
        x3::forward_ast<name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PREFIX_HPP_ */


/*
 * primary.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct aggregate;
struct allocator;
struct expression;
struct function_call;
struct literal;
struct name;
struct qualified_expression;
struct type_conversion;

struct primary :
    x3::variant<
        x3::forward_ast<aggregate>,
        x3::forward_ast<allocator>,
        x3::forward_ast<expression>,
        x3::forward_ast<function_call>,
        x3::forward_ast<literal>,
        x3::forward_ast<name>,
        x3::forward_ast<qualified_expression>,
        x3::forward_ast<type_conversion>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_ */


/*
 * primary_unit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_UNIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct configuration_declaration;
struct entity_declaration;
struct package_declaration;

struct primary_unit :
    x3::variant<
        x3::forward_ast<configuration_declaration>,
        x3::forward_ast<entity_declaration>,
        x3::forward_ast<package_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_UNIT_HPP_ */


/*
 * procedure_call.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct actual_parameter_part;
struct procedure_name;

struct procedure_call : x3::position_tagged
{
    actual_parameter_partactual_parameter_part;
    procedure_name      procedure_name;     
};


std::ostream& operator<<(std::ostream& os, procedure_call const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_HPP_ */


/*
 * procedure_call_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct label;
struct procedure_call;

struct procedure_call_statement : x3::position_tagged
{
    label               label;              
    procedure_call      procedure_call;     
};


std::ostream& operator<<(std::ostream& os, procedure_call_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_STATEMENT_HPP_ */


/*
 * process_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct attribute_declaration;
struct attribute_specification;
struct constant_declaration;
struct file_declaration;
struct group_declaration;
struct group_template_declaration;
struct subprogram_body;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;
struct use_clause;
struct variable_declaration;

struct process_declarative_item :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<attribute_declaration>,
        x3::forward_ast<attribute_specification>,
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<subprogram_body>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>,
        x3::forward_ast<use_clause>,
        x3::forward_ast<variable_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_ITEM_HPP_ */


/*
 * process_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct process_declarative_item;

struct process_declarative_part : x3::position_tagged
{
    process_declarative_itemprocess_declarative_item;
};


std::ostream& operator<<(std::ostream& os, process_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_PART_HPP_ */


/*
 * process_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct begin;
struct end;
struct is;
struct postponed;
struct process;
struct process_declarative_part;
struct process_label;
struct process_statement_part;
struct sensitivity_list;

struct process_statement : x3::position_tagged
{
    begin               begin;              
    end                 end;                
    is                  is;                 
    postponed           postponed;          
    process             process;            
    process_declarative_partprocess_declarative_part;
    process_label       process_label;      
    process_statement_partprocess_statement_part;
    sensitivity_list    sensitivity_list;   
};


std::ostream& operator<<(std::ostream& os, process_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_STATEMENT_HPP_ */


/*
 * process_statement_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_STATEMENT_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct sequential_statement;

struct process_statement_part : x3::position_tagged
{
    sequential_statementsequential_statement;
};


std::ostream& operator<<(std::ostream& os, process_statement_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_STATEMENT_PART_HPP_ */


/*
 * qualified_expression.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_QUALIFIED_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_QUALIFIED_EXPRESSION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct aggregate;
struct expression;
struct type_mark;

struct qualified_expression :
    x3::variant<
        x3::forward_ast<aggregate>,
        x3::forward_ast<expression>,
        x3::forward_ast<type_mark>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_QUALIFIED_EXPRESSION_HPP_ */


/*
 * range.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct direction;
struct range_attribute_name;
struct simple_expression;

struct range :
    x3::variant<
        x3::forward_ast<direction>,
        x3::forward_ast<range_attribute_name>,
        x3::forward_ast<simple_expression>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_HPP_ */


/*
 * range_constraint.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_CONSTRAINT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_CONSTRAINT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct range;

struct range_constraint : x3::position_tagged
{
    range               range;              
};


std::ostream& operator<<(std::ostream& os, range_constraint const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_CONSTRAINT_HPP_ */


/*
 * record_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RECORD_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RECORD_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct element_declaration;
struct end;
struct record;
struct record_type_simple_name;

struct record_type_definition : x3::position_tagged
{
    element_declaration element_declaration;
    end                 end;                
    record              record;             
    record_type_simple_namerecord_type_simple_name;
};


std::ostream& operator<<(std::ostream& os, record_type_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RECORD_TYPE_DEFINITION_HPP_ */


/*
 * relation.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct relational_operator;
struct shift_expression;

struct relation : x3::position_tagged
{
    relational_operator relational_operator;
    shift_expression    shift_expression;   
};


std::ostream& operator<<(std::ostream& os, relation const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_ */


/*
 * report_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_REPORT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_REPORT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct label;
struct report;
struct severity;

struct report_statement : x3::position_tagged
{
    expression          expression;         
    label               label;              
    report              report;             
    severity            severity;           
};


std::ostream& operator<<(std::ostream& os, report_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_REPORT_STATEMENT_HPP_ */


/*
 * return_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RETURN_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RETURN_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct label;
struct return;

struct return_statement : x3::position_tagged
{
    expression          expression;         
    label               label;              
    return              return;             
};


std::ostream& operator<<(std::ostream& os, return_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RETURN_STATEMENT_HPP_ */


/*
 * scalar_type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SCALAR_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SCALAR_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct enumeration_type_definition;
struct floating_type_definition;
struct integer_type_definition;
struct physical_type_definition;

struct scalar_type_definition :
    x3::variant<
        x3::forward_ast<enumeration_type_definition>,
        x3::forward_ast<floating_type_definition>,
        x3::forward_ast<integer_type_definition>,
        x3::forward_ast<physical_type_definition>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SCALAR_TYPE_DEFINITION_HPP_ */


/*
 * secondary_unit.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct architecture_body;
struct package_body;

struct secondary_unit :
    x3::variant<
        x3::forward_ast<architecture_body>,
        x3::forward_ast<package_body>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_HPP_ */


/*
 * secondary_unit_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;
struct physical_literal;

struct secondary_unit_declaration : x3::position_tagged
{
    identifier          identifier;         
    physical_literal    physical_literal;   
};


std::ostream& operator<<(std::ostream& os, secondary_unit_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_DECLARATION_HPP_ */


/*
 * selected_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct prefix;
struct suffix;

struct selected_name : x3::position_tagged
{
    prefix              prefix;             
    suffix              suffix;             
};


std::ostream& operator<<(std::ostream& os, selected_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_NAME_HPP_ */


/*
 * selected_signal_assignment.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct options;
struct select;
struct selected_waveforms;
struct target;
struct with;

struct selected_signal_assignment : x3::position_tagged
{
    expression          expression;         
    options             options;            
    select              select;             
    selected_waveforms  selected_waveforms; 
    target              target;             
    with                with;               
};


std::ostream& operator<<(std::ostream& os, selected_signal_assignment const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_ */


/*
 * selected_waveforms.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_WAVEFORMS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_WAVEFORMS_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct choices;
struct waveform;
struct when;

struct selected_waveforms : x3::position_tagged
{
    choices             choices;            
    waveform            waveform;           
    when                when;               
};


std::ostream& operator<<(std::ostream& os, selected_waveforms const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_WAVEFORMS_HPP_ */


/*
 * sensitivity_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct on;
struct sensitivity_list;

struct sensitivity_clause : x3::position_tagged
{
    on                  on;                 
    sensitivity_list    sensitivity_list;   
};


std::ostream& operator<<(std::ostream& os, sensitivity_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_CLAUSE_HPP_ */


/*
 * sensitivity_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct signal_name;

struct sensitivity_list : x3::position_tagged
{
    signal_name         signal_name;        
};


std::ostream& operator<<(std::ostream& os, sensitivity_list const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_LIST_HPP_ */


/*
 * sequence_of_statements.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENCE_OF_STATEMENTS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENCE_OF_STATEMENTS_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct sequential_statement;

struct sequence_of_statements : x3::position_tagged
{
    sequential_statementsequential_statement;
};


std::ostream& operator<<(std::ostream& os, sequence_of_statements const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENCE_OF_STATEMENTS_HPP_ */


/*
 * sequential_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENTIAL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENTIAL_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct assertion_statement;
struct case_statement;
struct exit_statement;
struct if_statement;
struct loop_statement;
struct next_statement;
struct null_statement;
struct procedure_call_statement;
struct report_statement;
struct return_statement;
struct signal_assignment_statement;
struct variable_assignment_statement;
struct wait_statement;

struct sequential_statement :
    x3::variant<
        x3::forward_ast<assertion_statement>,
        x3::forward_ast<case_statement>,
        x3::forward_ast<exit_statement>,
        x3::forward_ast<if_statement>,
        x3::forward_ast<loop_statement>,
        x3::forward_ast<next_statement>,
        x3::forward_ast<null_statement>,
        x3::forward_ast<procedure_call_statement>,
        x3::forward_ast<report_statement>,
        x3::forward_ast<return_statement>,
        x3::forward_ast<signal_assignment_statement>,
        x3::forward_ast<variable_assignment_statement>,
        x3::forward_ast<wait_statement>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENTIAL_STATEMENT_HPP_ */


/*
 * shift_expression.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct shift_operator;
struct simple_expression;

struct shift_expression : x3::position_tagged
{
    shift_operator      shift_operator;     
    simple_expression   simple_expression;  
};


std::ostream& operator<<(std::ostream& os, shift_expression const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_ */


/*
 * sign.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGN_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGN_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct +;
struct -;

struct sign :
    x3::variant<
        x3::forward_ast<+>,
        x3::forward_ast<->
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGN_HPP_ */


/*
 * signal_assignment_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct delay_mechanism;
struct label;
struct target;
struct waveform;

struct signal_assignment_statement : x3::position_tagged
{
    delay_mechanism     delay_mechanism;    
    label               label;              
    target              target;             
    waveform            waveform;           
};


std::ostream& operator<<(std::ostream& os, signal_assignment_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_ */


/*
 * signal_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct identifier_list;
struct signal;
struct signal_kind;
struct subtype_indication;

struct signal_declaration : x3::position_tagged
{
    expression          expression;         
    identifier_list     identifier_list;    
    signal              signal;             
    signal_kind         signal_kind;        
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, signal_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_DECLARATION_HPP_ */


/*
 * signal_kind.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_KIND_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_KIND_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct bus;
struct register;

struct signal_kind :
    x3::variant<
        x3::forward_ast<bus>,
        x3::forward_ast<register>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_KIND_HPP_ */


/*
 * signal_list.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct all;
struct others;
struct signal_name;

struct signal_list :
    x3::variant<
        x3::forward_ast<all>,
        x3::forward_ast<others>,
        x3::forward_ast<signal_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_ */


/*
 * signature.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNATURE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNATURE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct return;
struct type_mark;

struct signature : x3::position_tagged
{
    return              return;             
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, signature const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNATURE_HPP_ */


/*
 * simple_expression.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct adding_operator;
struct sign;
struct term;

struct simple_expression : x3::position_tagged
{
    adding_operator     adding_operator;    
    sign                sign;               
    term                term;               
};


std::ostream& operator<<(std::ostream& os, simple_expression const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_ */


/*
 * simple_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;

struct simple_name : x3::position_tagged
{
    identifier          identifier;         
};


std::ostream& operator<<(std::ostream& os, simple_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_ */


/*
 * slice_name.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SLICE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SLICE_NAME_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct discrete_range;
struct prefix;

struct slice_name : x3::position_tagged
{
    discrete_range      discrete_range;     
    prefix              prefix;             
};


std::ostream& operator<<(std::ostream& os, slice_name const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SLICE_NAME_HPP_ */


/*
 * string_literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_STRING_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_STRING_LITERAL_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct graphic_character;

struct string_literal : x3::position_tagged
{
    graphic_character   graphic_character;  
};


std::ostream& operator<<(std::ostream& os, string_literal const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_STRING_LITERAL_HPP_ */


/*
 * subprogram_body.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_BODY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_BODY_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct begin;
struct designator;
struct end;
struct is;
struct subprogram_declarative_part;
struct subprogram_kind;
struct subprogram_specification;
struct subprogram_statement_part;

struct subprogram_body : x3::position_tagged
{
    begin               begin;              
    designator          designator;         
    end                 end;                
    is                  is;                 
    subprogram_declarative_partsubprogram_declarative_part;
    subprogram_kind     subprogram_kind;    
    subprogram_specificationsubprogram_specification;
    subprogram_statement_partsubprogram_statement_part;
};


std::ostream& operator<<(std::ostream& os, subprogram_body const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_BODY_HPP_ */


/*
 * subprogram_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct subprogram_specification;

struct subprogram_declaration : x3::position_tagged
{
    subprogram_specificationsubprogram_specification;
};


std::ostream& operator<<(std::ostream& os, subprogram_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATION_HPP_ */


/*
 * subprogram_declarative_item.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_ITEM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct alias_declaration;
struct attribute_declaration;
struct attribute_specification;
struct constant_declaration;
struct file_declaration;
struct group_declaration;
struct group_template_declaration;
struct subprogram_body;
struct subprogram_declaration;
struct subtype_declaration;
struct type_declaration;
struct use_clause;
struct variable_declaration;

struct subprogram_declarative_item :
    x3::variant<
        x3::forward_ast<alias_declaration>,
        x3::forward_ast<attribute_declaration>,
        x3::forward_ast<attribute_specification>,
        x3::forward_ast<constant_declaration>,
        x3::forward_ast<file_declaration>,
        x3::forward_ast<group_declaration>,
        x3::forward_ast<group_template_declaration>,
        x3::forward_ast<subprogram_body>,
        x3::forward_ast<subprogram_declaration>,
        x3::forward_ast<subtype_declaration>,
        x3::forward_ast<type_declaration>,
        x3::forward_ast<use_clause>,
        x3::forward_ast<variable_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_ITEM_HPP_ */


/*
 * subprogram_declarative_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct subprogram_declarative_item;

struct subprogram_declarative_part : x3::position_tagged
{
    subprogram_declarative_itemsubprogram_declarative_item;
};


std::ostream& operator<<(std::ostream& os, subprogram_declarative_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_PART_HPP_ */


/*
 * subprogram_kind.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_KIND_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_KIND_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct function;
struct procedure;

struct subprogram_kind :
    x3::variant<
        x3::forward_ast<function>,
        x3::forward_ast<procedure>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_KIND_HPP_ */


/*
 * subprogram_specification.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_SPECIFICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct designator;
struct formal_parameter_list;
struct function;
struct impure;
struct procedure;
struct pure;
struct return;
struct type_mark;

struct subprogram_specification :
    x3::variant<
        x3::forward_ast<designator>,
        x3::forward_ast<formal_parameter_list>,
        x3::forward_ast<function>,
        x3::forward_ast<impure>,
        x3::forward_ast<procedure>,
        x3::forward_ast<pure>,
        x3::forward_ast<return>,
        x3::forward_ast<type_mark>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_SPECIFICATION_HPP_ */


/*
 * subprogram_statement_part.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_STATEMENT_PART_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct sequential_statement;

struct subprogram_statement_part : x3::position_tagged
{
    sequential_statementsequential_statement;
};


std::ostream& operator<<(std::ostream& os, subprogram_statement_part const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_STATEMENT_PART_HPP_ */


/*
 * subtype_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier;
struct is;
struct subtype;
struct subtype_indication;

struct subtype_declaration : x3::position_tagged
{
    identifier          identifier;         
    is                  is;                 
    subtype             subtype;            
    subtype_indication  subtype_indication; 
};


std::ostream& operator<<(std::ostream& os, subtype_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_DECLARATION_HPP_ */


/*
 * subtype_indication.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct constraint;
struct resolution_function_name;
struct type_mark;

struct subtype_indication : x3::position_tagged
{
    constraint          constraint;         
    resolution_function_nameresolution_function_name;
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, subtype_indication const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_ */


/*
 * suffix.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct all;
struct character_literal;
struct operator_symbol;
struct simple_name;

struct suffix :
    x3::variant<
        x3::forward_ast<all>,
        x3::forward_ast<character_literal>,
        x3::forward_ast<operator_symbol>,
        x3::forward_ast<simple_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_ */


/*
 * target.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TARGET_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TARGET_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct aggregate;
struct name;

struct target :
    x3::variant<
        x3::forward_ast<aggregate>,
        x3::forward_ast<name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TARGET_HPP_ */


/*
 * term.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct factor;
struct multiplying_operator;

struct term : x3::position_tagged
{
    factor              factor;             
    multiplying_operatormultiplying_operator;
};


std::ostream& operator<<(std::ostream& os, term const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_ */


/*
 * timeout_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TIMEOUT_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TIMEOUT_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct for;
struct time_expression;

struct timeout_clause : x3::position_tagged
{
    for                 for;                
    time_expression     time_expression;    
};


std::ostream& operator<<(std::ostream& os, timeout_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TIMEOUT_CLAUSE_HPP_ */


/*
 * type_conversion.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_CONVERSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_CONVERSION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct type_mark;

struct type_conversion : x3::position_tagged
{
    expression          expression;         
    type_mark           type_mark;          
};


std::ostream& operator<<(std::ostream& os, type_conversion const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_CONVERSION_HPP_ */


/*
 * type_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct full_type_declaration;
struct incomplete_type_declaration;

struct type_declaration :
    x3::variant<
        x3::forward_ast<full_type_declaration>,
        x3::forward_ast<incomplete_type_declaration>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DECLARATION_HPP_ */


/*
 * type_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct access_type_definition;
struct composite_type_definition;
struct file_type_definition;
struct scalar_type_definition;

struct type_definition :
    x3::variant<
        x3::forward_ast<access_type_definition>,
        x3::forward_ast<composite_type_definition>,
        x3::forward_ast<file_type_definition>,
        x3::forward_ast<scalar_type_definition>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DEFINITION_HPP_ */


/*
 * type_mark.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct subtype_name;
struct type_name;

struct type_mark :
    x3::variant<
        x3::forward_ast<subtype_name>,
        x3::forward_ast<type_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_ */


/*
 * unconstrained_array_definition.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct array;
struct element_subtype_indication;
struct index_subtype_definition;
struct of;

struct unconstrained_array_definition : x3::position_tagged
{
    array               array;              
    element_subtype_indicationelement_subtype_indication;
    index_subtype_definitionindex_subtype_definition;
    of                  of;                 
};


std::ostream& operator<<(std::ostream& os, unconstrained_array_definition const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_ */


/*
 * use_clause.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_USE_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_USE_CLAUSE_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct selected_name;
struct use;

struct use_clause : x3::position_tagged
{
    selected_name       selected_name;      
    use                 use;                
};


std::ostream& operator<<(std::ostream& os, use_clause const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_USE_CLAUSE_HPP_ */


/*
 * variable_assignment_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct label;
struct target;

struct variable_assignment_statement : x3::position_tagged
{
    expression          expression;         
    label               label;              
    target              target;             
};


std::ostream& operator<<(std::ostream& os, variable_assignment_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_ */


/*
 * variable_declaration.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_DECLARATION_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression;
struct identifier_list;
struct shared;
struct subtype_indication;
struct variable;

struct variable_declaration : x3::position_tagged
{
    expression          expression;         
    identifier_list     identifier_list;    
    shared              shared;             
    subtype_indication  subtype_indication; 
    variable            variable;           
};


std::ostream& operator<<(std::ostream& os, variable_declaration const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_DECLARATION_HPP_ */


/*
 * wait_statement.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAIT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAIT_STATEMENT_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct condition_clause;
struct label;
struct sensitivity_clause;
struct timeout_clause;
struct wait;

struct wait_statement : x3::position_tagged
{
    condition_clause    condition_clause;   
    label               label;              
    sensitivity_clause  sensitivity_clause; 
    timeout_clause      timeout_clause;     
    wait                wait;               
};


std::ostream& operator<<(std::ostream& os, wait_statement const& node);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAIT_STATEMENT_HPP_ */


/*
 * waveform.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */
        
#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_HPP_

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct unaffected;
struct waveform_element;

struct waveform :
    x3::variant<
        x3::forward_ast<unaffected>,
        x3::forward_ast<waveform_element>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_HPP_ */

