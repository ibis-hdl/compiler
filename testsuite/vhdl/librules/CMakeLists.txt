################################################################################
## IBIS/testsuite VHDL rules project
##
## The purpose of this project is simply to allow this big object to be compile
## in parallel with low-memory configurations.
##
## file: testsuite/vhdl/librules/CMakeLists.txt
################################################################################

project(testsuite_vhdl_rules LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(testsuite::vhdl_rules ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME} PRIVATE
    ibis::vhdl
)

if(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)
    add_dependencies(${PROJECT_NAME} external-boost-spirit-x3)
endif()


target_sources(${PROJECT_NAME}
    PRIVATE
        src/rules.cpp
)


set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_10240MiB
)


if (IBIS_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


#
# parser with Spirit.X3 DEBUG
set(IBIS_VHDL_PARSER_DEBUG OFF CACHE BOOL "debug printer of spirit.x3 parser tree")
if(${IBIS_VHDL_PARSER_DEBUG})
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG)
endif()
