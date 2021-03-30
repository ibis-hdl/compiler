################################################################################
## EDA/testsuite common project
##
## file: testsuite/common/CMakeLists.txt
################################################################################

project(testsuite_common LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(testsuite::common ALIAS ${PROJECT_NAME})


# FixMe: depend only on eda::util::make_iomanip header for failure_diagnostic_fixture
#        check for get_properties INCLUDE_DIRECTORIES or
#        define a header-only interface library for the headers used in both
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        eda::common
)


# default paths and settings
configure_file(
    ${PROJECT_SOURCE_DIR}/include/testsuite/common/compile_builtin.hpp.in
    ${PROJECT_BINARY_DIR}/include/testsuite/common/compile_builtin.hpp
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
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/common/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/common/detail/pch_prj.hpp>
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
