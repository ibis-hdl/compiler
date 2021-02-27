################################################################################
## EDA/testsuite common project
##
## file: testsuite/common/CMakeLists.txt
################################################################################

project(testsuite_common LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(testsuite::common ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        eda::common
)


if(EDA_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME} 
    PRIVATE
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
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)
