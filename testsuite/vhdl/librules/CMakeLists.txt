################################################################################
## EDA/testsuite VHDL rules project
##
## The purpose of this project is simply to allow this big object to be compile
## in parallel with low-memory configurations, e.g. using ninja's pool feature.
## On real developer machines set the JOB_POOL_COMPILE to job_pool_max_cores.
##
## file: testsuite/vhdl/librules/CMakeLists.txt
################################################################################

project(testsuite_vhdl_rules LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(testsuite::vhdl_rules ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME} PRIVATE
    eda::vhdl_parser
)

if(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)
    add_dependencies(${PROJECT_NAME} external-boost-spirit-x3)
endif()


# Ninja Build override to cope on low memory situations to compile "big" files
# FixMe: Maybe use Unity (Jumbo) Builds to solve maintenance of two equal sources
# see https://onqtam.com/programming/2019-12-20-pch-unity-cmake-3-16/
# https://cmake.org/cmake/help/v3.18/prop_tgt/UNITY_BUILD.html
set(SOURCE_LIST_HIGH_MEM
    src/rules.cpp
)
set(SOURCE_LIST_LOW_MEM
    src/rules_api.cpp
    src/rules_a.cpp    src/rules_b.cpp    src/rules_c.cpp 
    src/rules_d.cpp    src/rules_e.cpp    src/rules_f.cpp 
    src/rules_g.cpp                       src/rules_i.cpp 
    src/rules_l.cpp                       src/rules_n.cpp 
    src/rules_p.cpp    src/rules_q.cpp    src/rules_r.cpp 
    src/rules_s.cpp    src/rules_t.cpp    src/rules_u.cpp
    src/rules_v.cpp    src/rules_w.cpp 
)

cmake_host_system_information(
    RESULT localhost_RAM_MiB
    QUERY  AVAILABLE_PHYSICAL_MEMORY
)

if(localhost_RAM_MiB LESS 12000)
    set(SOURCE_LIST
        ${SOURCE_LIST_LOW_MEM}
    )
    # FixMe: Does it really work??
    set_source_files_properties(${SOURCE_LIST}
        PROPERTIES
            JOB_POOL_COMPILE NINJA_JOBS_ONE_CPU
    ) 
else()
    set(SOURCE_LIST
        ${SOURCE_LIST_HIGH_MEM}
    )
endif()


target_sources(${PROJECT_NAME} 
    PRIVATE
        ${SOURCE_LIST}
)


if (EDA_ENABLE_PCH)
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


# handle problems with Spirit.X template depth
target_compile_options(${PROJECT_NAME} 
    PRIVATE
        # - limit gcc/clang template error depth printing
        # - increase limit especially for clang recursive template instantiation,
        #   otherwise exceedes maximum depth of 512    
        $<$<CXX_COMPILER_ID:GNU>:  -ftemplate-backtrace-limit=0 -ftemplate-depth=1024>
        $<$<CXX_COMPILER_ID:Clang>:-ftemplate-backtrace-limit=0 -ftemplate-depth=1024>
)


# MSVC and MSYS2/MinGW64 has problems with spirit.x3
# increase object size for windows compilers, otherwise build will fail
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CXX_FLAGS_BIG_FILE /bigobj)
elseif(WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CXX_FLAGS_BIG_FILE -Wa,-mbig-obj)
endif()

if(WIN32)
    set_source_files_properties(
        ${SOURCE_LIST}
        PROPERTIES COMPILE_FLAGS "${CXX_FLAGS_BIG_FILE}"
    )
endif()


#
# parser with Spirit.X3 DEBUG
set(EDA_VHDL_PARSER_DEBUG OFF CACHE BOOL "debug printer of spirit.x3 parser tree")
if("${EDA_VHDL_PARSER_DEBUG}")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG)
endif()
