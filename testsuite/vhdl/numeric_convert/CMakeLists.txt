################################################################################
## testsuite/vhdl/numeric_convert/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite for converting parsed literals to numeric 
################################################################################

project(testrunner_vhdl_numeric LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")



# Ninja Build
set_property(TARGET testrunner_vhdl_numeric PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
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



if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall 
        -Wextra
    )
endif()


# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


# increase limit especially for clang recursive template instantiation,
# otherwise exceedes maximum depth of 512
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -ftemplate-depth=1024)
endif()


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    testsuite::common
    Boost::system
    Boost::filesystem
    Boost::locale
)


## 
# CMake/CTest
add_test(NAME test_vhdl_numeric_conversion
    COMMAND ${PROJECT_NAME}
)
