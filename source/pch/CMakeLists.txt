################################################################################
## IBIS/pch library project
##
## file: source/pch/CMakeLists.txt
################################################################################

project(ibis_pch LANGUAGES CXX)


# see [PCH: Unclear error when reusing precompiled headers from interface library](
# https://gitlab.kitware.com/cmake/cmake/-/issues/20288)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp)

add_library(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp)
add_library(ibis::pch ALIAS ${PROJECT_NAME})


target_precompile_headers(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/ibis/pch_default.hpp
)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/ibis/pch_default.hpp
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${strong_type_INCLUDE_DIR}>
)


# What the hell, required fixes for:
#
# (1) encoding to cope with MSVC:
#     - error C2855: The command line option "/source-charset" conflicts with the precompiled header file
#     - error C2855: The command line option "/execution-charset" conflicts with the precompiled header file
#     `cmake --trace-expand --preset msvc 2>&1> cmake.configure.txt` shows e.g.:
#     build/generators/fmt-release-x86_64-data.cmake(27):  set(fmt_COMPILE_OPTIONS_CXX_RELEASE /utf-8 )
target_compile_options(${PROJECT_NAME}
    PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)
# (2) MSVC's DLL Linker error (only for boost_locale) by use of static installed Conan libs (for 
#     some unknown reason 'BOOST_ALL_NO_LIB' isn't defined in all cases):
#     - fatal error LNK1104: cannot open "libboost_locale-vc143-mt-x64-1_86.lib"
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:Boost::disable_autolinking>"
)


if(DEVELOPER_BOOST_SPIRIT_X3_DEBUG)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG
    )
endif()
