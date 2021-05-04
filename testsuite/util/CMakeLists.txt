################################################################################
## IBIS/testsuite util project
##
## file: testsuite/vhdl/util/CMakeLists.txt
################################################################################
project(testsuite_util LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(testsuite::util ALIAS ${PROJECT_NAME})


add_dependencies(${PROJECT_NAME}
    external-cli11
)


if(DEVELOPER_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME}
    PRIVATE
        src/cli_args.cpp
        src/dataset_loader.cpp
        src/basic_failure_diagnostic_fixture.cpp
)

if(${PROJECT_NAME}_PCH)
    # override testsuite::pch helper
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/testsuite/util/detail/pch_default.hpp>
            $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/testsuite/util/detail/pch_ibis.hpp>
    )
elseif(IBIS_ENABLE_PCH_DEFAULT OR IBIS_ENABLE_PCH_IBIS)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM testsuite::pch)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)
