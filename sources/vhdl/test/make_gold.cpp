/*
 * make_gold.cpp
 *
 *  Created on: 38.04.2017
 *      Author: olaf
 */

/*
 * During the development of the parser the format of the test case data
 * expected files has been changed. Concrete, the ast_printer has changed the
 * format. This program replaces the contents of former expected files to the
 * new format.
 *
 * Be careful with this, all tests must be before successfully finished before,
 * otherwise you get false gold/expected files for the parser.
 *
 * WARNING: Quick&Dirty solution!
 */

#include "test_case_path.hpp"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <vector>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/ast_printer.hpp>


namespace fs = boost::filesystem;
namespace x3 = boost::spirit::x3;

namespace ast = eda::vhdl::ast;
namespace parser = eda::vhdl::parser;

/*
 * loader for all test_case input files into vector of them
 */
class dataset_loader
{
public:
    struct data_set {
        fs::path        input_file_path;
        std::string     input;
        fs::path        expected_file_path;
    };
public:
    typedef std::vector<data_set>    datasets_type;

public:
    datasets_type& test_cases();

public:
    dataset_loader(fs::path const& path);

private:
    int read_files(fs::path const& path);
    std::string read_file(fs::path const& file_path);

private:
    datasets_type         m_data_sets;
};


/*
 * parser used to generate the gold expected files
 */
template <typename ParserType, typename AttrType>
std::tuple<bool, std::string>
do_parse(
    std::string const &input,
    ParserType const &parser_rule,
    AttrType& attr,
    bool full_match = true
    )
{
    std::stringstream output;

    parser::iterator_type iter = input.begin();
    parser::iterator_type const end = input.end();

    parser::error_handler_type error_handler(iter, end, output);

    auto const parser =
        x3::with<x3::error_handler_tag>(std::ref(error_handler))
        [
              parser_rule
        ];

    bool success =
        x3::phrase_parse(iter, end, parser, parser::skipper, attr);

    if (success) {
        if (iter != end) {
            error_handler(iter, "Error! Expecting end of input here: ");
        }
        else {
            ast::printer print(output);
            print.verbose_symbol = true;
            print.verbose_variant = true;
            print(attr);
        }
    }

    // FixMe: C++17 Structured Bindings
    return std::make_tuple(
        success && (!full_match || (iter == end)),
        output.str()
    );
}



template <
    typename ParserRuleType,
    typename AttrType
>
class gold_writer
{
    typedef ParserRuleType      parser_rule_type;
    typedef AttrType            attribute_type;

    dataset_loader              data_set_reader;

public:
    gold_writer(std::string const& text_case_name)
    : data_set_reader(text_case_name)
    { }

    void write()
    {
        for(auto& set : data_set_reader.test_cases()) {
            std::cout << "processing " << set.input_file_path.stem() << "\n";
            generate(set);
        }
    }

private:
    void generate(dataset_loader::data_set& data_set)
    {
        bool parse_ok{ false };
        std::string parse_result {};
        parser_rule_type parse_rule;
        attribute_type attr;

        std::tie(parse_ok, parse_result) = do_parse(data_set.input, parse_rule, attr);

        write(data_set.expected_file_path, parse_result);
    }

    void write(fs::path& expected_path, std::string const& expected)
    {
        if(fs::exists(expected_path)) {
            std::cout << expected_path << " already exist, rename to *.bak\n";

            auto bak = expected_path;
            bak.replace_extension(".expected.bak");

            if(fs::exists(bak)) {
                std::cout << "Remove old backup file " << bak << "\n";
                fs::remove(bak);
            }

            fs::rename(expected_path, bak);
        }

        std::cout << "Write gold file " << expected_path << "\n";
        fs::ofstream ofs{ expected_path };
        ofs << expected;
    }
};

/*
 * dataset_loader implementation
 */
dataset_loader::dataset_loader(fs::path const& path)
{
    fs::path source_dir{ CTEST_TEST_CASE_PATH };

    std::cout << "dataset_loader load test files from " << path;
    read_files(source_dir / path);
}


int dataset_loader::read_files(fs::path const& path)
{
    try {
        if(fs::exists(path) && fs::is_directory(path)) {

           std::vector<fs::path> dir_list { };
            std::copy(
                fs::directory_iterator(path),
                fs::directory_iterator(),
                back_inserter(dir_list)
            );

            std::sort(dir_list.begin(), dir_list.end());

            for(auto const& file : dir_list) {

                if (fs::extension(file) == ".input") {
                    //std::cout << "INFO: read '" << file.native().c_str() << "'\n";
                    auto const input_path  = file;
                    auto expect_path = file;
                    expect_path.replace_extension(".expected");

                    m_data_sets.emplace_back(
                        data_set{
                            input_path.native().c_str(),
                            read_file(file),
                            expect_path.native().c_str()
                    });
                }
            }
        }
        else {
            std::cerr << "*** Directory: '" << fs::absolute(path)
                      << "' does not exist. ***\n";
            return 1;
        }
    }
    catch(std::exception const& e) {
        std::cerr << "*** Caught \"" << e.what() << "\" exception\n";
        return -1;
    }
    catch(...) {
        std::cerr << "*** Caught unexpected exception !!!\n";
        return -1;

    }
    return 0;
}


std::string dataset_loader::read_file(fs::path const& file_path)
{
    fs::ifstream file{ file_path };

    if(!file) {
        std::cerr << "ERROR: unable to open '" << file_path.native() << "'\n";
        throw std::ios_base::failure{ "file open error" };
    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    if(file.fail() && !file.eof()) {
        std::cerr << "ERROR: unable to open '" << file_path.native() << "'\n";
        throw std::ios_base::failure{ "rdbuf() read error" };
    }

    return ss.str();
}

dataset_loader::datasets_type& dataset_loader::test_cases()
{
    return m_data_sets;
}


/* ----8<--------8<--------8<--------8<--------8<--------8<--------8<----
import os

if __name__ == "__main__":
    blacklist = [
         'integer'
    ]
    for root, dirs, files in sorted(os.walk(os.getcwd() + '/' + 'test_case')):
        #print("root=" + str(root))
        subject = os.path.basename(root)
        if subject == 'test_case':
            continue
        subject_base = subject.replace('_failure', '')
        if subject_base in blacklist:
            # don't rewrite, e.g. integer is a simple string_view
            continue
        ast = "ast::" + subject_base
        parser = "parser::" + subject_base
        test_case = "test_case/" + subject
        text = """
{{
    gold_writer<{0}_type, {1}> goldy("{2}");
    goldy.write();
}}""".format(
        parser,
        ast,
        test_case
    )
        print(text)
 * ---->8-------->8-------->8-------->8-------->8-------->8-------->8---- */
int main()
{
#if 0
    {
        gold_writer<parser::string_literal_type, ast::string_literal> goldy("test_case/test_me");
        goldy.write();
    }
#endif
    {
        gold_writer<parser::abstract_literal_type, ast::abstract_literal> goldy("test_case/abstract_literal");
        goldy.write();
    }

    {
        gold_writer<parser::attribute_name_type, ast::attribute_name> goldy("test_case/attribute_name");
        goldy.write();
    }

    {
        gold_writer<parser::attribute_specification_type, ast::attribute_specification> goldy("test_case/attribute_specification");
        goldy.write();
    }

    {
        gold_writer<parser::based_literal_type, ast::based_literal> goldy("test_case/based_literal");
        goldy.write();
    }

    {
        gold_writer<parser::bit_string_literal_type, ast::bit_string_literal> goldy("test_case/bit_string_literal");
        goldy.write();
    }

    {
        gold_writer<parser::character_literal_type, ast::character_literal> goldy("test_case/character_literal");
        goldy.write();
    }

    {
        gold_writer<parser::constraint_type, ast::constraint> goldy("test_case/constraint");
        goldy.write();
    }

    {
        gold_writer<parser::decimal_literal_type, ast::decimal_literal> goldy("test_case/decimal_literal");
        goldy.write();
    }

    {
        gold_writer<parser::discrete_range_type, ast::discrete_range> goldy("test_case/discrete_range");
        goldy.write();
    }

    {
        gold_writer<parser::enumeration_type_definition_type, ast::enumeration_type_definition> goldy("test_case/enumeration_type_definition");
        goldy.write();
    }

    {
        gold_writer<parser::expression_type, ast::expression> goldy("test_case/expression");
        goldy.write();
    }

    {
        gold_writer<parser::expression_type, ast::expression> goldy("test_case/expression_failure");
        goldy.write();
    }

    {
        gold_writer<parser::factor_type, ast::factor> goldy("test_case/factor");
        goldy.write();
    }

    {
        gold_writer<parser::function_call_type, ast::function_call> goldy("test_case/function_call");
        goldy.write();
    }

    {
        gold_writer<parser::identifier_type, ast::identifier> goldy("test_case/identifier");
        goldy.write();
    }

    {
        gold_writer<parser::identifier_type, ast::identifier> goldy("test_case/identifier_failure");
        goldy.write();
    }

    {
        gold_writer<parser::identifier_list_type, ast::identifier_list> goldy("test_case/identifier_list");
        goldy.write();
    }

    {
        gold_writer<parser::index_constraint_type, ast::index_constraint> goldy("test_case/index_constraint");
        goldy.write();
    }

    {
        gold_writer<parser::indexed_name_type, ast::indexed_name> goldy("test_case/indexed_name");
        goldy.write();
    }

    {
        gold_writer<parser::literal_type, ast::literal> goldy("test_case/literal");
        goldy.write();
    }

    {
        gold_writer<parser::name_type, ast::name> goldy("test_case/name");
        goldy.write();
    }

    {
        gold_writer<parser::numeric_literal_type, ast::numeric_literal> goldy("test_case/numeric_literal");
        goldy.write();
    }

    {
        gold_writer<parser::physical_literal_type, ast::physical_literal> goldy("test_case/physical_literal");
        goldy.write();
    }

    {
        gold_writer<parser::physical_literal_type, ast::physical_literal> goldy("test_case/physical_literal_failure");
        goldy.write();
    }

    {
        gold_writer<parser::primary_type, ast::primary> goldy("test_case/primary");
        goldy.write();
    }

    {
        gold_writer<parser::range_type, ast::range> goldy("test_case/range");
        goldy.write();
    }

    {
        gold_writer<parser::relation_type, ast::relation> goldy("test_case/relation");
        goldy.write();
    }

    {
        gold_writer<parser::shift_expression_type, ast::shift_expression> goldy("test_case/shift_expression");
        goldy.write();
    }

    {
        gold_writer<parser::signal_assignment_statement_type, ast::signal_assignment_statement> goldy("test_case/signal_assignment_statement");
        goldy.write();
    }

    {
        gold_writer<parser::signal_list_type, ast::signal_list> goldy("test_case/signal_list");
        goldy.write();
    }

    {
        gold_writer<parser::simple_expression_type, ast::simple_expression> goldy("test_case/simple_expression");
        goldy.write();
    }

    {
        gold_writer<parser::string_literal_type, ast::string_literal> goldy("test_case/string_literal");
        goldy.write();
    }

    {
        gold_writer<parser::subtype_indication_type, ast::subtype_indication> goldy("test_case/subtype_indication");
        goldy.write();
    }

    {
        gold_writer<parser::term_type, ast::term> goldy("test_case/term");
        goldy.write();
    }

    {
        gold_writer<parser::use_clause_type, ast::use_clause> goldy("test_case/use_clause");
        goldy.write();
    }

    {
        gold_writer<parser::wait_statement_type, ast::wait_statement> goldy("test_case/wait_statement");
        goldy.write();
    }

    {
        gold_writer<parser::waveform_type, ast::waveform> goldy("test_case/waveform");
        goldy.write();
    }

}
