/*
 * data_set.hpp
 *
 *  Created on: 28.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_DATA_SET_HPP_
#define SOURCES_VHDL_TEST_DATA_SET_HPP_


#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <boost/filesystem.hpp>

#include <vector>
#include <iostream>


namespace x3_test {


namespace fs = boost::filesystem;



class dataset_loader
{
public:
    typedef fs::path::string_type                       string_type;
    typedef fs::path::string_type::value_type           char_type;

    typedef std::vector<string_type>                    dataset_type;

public:
    class data_set;

    data_set test_file_name() const;
    data_set input() const;
    data_set expect() const;

public:
    dataset_loader(fs::path const& path);

private:
    int read_files(fs::path const& path);
    string_type read_file(fs::path const& file_path);

private:
    dataset_type     m_file_path;
    dataset_type     m_input;
    dataset_type     m_expected;

#if defined(_WIN32) || defined(_WIN64)
    static constexpr std::wostream& cerr{ std::wcerr };
    static constexpr std::wostream& cout{ std::wcout };
#else
    static constexpr std::ostream& cerr{ std::cerr };
    static constexpr std::ostream& cout{ std::cout };
#endif
};

} // namespace x3_test


namespace x3_test {


class dataset_loader::data_set
{
public:
    typedef dataset_type::const_iterator    iterator;

public:
    data_set(dataset_type const& data)
    : m_data{ data }
    { }

public: // boost.test dataset API
    enum { arity = 1 };
    using sample = dataset_type::value_type;
    boost::unit_test::data::size_t size() const { return m_data.size(); }
    iterator begin() const { return m_data.begin(); }

private:
    dataset_type const& m_data;
};


using ::boost::unit_test::data::monomorphic::operator^;


} // namespace x3_test


namespace boost { namespace unit_test { namespace data { namespace monomorphic {
      // registering as a proper dataset
      template <>
      struct is_dataset<x3_test::dataset_loader::data_set> : boost::mpl::true_ {};
}}}}


#endif /* SOURCES_VHDL_TEST_DATA_SET_HPP_ */
