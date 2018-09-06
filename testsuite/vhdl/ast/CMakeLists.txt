################################################################################
## testsuite/vhdl/ast/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite related to AST 
################################################################################

project(testrunner_ast LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")



# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


add_dependencies(${PROJECT_NAME} boost-utf)


target_sources(${PROJECT_NAME} PRIVATE
    src/common/test_ast.cpp
    src/common/position_cache_fixture.cpp
)


target_sources(${PROJECT_NAME} PRIVATE
    src/position_cache_test_1.cpp
    src/position_cache_test_2.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
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


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    testsuite::common
    Boost::system
    Boost::filesystem
)


## 
# CMake/CTest
add_test(NAME test_ast
    COMMAND ${PROJECT_NAME} -- 
    --source-dir=${PROJECT_SOURCE_DIR}/test_case
)
