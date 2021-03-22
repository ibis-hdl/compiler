/*
 * position_cache_fixture.hpp
 *
 *  Created on: 06.09.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_VHDL_AST_INCLUDE_TESTSUITE_AST_POSITION_CACHE_FIXTURE_HPP_
#define TESTSUITE_VHDL_AST_INCLUDE_TESTSUITE_AST_POSITION_CACHE_FIXTURE_HPP_

#include <eda/vhdl/ast/position_cache.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>

#include <string>
#include <tuple>
#include <optional>
#include <vector>
#include <map>

#include <testsuite/common/namespace_alias.hpp>

namespace testsuite {

struct position_cache_fixture
{
    position_cache_fixture();
    ~position_cache_fixture();

    static position_cache_fixture*& instance();

    std::string test_case_source_dir() const;
    std::size_t load_reference(std::string const& file_name);

    std::string const& reference_contents(std::size_t id) const {
        return inputs[id];
    }

    std::tuple<parser::iterator_type, parser::iterator_type>
        contents_range(std::size_t id, std::string_view str);

    ast::position_tagged& addNode(std::string const& key, ast::position_tagged const& node);
    ast::position_tagged const& getNode(std::string const& key) const;

public:
    /**
     * store the ID to avoid initialization order problems.
     *
     * This ID must be set each time a file is loaded/added to the fixture/position_cache
     * to prevent problems with the file ID bound to the fixture/cache due to
     * unspecified order of execution of tests.
     * This implies, that the contents <N> txt tests must be run with the
     * approbiate sub tests.
     */
    std::size_t current_FileID;

    std::size_t input_count() const { return inputs.size(); }
    std::size_t node_count() const { return node_map.size(); }

public:
    eda::vhdl::ast::position_cache<parser::iterator_type> position_cache;

private:
    static std::string read_file(std::string const& file_name);

private:
    std::optional<std::string> mutable              input_path;
    std::vector<std::string>                        inputs;

    using node_map_type = std::map<std::string, ast::position_tagged>;
    node_map_type                                   node_map;
};


} // namespace testsuite



#endif /* TESTSUITE_VHDL_AST_INCLUDE_TESTSUITE_AST_POSITION_CACHE_FIXTURE_HPP_ */
