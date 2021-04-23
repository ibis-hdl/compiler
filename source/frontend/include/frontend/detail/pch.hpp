#pragma once

#include <algorithm>
#include <atomic>
#include <climits>
#include <csignal>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iosfwd>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <vector>

#include <boost/config.hpp>
#include <boost/locale.hpp>
#include <boost/process.hpp>
#include <boost/stacktrace.hpp>
#include <boost/version.hpp>

#include <CLI/CLI.hpp>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/pointer.h>
#include <rapidjson/prettywriter.h>
