################################################################################
## testsuite/vhdl/numeric_convert/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite for converting parsed literals to numeric 
################################################################################

project(testrunner_vhdl_numeric LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")



# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


add_dependencies(${PROJECT_NAME} boost-spirit-x3)
add_dependencies(${PROJECT_NAME} boost-utf)


target_sources(${PROJECT_NAME} PRIVATE
    src/common/test_numeric_convert.cpp
    src/common/numeric_parser.cpp
    src/common/binary_string.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    src/bit_string_literal_test.cpp
    src/decimal_literal_test.cpp
    src/based_literal_test.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${SPIRIT_X3_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${BOOST_UTF_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME} PRIVATE
    # don't allow automatically select which libraries to link against    
    $<$<CXX_COMPILER_ID:MSVC>:BOOST_ALL_NO_LIB>
)


target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:      /W1>
    $<$<CXX_COMPILER_ID:GNU>:       -Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:     -Wall -Wextra>
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    testsuite::common
    Boost::system
    Boost::filesystem
    Boost::locale
)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Boost::unit_test_framework 
    )
endif()


#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


## 
# CMake/CTest
add_test(NAME test_vhdl_numeric_conversion
    COMMAND ${PROJECT_NAME}
)
