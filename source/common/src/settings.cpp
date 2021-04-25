#include <ibis/settings.hpp>
#include <ibis/namespace_alias.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <boost/property_tree/json_parser.hpp>

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

    boost::iostreams::stream<  // --
        boost::iostreams::basic_array_source<char_type> >
        is(json_sv.begin(), json_sv.size());

    pt::ptree other;
    pt::read_json(is, other);

    // call ptree's API, if called multiple times, other is appended multiple times too!
    instance().insert(instance().end(), other.begin(), other.end());
}

}  // namespace ibis
