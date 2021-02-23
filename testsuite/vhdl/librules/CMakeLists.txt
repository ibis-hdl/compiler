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



# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_one_core)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


if(EDA_EXTERNAL_BOOST_SPIRIT_X3)
    add_dependencies(${PROJECT_NAME} external-boost-spirit-x3)
endif()


# Check on big RAM power stations to compile big files
cmake_host_system_information(
    RESULT localhost_RAM_MB
    QUERY  AVAILABLE_PHYSICAL_MEMORY
)

if(localhost_RAM_MB GREATER 12000)
    set(SOURCE_LIST src/rules.cpp)
else()
    # FixMe: This is not the best solution to cope with low RAM situations. 
    # Do conditional compiling the file rules.cpp for {A-Z} rules into multiple 
    # object files.
    set(SOURCE_LIST 
        src/rules_api.cpp
        src/rules_a.cpp 
        src/rules_b.cpp 
        src/rules_c.cpp 
        src/rules_d.cpp 
        src/rules_e.cpp 
        src/rules_f.cpp 
        src/rules_g.cpp
        src/rules_i.cpp 
        src/rules_l.cpp 
        src/rules_n.cpp 
        src/rules_p.cpp 
        src/rules_q.cpp 
        src/rules_r.cpp 
        src/rules_s.cpp 
        src/rules_t.cpp 
        src/rules_u.cpp 
        src/rules_v.cpp 
        src/rules_w.cpp 
    )
endif()

target_sources(${PROJECT_NAME} PRIVATE
    ${SOURCE_LIST}
)


target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:      /W1>
    $<$<CXX_COMPILER_ID:GNU>:       -Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:     -Wall -Wextra>
)


# handle problems with Spirit.X template depth
target_compile_options(${PROJECT_NAME} PRIVATE
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


target_link_libraries(${PROJECT_NAME} PRIVATE
    eda::vhdl_parser
)

