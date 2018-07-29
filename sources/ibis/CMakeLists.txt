################################################################################
## sources/ibis/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(ibis LANGUAGES CXX)


## DocOpt++
# parsing command line 
include(external_docopt_cpp)
include_directories(${DOCOPT_CPP_DIR})


set(IBIS_SOURCE
    ${DOCOPT_CPP_DIR}/docopt.cpp
    src/parse_cli.cpp
    src/global_options.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${IBIS_SOURCE})


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)


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




# Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
)

