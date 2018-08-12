################################################################################
## testsuite/vhdl/syntax/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite for the synatx test for parser 
################################################################################

project(testrunner_vhdl_syntax LANGUAGES CXX)


set(SYNTAXTEST_COMMON_SOURCES
    src/common/test_vhdl_syntax.cpp
)

set(SYNTAXTEST_SOURCES
    ${SYNTAXTEST_COMMON_SOURCES}
    src/simple.cpp
    #src/ast_walk_node_count.cpp -> strange error
)


add_executable(${PROJECT_NAME} ${SYNTAXTEST_SOURCES})

# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


# adjust include path
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

##
# Boost.Org UTF
find_package(Boost REQUIRED COMPONENTS system filesystem locale unit_test_framework)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl_grammar?
    testsuite::common
    Boost::system
    Boost::filesystem
    Boost::locale
)


## 
# CMake/CTest
# The argument is the top level directory of the test directories of 'test_case'
add_test(NAME test_vhdl_syntax
    COMMAND ${PROJECT_NAME} -- 
    --source-prefix=${PROJECT_SOURCE_DIR}
)
