/*
 * ctx.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/context.hpp>
#include <eda/util/make_iomanip.hpp>
#include <eda/settings.hpp>

#include <iostream>

#include <eda/support/boost/locale.hpp>


namespace eda { namespace vhdl {


context::context()
: error_count{ /* default limit */ }
, warning_count{ /* default limit */ }
{
	auto error_limit = 20; //XXX eda::setting["ferror-limit"];

	// check if error_limit is not disabled (equals to 0)
	if (error_limit != 0) {
		error_count.limit() = error_limit;
	}
}


std::ostream& failure_status::operator()(std::ostream& os) const
{
    using boost::locale::translate;
    using boost::locale::format;

    // Fix for Clang '-Weverything' Diagnostic at format(translate("...", count)):
    //     warning: implicit conversion loses integer precision: 'const size_t'
    //     (aka 'const unsigned long') to 'int' [-Wshorten-64-to-32]
    //
    // Obviously boost.locale uses an int32 in the [plural form](
    //  https://www.boost.org/doc/libs/1_67_0/libs/locale/doc/html/messages_formatting.html#plural_forms).
    // To avoid further references by '-Weverything' diagnostics a plural form
    // for count is introduced. For plural form the concrete maximum value isn't
    // critical in human language.
    auto const plural_count = [](size_t count) {
        static constexpr int N{ std::numeric_limits<int>::max() };
        if (count > N) return N;
        return static_cast<int>(count);
    };


    // concept, see [Wanbox](https://wandbox.org/permlink/VJrqXuEFppw1htY7)
    auto const error_message = (format(translate("{1} error", "{1} errors",
        plural_count(ctx.error_count))) % ctx.error_count).str();

    auto const warning_message = (format(translate("{1} warning", "{1} warnings",
        plural_count(ctx.warning_count))) % ctx.warning_count).str();

    if (ctx.error_count && ctx.warning_count) {
        os << format(translate("{1} and {2} generated.")) % error_message % warning_message;
    }
    else if (ctx.error_count) {
        os << format(translate("{1} generated.")) % error_message;
    }
    else if (ctx.warning_count) {
        os << format(translate("{1} generated.")) % warning_message;
    }
    else {
        // all went fine
    }

    return os;
}


} } // namespace eda.vhdl

