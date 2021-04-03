#include <eda/vhdl/context.hpp>

#include <eda/vhdl/ast/util/string_span_hash.hpp>

#include <eda/settings.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <cstddef>
#include <algorithm>
#include <string>

namespace eda::vhdl {

context::context(std::size_t default_error_limit)
    : error_count(default_error_limit)
{
}

context::context(eda::settings const& settings)
{
    unsigned const error_limit = settings["ferror-limit"].get<long>();

    // check if error_limit is not disabled (equals to 0)
    if (error_limit != 0) {
        error_count.limit() = error_limit;
    }
}

std::ostream& failure_status::print(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // Fix for Clang '-Weverything' Diagnostic at format(translate("...", count)):
    //     warning: implicit conversion loses integer precision: 'const size_t'
    //     (aka 'const unsigned long') to 'int' [-Wshorten-64-to-32]
    //
    // Obviously boost.locale uses an int32 in the [plural form](
    //  https://www.boost.org/doc/libs/1_67_0/libs/locale/doc/html/messages_formatting.html#plural_forms).
    // To avoid further references by '-Weverything' diagnostics a plural form
    // lambda function for count is introduced.
    // The underlying problem is that error and warning count are of type size_t/uint64_t.
    // Even if never so much "failure" will be relevant the range for the locale must
    // be limited to int32. For the plural form the concrete count maximum
    // value isn't critical in human language.
    auto const plural_count = [](size_t count) {
        if (count > std::numeric_limits<int>::max()) {
            return std::numeric_limits<int>::max();
        }
        return static_cast<int>(count);
    };

    // render the error/warning message to console, for concept
    // see [Wandbox](https://wandbox.org/permlink/VJrqXuEFppw1htY7)

    // TRANSLATORS: singular/plural error(s)
    auto const error_message =
        (format(translate("{1} error", "{1} errors", plural_count(ctx.error_count)))  // --
         % ctx.error_count)
            .str();

    // TRANSLATORS: singular/plural warning(s)
    auto const warning_message =
        (format(translate("{1} warning", "{1} warnings", plural_count(ctx.warning_count)))  // --
         % ctx.warning_count)
            .str();

    if ((ctx.error_count != 0) && (ctx.warning_count != 0)) {
        // TRANSLATORS: summary error(s) and warning(s)
        os << format(translate("{1} and {2} generated."))  // --
                  % error_message % warning_message;
    }
    else if (ctx.error_count != 0) {
        // TRANSLATORS: summary error(s) only
        os << format(translate("{1} generated.")) % error_message;
    }
    else if (ctx.warning_count != 0) {
        // TRANSLATORS: summary warning(s) only
        os << format(translate("{1} generated.")) % warning_message;
    }
    else {
        // all went fine
    }

    return os;
}

}  // namespace eda::vhdl
