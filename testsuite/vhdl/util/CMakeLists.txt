################################################################################
## EDA/testsuite util project
##
## file: testsuite/vhdl/util/CMakeLists.txt
################################################################################

project(testsuite_util LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(testsuite::util ALIAS ${PROJECT_NAME})


# default paths and settings
configure_file(
    ${PROJECT_SOURCE_DIR}/include/testsuite/util/compile_builtin.hpp.in
    ${PROJECT_BINARY_DIR}/include/testsuite/util/compile_builtin.hpp
    @ONLY
)


add_dependencies(${PROJECT_NAME}
    external-cli11
)


if(DEVELOPER_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME}
    PRIVATE
        src/cli_args.cpp
        src/data_set.cpp
        src/failure_diagnostic_fixture.cpp
)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/util/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/util/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
)
