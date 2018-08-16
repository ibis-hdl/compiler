/*
 * syntax.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_

#include <eda/vhdl/ast.hpp>	// XXX forward

#include <eda/vhdl/ast/basic_ast_walker.hpp>
#include <eda/vhdl/context.hpp>

#include <iosfwd>
#include <string_view>


namespace eda { namespace vhdl { namespace analyze {


class syntax_worker
{
public:
	using error_handler_type = std::function<
        void(ast::position_tagged, std::string const&)>;

public:
    template <typename ErrorHandler>
	syntax_worker(std::ostream& os_,
                  vhdl::context& context_,
		          ErrorHandler const& error_handler_)
	: os{ os_ }
    , context{ context_ }
    , error_handler{
          [&](ast::position_tagged error_position, std::string const& message)
              { error_handler_(error_position, message); }
          }
	{ }

public:
	bool has_errors() const;

public:
    void operator()(ast::block_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::case_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::generate_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::if_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::loop_statement const& node, std::string_view const& node_name) const;
    void operator()(ast::process_statement const& node, std::string_view const& node_name) const;

    template<typename NodeT>
    void operator()(NodeT const&, std::string_view const&) const { }

private:
    template<typename NodeT>
    bool label_matches(NodeT const& node, std::string_view const& node_name) const;

private:
    std::ostream&									os;
    vhdl::context&                                  context;
    error_handler_type                              error_handler;
};


using syntax_checker = ast::basic_ast_walker<syntax_worker>;


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_ */
