/*
 * data_set.hpp
 *
 *  Created on: 28.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_TEST_DATA_SET_HPP_
#define SOURCES_VHDL93_TEST_DATA_SET_HPP_


#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <vector>
#include <iostream>


namespace x3_test {


namespace fs = boost::filesystem;



class dataset_loader
{
public:
    typedef std::vector<std::string>                    dataset_type;

public:
    class data_set;

    data_set input() const;
    data_set expect() const;

public:
    dataset_loader(fs::path const& path)
    {
        read_files(path);
    }

private:
    int read_files(fs::path const& path)
    {
        try {
            if(fs::exists(path) && fs::is_directory(path)) {

                auto dir_iter = fs::directory_iterator(path);
                auto const& dir_end  = fs::directory_iterator();
                for( ; dir_iter != dir_end; dir_iter++) {

                    if (fs::extension(dir_iter->path()) == ".input") {

                        auto input_path  = dir_iter->path();
                        auto expect_path = dir_iter->path();
                        expect_path.replace_extension(".expected");

                        m_input.emplace_back(   read_file(input_path) );
                        m_expected.emplace_back(read_file(expect_path));
                    }
                }
            }
            else {
                std::cerr << "Directory: " << fs::absolute(path)
                << " does not exist.\n";
                return 1;
            }
        }
        catch(fs::filesystem_error const& e) {
            std::cerr << "Caught " << e.what() << " exception\n";
            return 1;
        }
        catch(...) {
            std::cerr << "Caught unexpected exception !!!\n";
            return 1;

        }
        return 0;
    }

    std::string read_file(fs::path const& file_path)
    {
        fs::ifstream file{ file_path };

        if(!file) {
            throw std::ios_base::failure{ "file open error" };
        }

        std::ostringstream ss{};
        ss << file.rdbuf();

        if(file.fail() && !file.eof()) {
            throw std::ios_base::failure{ "rdbuf() read error" };
        }

        return ss.str();
    }

private:
    dataset_type     m_input;
    dataset_type     m_expected;
};

} // namespace x3_test


namespace x3_test {


class dataset_loader::data_set
{
public:
	typedef dataset_type::const_iterator	iterator;

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


dataset_loader::data_set dataset_loader::input() const
{
    return data_set(m_input);
}

dataset_loader::data_set dataset_loader::expect() const
{
    return data_set(m_expected);
}


using ::boost::unit_test::data::monomorphic::operator^;


} // namespace x3_test


namespace boost { namespace unit_test { namespace data { namespace monomorphic {
	  // registering fibonacci_dataset as a proper dataset
	  template <>
	  struct is_dataset<x3_test::dataset_loader::data_set> : boost::mpl::true_ {};
}}}}


#endif /* SOURCES_VHDL93_TEST_DATA_SET_HPP_ */
