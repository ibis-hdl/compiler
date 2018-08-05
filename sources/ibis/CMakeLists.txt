################################################################################
## sources/ibis/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(ibis LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")

# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


target_sources(${PROJECT_NAME} PRIVATE
    src/docopt_inst.cpp
    src/parse_env.cpp
    src/parse_cli.cpp
    src/main.cpp
    src/signal.cpp
    #$<BOOL:${EDA_WITH_GDB_STACKTRACE}>:src/stacktrace_gdb.cpp>
)
if(EDA_WITH_GDB_STACKTRACE)
    target_sources(${PROJECT_NAME} PRIVATE
        src/stacktrace_gdb.cpp
    )
endif()


##
# DocOpt++
# parsing command line 
include(external_docopt_cpp)
include_directories(${DOCOPT_CPP_DIR})


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${DOCOPT_CPP_DIR}
)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall 
    -Wextra
)


if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


#target_compile_definitions(${PROJECT_NAME} PRIVATE
#    $<BOOL:${EDA_WITH_GDB_STACKTRACE}>:-DEDA_WITH_GDB_STACKTRACE> 
#)
if(EDA_WITH_GDB_STACKTRACE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DEDA_WITH_GDB_STACKTRACE
    )
endif()


##
# DocOpt++
add_dependencies(${PROJECT_NAME} docopt_cpp)


## 
# Boost.Org Libraries
find_package(Boost REQUIRED COMPONENTS 
    system locale 
    filesystem
)


# Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
    Boost::system
    Boost::locale
    Boost::filesystem
)

