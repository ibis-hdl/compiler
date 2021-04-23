#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <string>
#include <tuple>
#include <optional>
#include <vector>
#include <map>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite::vhdl::ast {

///
/// @brief Fixture for testing parser::position_cache
///
/// @todo Implement using testsuite::util::cli_args
///
struct position_cache_fixture {
    position_cache_fixture();
    ~position_cache_fixture();

    static position_cache_fixture*& instance();

    std::string test_case_source_dir() const;
    std::size_t load_reference(std::string const& file_name);

    std::string const& reference_contents(std::size_t id) const { return inputs[id]; }

    std::tuple<parser::iterator_type, parser::iterator_type> contents_range(std::size_t id,
                                                                            std::string_view str);

    ibis::vhdl::ast::position_tagged& addNode(std::string const& key,
                                              ibis::vhdl::ast::position_tagged const& node);
    ibis::vhdl::ast::position_tagged const& getNode(std::string const& key) const;

public:
    ///
    /// store the ID to avoid initialization order problems.
    ///
    /// This ID must be set each time a file is loaded/added to the fixture/position_cache
    /// to prevent problems with the file ID bound to the fixture/cache due to
    /// unspecified order of execution of tests.
    /// This implies, that the contents <N> txt tests must be run with the
    /// appropiate sub tests.
    ///
    std::size_t current_FileID;

    std::size_t input_count() const { return inputs.size(); }
    std::size_t node_count() const { return node_map.size(); }

public:
    ibis::vhdl::parser::position_cache<parser::iterator_type> position_cache;

private:
    static std::string read_file(std::string const& file_name);

private:
    std::optional<std::string> mutable input_path;
    std::vector<std::string> inputs;

    using node_map_type = std::map<std::string, ibis::vhdl::ast::position_tagged>;
    node_map_type node_map;
};

}  // namespace testsuite::vhdl::ast
