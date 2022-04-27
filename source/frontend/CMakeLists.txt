################################################################################
## IBIS/ibis project
##
## file: source/ibis/CMakeLists.txt
################################################################################

project(ibis LANGUAGES CXX)


add_executable(${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::common
        ibis::vhdl
        Boost::system
        Boost::locale
        Boost::filesystem   # Boost::process depends on
        Threads::Threads
        # cope with "fatal error LNK2011: precompiled object not linked in"
        "$<$<CXX_COMPILER_ID:MSVC>:ibis_pch>"
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ibis/frontend/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/ibis/frontend/version.hpp
    @ONLY
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/init.cpp
        src/signal_handler.cpp
        $<$<BOOL:${IBIS_WITH_GDB_STACKTRACE}>:src/stacktrace_gdb.cpp>
        $<$<BOOL:${IBIS_WITH_BOOST_STACKTRACE}>:src/stacktrace_boost.cpp>
)


if(${PROJECT_NAME}_PCH)
    # override ibis_pch helper
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/ibis/frontend/detail/pch_default.hpp>
            $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/ibis/frontend/detail/pch_ibis.hpp>
    )
elseif(IBIS_ENABLE_PCH_DEFAULT OR IBIS_ENABLE_PCH_IBIS)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
        # PCH, especially G++ requires this
        $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/vhdl/include>>
        $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:$<BUILD_INTERFACE:${STRONG_TYPE_INCLUDE_DIR}>>
)


# [How to split strings across multiple lines in CMake?](
#  https://stackoverflow.com/questions/7637539/how-to-split-strings-across-multiple-lines-in-cmake)
string(CONCAT _SIGNAL_HANDLER_DEFINES
    "$<$<BOOL:${IBIS_WITH_GDB_STACKTRACE}>:IBIS_WITH_GDB_STACKTRACE>;"
    "$<$<BOOL:${IBIS_WITH_BOOST_STACKTRACE}>:IBIS_WITH_BOOST_STACKTRACE>"
)

set_source_files_properties(
    src/signal_handler.cpp
    src/stacktrace_gdb.cpp
    src/stacktrace_boost.cpp
    APPEND PROPERTIES
        COMPILE_DEFINITIONS "${_SIGNAL_HANDLER_DEFINES}"
)


# FixMe: Use generator, e.g. see https://www.brianlheim.com/2018/04/09/cmake-cheat-sheet.html
# $<$<CXX_COMPILER_ID:GNU>:-g -fno-omit-frame-pointer>
#
# FixMe: What was the intend of this compile flags? G++ with PCH fires probably here a
# warning: "cmake_pch.hxx.gch: created with -gnone, but used with -gdwarf-2".
# Maybe it's related to stack unwinding? Nevertheless, than this should be moved
# to options_devel and stacktrace section (depending on enabled option).
# It's disabled for now.

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#    target_compile_options(${PROJECT_NAME}
#        PRIVATE
#            -g -fno-omit-frame-pointer
#    )
#    set_target_properties(${PROJECT_NAME}
#        PROPERTIES
#            LINK_FLAGS "-g -fno-omit-frame-pointer"
#    )
endif()


##
# [Boost stacktrace](https://www.boost.org/doc/libs/1_75_0/doc/html/stacktrace/configuration_and_build.html)
#
# [Configuration and Build](
#  https://www.boost.org/doc/libs/1_67_0/doc/html/stacktrace/configuration_and_build.html)
#
# FixMe: This needs a rewrote; the stacktrace libraries are checked from
#        top level CMakeList.txt and are optionally now. Here we can choose
#        the best options than.
#        As an example: https://github.com/aaszodi/multovl/blob/master/CMakeLists.txt
#        where boost chrono is optional and tested on Boost_CHRONO_FOUND
#        - clangw11 has libboost_stacktrace_{basic,noop}-clangw11-...
#        - vc141 has libboost_stacktrace_{noop,windbg,windbg_cached}-vc141-...
#
# FixMe: below is Win32 specific!
if(Boost_STACKTRACE_WINDBG_FOUND)
    message(STATUS "Found stacktrace WinDbg")
else()
    if(IBIS_WITH_BOOST_STACKTRACE)
        message(STATUS "=> Configure Fix: Found no stacktrace WinDbg, disable Boost.stacktrace")
        set(IBIS_WITH_BOOST_STACKTRACE OFF
            CACHE BOOL "Boost.stacktrace option requires WindDb (not found)" FORCE)
    endif()
endif()

if(WIN32 AND IBIS_WITH_GDB_STACKTRACE)
    # Boost.stacktrace (GDB) is linux only these days
    message(STATUS "=> Configure Fix: On Win32 Boost.stacktrace (GDB) isn't tested, disabled.")
            set(IBIS_WITH_GDB_STACKTRACE OFF
                CACHE BOOL "Boost.stacktrace (GDB) option not tested on Win32." FORCE)
endif()

# old stuff
if(IBIS_WITH_BOOST_STACKTRACE_temporary_disabled)
    if(WIN32)
        find_package(Boost REQUIRED COMPONENTS stacktrace_windbg)
        message(STATUS "WinDbg library found.")
        target_compile_definitions(${PROJECT_NAME}
            PRIVATE
                BOOST_STACKTRACE_USE_WINDBG
        )
        target_include_directories(${PROJECT_NAME}
            PRIVATE
                ${Boost_INCLUDE_DIRS}
        )
        target_link_libraries(${PROJECT_NAME}
            PRIVATE
                dbgeng ole32
        )
    else()
        find_package(Backtrace REQUIRED)
        message(STATUS "### backtrace library found.")
        message(STATUS "### backtrace include dir is: ${Backtrace_INCLUDE_DIR}")
        message(STATUS "### backtrace library is: ${Backtrace_LIBRARY}")
        target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_STACKTRACE_USE_BACKTRACE)
        target_include_directories(${PROJECT_NAME} PUBLIC ${Backtrace_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} INTERFACE ${Backtrace_LIBRARY})
        if(UNIX AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            # [Where is libdl.so on Mac OS X?](
            #  https://stackoverflow.com/questions/20169660/where-is-libdl-so-on-mac-os-x)
            target_link_libraries(${PROJECT_NAME} INTERFACE ${CMAKE_DL_LIBS})
        endif()
    endif()
endif()


