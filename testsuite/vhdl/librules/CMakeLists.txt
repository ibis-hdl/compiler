################################################################################
## testsuite/vhdl/librules/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite library for rules 
##
## The purpose of this project is simply to allow this big object to be compile
## in parallel with low-memory configurations, e.g. using ninja's pool feature.
## On real developer machines set the JOB_POOL_COMPILE to job_pool_max_cores.
################################################################################

project(testsuite_vhdl_rules LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(testsuite::vhdl_rules ALIAS ${PROJECT_NAME})



# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_one_core)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


##
# Boost.Org's local git clone(s)
add_dependencies(${PROJECT_NAME} boost-spirit-x3)


target_sources(${PROJECT_NAME} PRIVATE
    src/rules_1.cpp
    src/rules_2.cpp
    src/rules_api.cpp
    #src/rules.cpp -> single file
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
        src/rules_1.cpp
        src/rules_2.cpp
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
