#include <ibis/settings.hpp>
#include <ibis/namespace_alias.hpp>

#include <ibis/compiler/warnings_off.hpp>  // [-Wdeprecated-copy]
#include <boost/iostreams/stream.hpp>
#include <ibis/compiler/warnings_on.hpp>

#include <boost/iostreams/device/array.hpp>

#include <ibis/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/property_tree/json_parser.hpp>
#include <ibis/compiler/warnings_on.hpp>

namespace ibis {

std::ostream& settings::dump(std::ostream& os)
{
    pt::write_json(os, instance());
    return os;
}

void settings::insert_json(std::string_view json_sv)
{
    // [Is there a way to create a stringstream from a string_view without copying data?](
    // https://stackoverflow.com/questions/58524805/is-there-a-way-to-create-a-stringstream-from-a-string-view-without-copying-data)
    using char_type = std::string_view::value_type;

    // FixMe [Future Boost]: std::string_view doesn't seems to be well supported using
    // Boost+Clang-Win: error: no matching constructor for initialization of
    // 'boost::iostreams::basic_array_source<char_type>' (aka 'basic_array_source<char>')
    // note: candidate constructor not viable: no known conversion from
    // 'std::basic_string_view<char, std::char_traits<char>>::const_iterator' (aka
    // '_String_view_iterator<std::char_traits<char>>') to
    // 'boost::iostreams::basic_array_source<char>::char_type *' (aka 'char *') for 1st argument
    boost::iostreams::stream<  // --
        boost::iostreams::basic_array_source<char_type> >
        json_stream(json_sv.data(), json_sv.size());

    pt::ptree json_pt;
    pt::read_json(json_stream, json_pt);

    // call ptree's API, if called multiple times, it is appended multiple times too!
    instance().insert(instance().end(), json_pt.begin(), json_pt.end());
}

}  // namespace ibis
