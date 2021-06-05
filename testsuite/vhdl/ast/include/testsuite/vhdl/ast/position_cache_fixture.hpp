#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <filesystem>
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
class position_cache_fixture {
public:
public:
    using position_cache_type = ibis::vhdl::parser::position_cache<parser::iterator_type>;
    using file_id_type = position_cache_type::file_id_type;

public:
    position_cache_fixture();
    ~position_cache_fixture();

    static position_cache_fixture& instance();

    /// Get the path to the test case input, given from CLI or compile builtin.
    /// @todo Implement using testsuite::util::cli_args
    std::string test_case_source_dir() const;

    /// read the file contents into internal reference storage, returning the ID of them. Same time,
    /// current_FileID() is updated. The position_cache isn't altered.
    std::size_t load_reference(fs::path const& file_name);

    /// return the last ID given from load_reference().
    std::size_t current_FileID() const { return current_file_id; }

    std::string const& reference_contents(std::size_t id) const { return inputs[id]; }

    /// find in the given file ID a string view @a str and return a pair of iterators to begin and
    /// end pointing the @a str.
    std::tuple<parser::iterator_type, parser::iterator_type> contents_range(  // --
        file_id_type id, std::string_view str);

    /// add a tagged ast::position_tagged node by key into internal registry.
    ibis::vhdl::ast::position_tagged& addNode(  // --
        std::string const& key, ibis::vhdl::ast::position_tagged const& node);

    /// get tagged ast::position_tagged node by key from internal registry.
    ibis::vhdl::ast::position_tagged const& getNode(std::string const& key) const;

public:
    std::size_t input_count() const { return inputs.size(); }
    std::size_t node_count() const { return node_map.size(); }

public:
    position_cache_type position_cache;

private:
    static std::string read_file(fs::path const& file_name);

private:
    std::optional<std::string> mutable input_path;
    std::vector<std::string> inputs;

    std::size_t current_file_id = 0;

    using node_map_type = std::map<std::string, ibis::vhdl::ast::position_tagged>;
    node_map_type node_map;
};

}  // namespace testsuite::vhdl::ast
